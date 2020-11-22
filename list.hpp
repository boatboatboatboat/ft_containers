//
// Created by boat on 11/18/20.
//

#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include "helpers/enable_if.hpp"
#include "helpers/hacks.hpp"
#include "helpers/is_iterator.hpp"
#include "iterator/iterator.hpp"
#include <functional>

namespace ft {

class AbstractNode {
public:
    virtual ~AbstractNode();
};

class HeadNode : virtual public AbstractNode {
public:
    explicit HeadNode(AbstractNode* next);
    virtual ~HeadNode();

    AbstractNode const* next() const;
    AbstractNode*& next();

    void insert_after(AbstractNode* node);

private:
    HeadNode();
    AbstractNode* _next;
};

class TailNode : virtual public AbstractNode {
public:
    explicit TailNode(AbstractNode* previous);
    virtual ~TailNode();

    AbstractNode const* prev() const
    {
        return _prev;
    }

    AbstractNode*& prev()
    {
        return _prev;
    }

    void insert_before(AbstractNode* node);

private:
    TailNode();
    AbstractNode* _prev;
};

template <typename T>
class ValueNode : public HeadNode, public TailNode {
public:
    explicit ValueNode(T inner)
        : HeadNode(nullptr)
        , TailNode(nullptr)
        , _inner(inner)
    {
    }

    T& inner() { return _inner; }
    T const& inner() const { return _inner; }

    void destroy()
    {
        TailNode* next_node = dynamic_cast<TailNode*>(next());
        HeadNode* prev_node = dynamic_cast<HeadNode*>(prev());
        next_node->prev() = prev_node;
        prev_node->next() = next_node;
        delete this; // LOL
    }

    void reparent(AbstractNode* n)
    {
        {
            TailNode* next_node = dynamic_cast<TailNode*>(next());
            HeadNode* prev_node = dynamic_cast<HeadNode*>(prev());
            next_node->prev() = prev_node;
            prev_node->next() = next_node;
        }
        {
            TailNode* next_node = dynamic_cast<TailNode*>(n);
            HeadNode* prev_node = dynamic_cast<HeadNode*>(next_node->prev());
            next_node->prev() = this;
            prev_node->next() = this;
            next() = next_node;
            prev() = prev_node;
        }
    }

private:
    ValueNode();

    T _inner;
};

template <bool IsConst, typename T>
class InnerListIterator;

template <typename T>
class InnerList {
public:
    typedef InnerList<T> self_type;
    typedef T value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef InnerListIterator<false, T> iterator;
    typedef InnerListIterator<true, T> const_iterator;
    typedef reverse_bd_iterator<iterator> reverse_iterator;
    typedef reverse_bd_iterator<const_iterator> const_reverse_iterator;
    typedef size_t size_type;

    typedef ValueNode<value_type> value_node_type;
    typedef HeadNode head_node_type;
    typedef TailNode tail_node_type;
    typedef AbstractNode node_type;

    // initialization in function is required because of cpp bad + asan bug
    InnerList()
        : _head(nullptr)
        , _tail(nullptr)
    {
        _head = head_node_type(&_tail);
        _tail = tail_node_type(&_head);
    }

    // c++ being bad + asan false positive requires initialization inside of the function
    InnerList(InnerList const& rhs)
        : _head(nullptr)
        , _tail(nullptr)
    {
        _head = head_node_type(&_tail);
        _tail = tail_node_type(&_head);
        node_type const* k = rhs._head.next();
        while (k != &rhs._tail) {
            value_node_type const* x = dynamic_cast<value_node_type const*>(k);
            insert(end(), x->inner());
            k = x->next();
        }
    }

    InnerList& operator=(InnerList const& rhs)
    {
        if (this == &rhs) {
            return *this;
        }
        clear();
        _head = head_node_type(&_tail);
        _tail = tail_node_type(&_head);
        node_type const* k = rhs._head.next();
        while (k != &rhs._tail) {
            value_node_type const* x = dynamic_cast<value_node_type const*>(k);
            insert(end(), x->inner());
            k = x->next();
        }
        return *this;
    }

