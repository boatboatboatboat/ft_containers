//
// Created by boat on 11/15/20.
//

#ifndef FT_CONTAINERS_NEWLIST_HPP
#define FT_CONTAINERS_NEWLIST_HPP

#include <stddef.h>

#define CPP_BAD
#define nullptr NULL

namespace ft {

template <typename T>
class ListNode;

template <typename T>
class InnerList;

template <typename T>
class ListIterator {
public:
    typedef ListNode<T> node_type;
    typedef InnerList<T> list_type;

    ListIterator()
        : _current(nullptr)
        , _parent(nullptr)
        , _past(0)
    {
    }

    ListIterator(ListIterator const& other)
        : _current(other._current)
        , _parent(other._parent)
        , _past(other._past)
    {
    }

    ListIterator(node_type* cur, list_type* parent)
        : _current(cur)
        , _parent(parent)
        , _past(cur != nullptr)
    {
    }

    ListIterator insert_before(ListNode<T>* node)
    {
        if (_current == nullptr) {
            _current = node;
            node->prev() = nullptr;
            node->next() = nullptr;
            _parent->head() = _current;
            _parent->tail() = _current;
            _parent->len() = 1;
        } else if (_past > 0) {
            _current = node;
            _parent->tail() = _current;
            _parent->len() += 1;
            if (_parent->len() == 1) {
                _parent->head() = _current;
            }
        } else {
            if (_parent->head() != _current) {
                node_type* pre_current = _current->prev();
                pre_current->next() = node;
            } else {
                _parent->head() = node;
            }
            _current->prev() = node;
            _parent->len() += 1;
        }
        return ListIterator(_current, _parent);
    }

    ListIterator remove()
    {
        if (_past != 0 && _current != nullptr) {
            node_type* ret_val = _current->next();
            if (_current->next() != nullptr) {
                _current->next()->prev() = _current->prev();
            }
            if (_current->prev() != nullptr) {
                _current->prev()->next() = _current->next();
            }
            delete _current;
            return ListIterator(ret_val, _parent);
        }
        return *this;
    }

    ListIterator& operator++()
    {
        if (_past != 0) {
            // we're still past-the-end
            _past += 1;
        } else if (_current != nullptr) {
            _current = _current->next();
        } else if (_parent != nullptr && _parent->head() != nullptr) {
            _current = _parent->head();
        }
        return *this;
    }

    ListIterator operator++(int)
    {
        ListIterator old = *this;
        ++(*this);
        return old;
    }

    ListIterator& operator--()
    {
        if (_past != 0) {
            _past -= 1;
        } else if (_current != nullptr) {
            _current = _current->prev();
        } else if (_parent != nullptr && _parent->tail() != nullptr) {
            _current = _parent->tail();
        }
        return *this;
    }

    ListIterator operator--(int)
    {
        ListIterator old = *this;
        --(*this);
        return old;
    }

    node_type* current()
    {
        return _current;
    }

    node_type const* current() const
    {
        return _current;
    }

    bool operator==(ListIterator const& rhs) const
    {
        return _parent == rhs._parent && _current == rhs._current;
    }

    bool operator!=(ListIterator const& rhs) const
    {
        return !(*this == rhs);
    }

private:
    node_type* _current;
    list_type* _parent;
    int _past;
};

template <typename T>
class ListNode {
public:
    typedef ListNode<T> self_type;
    typedef T value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef value_type* pointer_type;
    typedef value_type const* const_pointer_type;

    ListNode(self_type* prev, self_type* next, value_type inner)
        : _inner(inner)
        , _prev(prev)
        , _next(next)
    {
    }

    explicit ListNode(value_type inner)
        : _inner(inner)
    {
    }

    reference get()
    {
        return _inner;
    }
    const_reference get() const
    {
        return _inner;
    }

    self_type*& next()
    {
        return _next;
    }
    self_type*& prev()
    {
        return _prev;
    }

private:
    ListNode();
    value_type _inner;
    self_type* _prev;
    self_type* _next;
};

template <typename T>
class InnerList {
public:
    typedef T value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef value_type* pointer_type;
    typedef value_type const* const_pointer_type;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef ListNode<T> node_type;
    typedef ListIterator<T> iterator;
    typedef ListIterator<const T> const_iterator;
    typedef reverse_bd_iterator<iterator> reverse_iterator;
    typedef reverse_bd_iterator<const_iterator> const_reverse_iterator;

    InnerList()
        : _len(0)
        , _head(nullptr)
        , _tail(nullptr)
    {
    }

    InnerList(InnerList const& other)
        : _len(0)
        , _head(nullptr)
        , _tail(nullptr)
    {
        iterator iter = iterator(nullptr, this);
        for (const_iterator x = other.begin(); x != other.end(); x++) {
            iter.insert_before(new node_type(x.current()->get()));
        }
    }

    InnerList& operator=(InnerList const& other)
    {
        if (this != &other) {
            return *this;
        }
        clear();
        iterator iter = iterator(nullptr, this);
        for (const_iterator x = other.begin(); x != other.end(); x++) {
            iter.insert_before(new node_type(x.current()->get()));
        }
    }

    ~InnerList()
    {
        clear();
    }

    iterator begin()
    {
        return iterator(head(), this);
    }

    iterator end()
    {
        return iterator(nullptr, this);
    }

    const_iterator begin() const
    {
        return const_iterator(head(), this);
    }

    const_iterator end() const
    {
        return const_iterator(nullptr, this);
    }

    void clear()
    {
        erase(begin(), end());
    }

    iterator erase(iterator position)
    {
        return position.remove();
    }

    iterator erase(iterator first, iterator last)
    {
        while (first != last) {
            first = erase(first);
        }
        return last;
    }

    size_type& len()
    {
        return _len;
    }

    size_type len() const
    {
        return _len;
    }

    bool empty() const
    {
        return len() == 0;
    }

    node_type*& head()
    {
        return _head;
    }

    node_type*& tail()
    {
        return _tail;
    }

    node_type const* head() const
    {
        return _head;
    }

    node_type const* tail() const
    {
        return _tail;
    }

private:
    size_type _len;
    node_type* _head;
    node_type* _tail;
};

template <typename T>
class list {
private:
    typedef InnerList<T> inner_list;
    typedef ListNode<T> node_type;

public:
    typedef T value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef ListIterator<T> iterator;
    typedef ListIterator<T const> const_iterator;
    typedef reverse_bd_iterator<iterator> reverse_iterator;
    typedef reverse_bd_iterator<const_iterator> const_reverse_iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    list()
        : _inner()
    {
    }

    iterator begin()
    {
        return _inner.begin();
    }

    iterator end()
    {
        return _inner.end();
    }

    void push_back(value_type const& x)
    {
        end().insert_before(new node_type(x));
    }

    void push_front(value_type const& x)
    {
        begin().insert_before(new node_type(x));
    }

private:
    inner_list _inner;
};

}

#endif // FT_CONTAINERS_NEWLIST_HPP
