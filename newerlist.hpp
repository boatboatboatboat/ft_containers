//
// Created by boat on 11/18/20.
//

#ifndef FT_CONTAINERS_NEWERLIST_HPP
#define FT_CONTAINERS_NEWERLIST_HPP

#include "helpers/enable_if.hpp"
#include "helpers/hacks.hpp"
#include "helpers/is_iterator.hpp"
#include "iterator/iterator.hpp"

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
        dynamic_cast<TailNode*>(position.current_node())->insert_before(new value_node_type(val));
        return --position;
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
        _head = x._head;
        _tail = x._tail;
        x._head = thead;
        x._tail = ttail;
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

    // pretty stupid because it's non-trivial now
    InnerListIterator(InnerListIterator<IsConst, T> const& rhs)
        : _current_node(rhs._current_node)
        , _parent(rhs._parent)
        , _past(rhs._past)
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

    node_type* current_node() { return _current_node; }

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

namespace ft {

template <typename T>
class list {
private:
    typedef InnerList<T> list_type;

public:
    typedef typename list_type::value_type value_type;
    typedef typename list_type::reference reference;
    typedef typename list_type::const_reference const_reference;
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

    // fixes C++ being a bad language
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
        insert(first, last);
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

private:
    size_type _len;
    list_type _inner_list;
};

}

#endif //FT_CONTAINERS_NEWERLIST_HPP