    ~InnerList()
    {
        clear();
    }

    reference front()
    {
        return dynamic_cast<value_node_type*>(_head.next())->inner();
    }

    const_reference front() const
    {
        return dynamic_cast<value_node_type*>(_head.next())->inner();
    }

    reference back()
    {
        return dynamic_cast<value_node_type*>(_tail.prev())->inner();
    }

    const_reference back() const
    {
        return dynamic_cast<value_node_type*>(_tail.prev())->inner();
    }

    iterator insert(iterator position, value_type const& val)
    {
        value_node_type* x = new value_node_type(val);
        dynamic_cast<TailNode*>(position.current_node())->insert_before(x);
        return iterator(position.parent(), x);
    }

    iterator erase(iterator position)
    {
        iterator next = position;
        ++next;
        dynamic_cast<value_node_type*>(position.current_node())->destroy();
        return next;
    }

    void clear()
    {
        iterator x = begin();
        while (x != end()) {
            x = erase(x);
        }
    }

    iterator begin()
    {
        return iterator(const_cast<self_type*>(this), head()->next());
    }

    iterator end()
    {
        return iterator(const_cast<self_type*>(this), tail());
    }

    const_iterator begin() const
    {
        return const_iterator(const_cast<self_type*>(this), head()->next());
    }

    const_iterator end() const
    {
        return const_iterator(const_cast<self_type*>(this), tail());
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(--end());
    }

    reverse_iterator rend()
    {
        return reverse_iterator(--begin());
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(--end());
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(--begin());
    }

    head_node_type* head()
    {
        return &_head;
    }

    tail_node_type* tail()
    {
        return &_tail;
    }

    head_node_type const* head() const
    {
        return &_head;
    }

    tail_node_type const* tail() const
    {
        return &_tail;
    }

    void swap(InnerList& x)
    {
        head_node_type thead = _head;
        tail_node_type ttail = _tail;

        if (x._head.next() == &x._tail) {
            _head = head_node_type(&_tail);
            _tail = tail_node_type(&_head);
        } else {
            _head = x._head;
            dynamic_cast<TailNode*>(_head.next())->prev() = &_head;
            _tail = x._tail;
            dynamic_cast<HeadNode*>(_tail.prev())->next() = &_tail;
        }
        if (thead.next() == &_tail) {
            x._head = head_node_type(&x._tail);
            x._tail = tail_node_type(&x._head);
        } else {
            x._head = thead;
            dynamic_cast<TailNode*>(x._head.next())->prev() = &x._head;
            x._tail = ttail;
            dynamic_cast<HeadNode*>(x._tail.prev())->next() = &x._tail;
        }
    }

private:
    head_node_type _head;
    tail_node_type _tail;
};

template <bool IsConst, typename T>
class InnerListIterator {
public:
    typedef InnerListIterator<IsConst, T> self_type;
    typedef InnerList<T> list_type;
    typedef T value_type;
    typedef AbstractNode node_type;
    typedef TailNode tail_node_type;
    typedef HeadNode head_node_type;
    typedef ValueNode<value_type> value_node_type;

    InnerListIterator()
        : _current_node(nullptr)
        , _parent(nullptr)
        , _past(0)
    {
    }

    InnerListIterator(InnerListIterator<true, T> const& rhs)
        : _current_node(rhs.current_node())
        , _parent(rhs.parent())
        , _past(rhs.past())
    {
    }
    InnerListIterator(InnerListIterator<false, T> const& rhs)
        : _current_node(rhs.current_node())
        , _parent(rhs.parent())
        , _past(rhs.past())
    {
    }

    InnerListIterator(list_type* parent, node_type* cn)
        : _current_node(cn)
        , _parent(parent)
        , _past(0)
    {
    }

    InnerListIterator(list_type const* parent, node_type const* cn)
        : _current_node(const_cast<node_type*>(cn))
        , _parent(const_cast<list_type*>(parent))
        , _past(0)
    {
    }

    value_type& operator*()
    {
        return dynamic_cast<value_node_type*>(_current_node)->inner();
    }

    value_type const& operator*() const
    {
        return dynamic_cast<value_node_type*>(_current_node)->inner();
    }

    value_type* operator->()
    {
        return &dynamic_cast<value_node_type*>(_current_node)->inner();
    }

    value_type const* operator->() const
    {
        return &dynamic_cast<value_node_type*>(_current_node)->inner();
    }

    node_type* current_node() const { return _current_node; }

    self_type& operator++()
    {
        if (_parent != nullptr) {
            if (_past != 0 || _current_node == _parent->tail()) {
                _past += 1;
            } else {
                _current_node = dynamic_cast<HeadNode*>(_current_node)->next();
            }
        }
        return *this;
    }

    self_type operator++(int)
    {
        self_type old = *this;
        ++(*this);
        return old;
    }

    self_type& operator--()
    {
        if (_parent != nullptr) {
            if (_past != 0 || _current_node == _parent->head()) {
                _past -= 1;
            } else {
                _current_node = dynamic_cast<TailNode*>(_current_node)->prev();
            }
        }
        return *this;
    }

    self_type operator--(int)
    {
        self_type old = *this;
        --(*this);
        return old;
    }

    list_type* parent() const { return _parent; }
    int past() const { return _past; }

    bool operator==(self_type const& rhs) const { return _parent == rhs._parent && _current_node == rhs._current_node; }
    bool operator!=(self_type const& rhs) const { return !(*this == rhs); }

private:
    node_type* _current_node;
    list_type* _parent;
    int _past;
};

}

template <typename T>
struct type_dereference<ft::InnerListIterator<true, T> CPP_BAD> {
    typedef T type;
};
template <typename T>
struct type_dereference<ft::InnerListIterator<false, T> CPP_BAD> {
    typedef T type;
};
template <typename T>
struct is_iterator<ft::InnerListIterator<false, T> CPP_BAD> {
    static const bool value = true;
};
template <typename T>
struct is_iterator<ft::InnerListIterator<true, T> CPP_BAD> {
    static const bool value = true;
};

namespace ft {

template <typename T>
class list {
private:
    typedef InnerList<T> list_type;

public:
    typedef typename list_type::value_type value_type;
    typedef typename list_type::reference reference;
    typedef typename list_type::const_reference const_reference;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef typename list_type::iterator iterator;
    typedef typename list_type::const_iterator const_iterator;
    typedef typename list_type::reverse_iterator reverse_iterator;
    typedef typename list_type::const_reverse_iterator const_reverse_iterator;

    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    list()
        : _len(0)
        , _inner_list()
    {
    }

    explicit list(size_type n, value_type const& val = value_type())
        : _len(0)
        , _inner_list()
    {
        assign(n, val);
    }

    template <typename InputIterator>
    list(InputIterator first, InputIterator last,
        typename enable_if<is_iterator<InputIterator>::dummy>::type* = 0)
        : _len(0)
        , _inner_list()
    {
        assign(first, last);
    }

    list(list const& rhs)
        : _len(rhs._len)
        , _inner_list(rhs._inner_list)
    {
    }

    list& operator=(list const& rhs)
    {
        if (this == &rhs) {
            return *this;
        }
        _len = rhs._len;
        _inner_list = rhs._inner_list;
        return *this;
    }

    iterator begin() { return _inner_list.begin(); }
    const_iterator begin() const { return _inner_list.begin(); }
    iterator end() { return _inner_list.end(); }
    const_iterator end() const { return _inner_list.end(); }
    reverse_iterator rbegin() { return _inner_list.rbegin(); }
    const_reverse_iterator rbegin() const { return _inner_list.rbegin(); }
    reverse_iterator rend() { return _inner_list.rend(); }
    const_reverse_iterator rend() const { return _inner_list.rend(); }

    bool empty() const
    {
        return _len == 0;
    }

    size_type size() const
    {
        return _len;
    }

    size_type max_size() const
    {
        return -1UL;
    }

    reference front()
    {
        return _inner_list.front();
    }

    const_reference front() const
    {
        return _inner_list.front();
    }

    reference back()
    {
        return _inner_list.back();
    }

    const_reference back() const
    {
        return _inner_list.back();
    }

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last,
        typename enable_if<is_iterator<InputIterator>::value>::type* = 0)
    {
        clear();
        insert(begin(), first, last);
    }

    void assign(size_type n, value_type const& val)
    {
        clear();
        insert(begin(), n, val);
    }

    void push_front(value_type const& val)
    {
        insert(begin(), val);
    }

    void pop_front()
    {
        erase(begin());
    }

    void push_back(value_type const& val)
    {
        insert(end(), val);
    }

    void pop_back()
    {
        erase(--end());
    }

    iterator insert(iterator position, value_type const& val)
    {
        _len += 1;
        return _inner_list.insert(position, val);
    }

    void insert(iterator position, size_type n, value_type const& val)
    {
        for (; n > 0; n--) {
            insert(position, val);
        }
    }

    template <typename InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last,
        typename enable_if<is_iterator<InputIterator>::value>::type* = 0)
    {
        while (first != last) {
            insert(position, *first);
            first++;
        }
    }

    iterator erase(iterator position)
    {
        _len -= 1;
        return _inner_list.erase(position);
    }

    iterator erase(iterator first, iterator last)
    {
        while (first != last) {
            first = erase(first);
            ++first;
        }
        return first;
    }

    void swap(list& x)
    {
        size_type tlen = _len;
        _len = x._len;
        x._len = tlen;
        _inner_list.swap(x._inner_list);
    }

    void resize(size_type n, value_type const& val = value_type())
    {
        while (n < _len) {
            pop_back();
        }
        while (n > _len) {
            push_back(val);
        }
    }

    void clear()
    {
        _len = 0;
        _inner_list.clear();
    }

    void splice(iterator position, list& x)
    {
        splice(position, x, x.begin(), x.end());
    }

    void splice(iterator position, list& x, iterator i)
    {
        dynamic_cast<ValueNode<T>*>(i.current_node())->reparent(position.current_node());
        x._len -= 1;
        _len += 1;
    }

    void splice(iterator position, list& x, iterator first, iterator last)
    {
        while (first != last) {
            iterator k = first;
            ++k;
            splice(position, x, first);
            first = k;
        }
    }

    void remove(value_type const& val)
    {
        iterator x = begin();
        while (x != end()) {
            if (*x == val) {
                x = erase(x);
            } else {
                ++x;
            }
        }
    }

    template <typename Predicate>
    void remove_if(Predicate pred)
    {
        iterator x = begin();
        while (x != end()) {
            if (pred(*x)) {
                x = erase(x);
            } else {
                ++x;
            }
        }
    }

    void unique()
    {
        if (empty()) {
            return;
        }
        iterator unique = begin();
        iterator iter = ++begin();
        while (iter != end()) {
            if (*unique == *iter) {
                iter = erase(iter);
            } else {
                unique = iter;
                ++iter;
            }
        }
    }

    template <typename BinaryPredicate>
    void unique(BinaryPredicate binary_pred)
    {
        if (empty()) {
            return;
        }
        iterator unique = begin();
        iterator iter = ++begin();
        while (iter != end()) {
            if (binary_pred(*unique, *iter)) {
                iter = erase(iter);
            } else {
                unique = iter;
                ++iter;
            }
        }
    }

    void merge(list& x)
    {
        if (this == &x) {
            return;
        }

        list nt;

        iterator cur_lhs = begin();
        iterator cur_rhs = x.begin();
        const_iterator end_lhs = end();
        const_iterator end_rhs = x.end();

        while ((cur_lhs != end_lhs) && (cur_rhs != end_rhs)) {
            if (*cur_lhs < *cur_rhs) {
                nt.push_back(*cur_lhs);
                ++cur_lhs;
            } else {
                nt.push_back(*cur_rhs);
                ++cur_rhs;
            }
        }
        while (cur_lhs != end_lhs) {
            nt.push_back(*cur_lhs);
            ++cur_lhs;
        }
        while (cur_rhs != end_rhs) {
            nt.push_back(*cur_rhs);
            ++cur_rhs;
        }
        x.clear();
        *this = nt;
    }

    template <typename Compare>
    void merge(list& x, Compare comp)
    {
        if (this == &x) {
            return;
        }

        list nt;

        iterator cur_lhs = begin();
        iterator cur_rhs = x.begin();
        const_iterator end_lhs = end();
        const_iterator end_rhs = x.end();

        while ((cur_lhs != end_lhs) && (cur_rhs != end_rhs)) {
            if (comp(*cur_lhs, *cur_rhs)) {
                iterator n = cur_lhs;
                ++n;
                nt.splice(nt.end(), *this, cur_lhs);
                cur_lhs = n;
            } else {
                iterator n = cur_rhs;
                ++n;
                nt.splice(nt.end(), x, cur_rhs);
                cur_rhs = n;
            }
        }
        while (cur_lhs != end_lhs) {
            iterator n = cur_lhs;
            ++n;
            nt.splice(nt.end(), *this, cur_lhs);
            cur_lhs = n;
        }
        while (cur_rhs != end_rhs) {
            iterator n = cur_rhs;
            ++n;
            nt.splice(nt.end(), x, cur_rhs);
            cur_rhs = n;
        }
        *this = nt;
    }

    void sort()
    {
        if (empty()) {
            return;
        }

        list funny;

        iterator cur_it = begin();
        while (!empty()) {
            iterator min_it = cur_it;
            while (cur_it != end()) {
                if (*cur_it < *min_it) {
                    min_it = cur_it;
                }
                ++cur_it;
            }
            if (min_it != end()) {
                funny.splice(funny.end(), *this, min_it);
            }
            cur_it = begin();
        }
        funny.swap(*this);
    }

    template <typename Compare>
    void sort(Compare comp)
    {
        if (empty()) {
            return;
        }

        list funny;

        iterator cur_it = begin();
        while (!empty()) {
            iterator min_it = cur_it;
            while (cur_it != end()) {
                if (comp(*cur_it, *min_it)) {
                    min_it = cur_it;
                }
                ++cur_it;
            }
            if (min_it != end()) {
                funny.splice(funny.end(), *this, min_it);
            }
            cur_it = begin();
        }
        funny.swap(*this);
    }

    void reverse()
    {
        list funny;
        while (begin() != end()) {
            funny.splice(funny.begin(), *this, begin());
        }
        *this = funny;
    }

    friend bool operator==(list const& lhs, list const& rhs)
    {
        if (&lhs == &rhs) {
            return true;
        }
        if (lhs.size() != rhs.size()) {
            return false;
        }

        const_iterator si = lhs.begin();
        const_iterator oi = rhs.begin();
        while (si != lhs.end()) {
            if (*si != *oi) {
                return false;
            }
            si++;
            oi++;
        }
        return true;
    }

    friend bool operator!=(list const& lhs, list const& rhs) { return !(lhs == rhs); }

    friend bool operator<(list const& lhs, list const& rhs)
    {
        if (&lhs == &rhs) {
            return false;
        }
        const_iterator si = lhs.begin();
        const_iterator oi = rhs.begin();
        while (si != lhs.end()) {
            if (oi == rhs.end() || *oi < *si) {
                return false;
            } else if (*oi < *si) {
                return true;
            }
            si++;
            oi++;
        }
        return oi != rhs.end();
    }

    friend bool operator>(list const& lhs, list const& rhs) { return rhs < lhs; }
    friend bool operator<=(list const& lhs, list const& rhs) { return !(lhs > rhs); }
    friend bool operator>=(list const& lhs, list const& rhs) { return !(lhs < rhs); }

private:
    size_type _len;
    list_type _inner_list;
};

}

template <typename T>
void swap(ft::list<T>& a, ft::list<T>& b)
{
    a.swap(b);
}

#endif //FT_CONTAINERS_LIST_HPP
