//
// Created by boat on 11/9/20.
//

#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include "helpers/enable_if.hpp"
#include "helpers/hacks.hpp"
#include "helpers/is_iterator.hpp"
#include "helpers/type_dereference.hpp"
#include "iterator/iterator.hpp"
#include <cstddef>
#include <stdexcept>
#include <stdint.h>
#define CPP_BAD
#define nullptr NULL
#define list_end_ptr nullptr

namespace ft {

template <typename T>
class list;

template <typename _>
class NewListItem_tp {
public:
    explicit NewListItem_tp(NewListItem_tp* prev, NewListItem_tp* next)
        : prev(prev)
        , next(next)
    {
    }
    NewListItem_tp* prev;
    NewListItem_tp* next;
    virtual ~NewListItem_tp() { }

private:
    NewListItem_tp();
};
typedef NewListItem_tp<void> ListItem;

template <typename T>
class ValueItem : public ListItem {
public:
    explicit ValueItem(ListItem* prev, ListItem* next, T inner)
        : ListItem(prev, next)
        , inner(inner)
    {
    }
    virtual ~ValueItem() { }
    T inner;

private:
    ValueItem();
};

template <typename _>
class IndicatorItem_tp : public ListItem {
public:
    explicit IndicatorItem_tp(ListItem* prev, ListItem* next)
        : ListItem(prev, next)
    {
    }
    virtual ~IndicatorItem_tp() { }

private:
    IndicatorItem_tp();
};
typedef IndicatorItem_tp<void> IndicatorItem;

template <typename T>
class list_iterator;

}

template <typename T>
struct type_dereference<ft::list_iterator<T> CPP_BAD> {
    typedef T type;
};

namespace ft {
template <typename T>
class list_iterator {
public:
    typedef list_iterator self_type;
    typedef self_type& self_reference;
    typedef self_type const& const_self_reference;
    typedef T value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef value_type* pointer_type;
    typedef value_type const* const_pointer_type;
    typedef ListItem* item_type;
    typedef ValueItem<T>* value_item_type;
    typedef IndicatorItem* tag_item_type;
    typedef list<T>* parent_type;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    list_iterator()
        : _item(nullptr)
        , _parent(nullptr)
        , _is_end(true)
    {
    }

    explicit list_iterator(item_type item, parent_type parent, bool at_end)
        : _item(item)
        , _parent(parent)
        , _is_end(at_end)
    {
    }

    list_iterator(const_self_reference x)
        : _item(x._item)
        , _parent(x._parent)
        , _is_end(x._is_end)
    {
    }

    list_iterator& operator=(const_self_reference x)
    {
        _item = x._item;
        _parent = x._parent;
        _is_end = x._is_end;
        return *this;
    }

    ~list_iterator()
    {
    }

    item_type base() const
    {
        return _item;
    }

    bool operator==(const_self_reference x) const
    {
        return _is_end == x._is_end && _item == x._item;
    }

    bool operator!=(const_self_reference x) const
    {
        return !(*this == x);
    }

    self_type& operator++()
    {
        if (_item == nullptr) {
            return *this;
        }
        if (_item->next == nullptr) {
            _is_end = true;
        } else {
            _item = _item->next;
        }
        return *this;
    }

    self_type operator++(int)
    {
        self_type old = *this;
        ++(*this);
        return list_iterator(old);
    }

    self_type& operator--()
    {
        if (_item == nullptr) {
            return *this;
        }
        if (_item->prev != nullptr) {
            if (_is_end) {
                _item = _item->prev;
            } else {
                _is_end = false;
            }
        }
        return *this;
    }

    self_type operator--(int)
    {
        self_type old = *this;
        --(*this);
        return list_iterator(old);
    }

    reference operator*()
    {
        return dynamic_cast<value_item_type>(_item)->inner;
    }

    const_reference operator*() const
    {
        return dynamic_cast<value_item_type>(_item)->inner;
    }

    pointer_type operator->()
    {
        return &(dynamic_cast<value_item_type>(_item)->inner);
    }

    const_pointer_type operator->() const
    {
        return &(dynamic_cast<value_item_type>(_item)->inner);
    }

private:
    item_type _item;
    parent_type _parent;
    bool _is_end;
};
}

template <typename T>
struct is_iterator<ft::list_iterator<T> CPP_BAD> {
    static const bool value = true;
};

template <typename T>
struct is_iterator<ft::list_iterator<const T> CPP_BAD> {
    static const bool value = true;
};

namespace ft {
template <typename T>
class list {
private:
    typedef ListItem item_type;
    typedef ValueItem<T> value_item_type;
    typedef IndicatorItem tag_item_type;

public:
    typedef T value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;
    typedef list_iterator<T> iterator;
    typedef list_iterator<T const> const_iterator;
    typedef reverse_bd_iterator<iterator> reverse_iterator;
    typedef reverse_bd_iterator<const_iterator> const_reverse_iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    list()
        : _len(0)
        , _front(&_head)
        , _back(&_tail)
        , _head(nullptr, &_tail, Head)
        , _tail(&_head, nullptr, Tail)
    {
    }

    explicit list(size_type n, value_type const& val = value_type())
        : _len(n)
        , _front(&_head)
        , _back(&_tail)
        , _head(nullptr, &_tail, Head)
        , _tail(&_head, nullptr, Tail)
    {
        insert(begin(), n, val);
    }

    template <typename InputIterator>
    list(InputIterator first, InputIterator last)
        : _len(0)
        , _front(&_head)
        , _back(&_tail)
        , _head(nullptr, &_tail, Head)
        , _tail(&_head, nullptr, Tail)

    {
        insert(first, last);
    }

    list(list const& x)
        : _len(0)
        , _front(&_head)
        , _back(&_tail)
        , _head(nullptr, &_tail, Head)
        , _tail(&_head, nullptr, Tail)
    {
        insert(begin(), x.begin(), x.end());
    }

    ~list()
    {
        clear();
    }

    list& operator=(list const& x)
    {
        if (this == &x) {
            return *this;
        }
        clear();
        insert(begin(), x.begin(), x.end());
        return *this;
    }

    iterator begin()
    {
        return iterator(_front, this, empty());
    }

    const_iterator begin() const
    {
        return const_iterator(
            reinterpret_cast<ListItem*>(_front),
            CPP98_IS_BAD(list<const T>*, this),
            empty());
    }

    iterator end()
    {
        return iterator(_back, this, true);
    }

    const_iterator end() const
    {
        return const_iterator(
            reinterpret_cast<ListItem*>(_front),
            CPP98_IS_BAD(list<const T>*, this),
            true);
    }

    const_reverse_iterator rbegin() const
    {
        const_iterator c = end();
        if (!empty()) {
            --c;
        }
        return const_reverse_iterator(c);
    }

    reverse_iterator rbegin()
    {
        iterator c = end();
        if (!empty()) {
            --c;
        }
        return reverse_iterator(c);
    }

    const_reverse_iterator rend() const
    {
        const_iterator c = begin();
        if (!empty()) {
            --c;
        }
        return const_reverse_iterator(c);
    }

    reverse_iterator rend()
    {
        iterator c = begin();
        if (!empty()) {
            --c;
        }
        return reverse_iterator(c);
    }

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
        return SIZE_MAX;
    }

    reference front()
    {
        return dynamic_cast<value_item_type*>(_front)->inner;
    }

    const_reference front() const
    {
        return dynamic_cast<value_item_type*>(_front)->inner;
    }

    reference back()
    {
        return dynamic_cast<value_item_type*>(_back)->inner;
    }

    const_reference back() const
    {
        return dynamic_cast<value_item_type*>(_back)->inner;
    }

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
        (void)first;
        (void)last;
        insert(first, last);
        throw std::runtime_error("unimplemented");
    }

    void assign(size_type n, value_type const& val)
    {
        insert(n, val);
        throw std::runtime_error("unimplemented");
    }

    void push_front(value_type const& val)
    {
        insert(begin(), val);
    }

    void pop_front()
    {
        _front = _front->next;
        delete _front->prev;
        _front->prev = nullptr;
    }

    void push_back(value_type const& val)
    {
        insert(end(), val);
    }

    void pop_back()
    {
        (void)erase(--end());
    }

    iterator insert(iterator position, value_type const& val)
    {
        item_type* prev = (--iterator(position)).base();
        item_type* next = position.base();
        if (prev == next) {
            prev = nullptr;
        }
        item_type* new_item = new value_item_type(prev, next, val);

        if (empty()) {
            _front = new_item;
            _back = new_item;
        } else {
            next->prev = new_item;
        }
        if (prev == nullptr) {
            _front = new_item;
        } else {
            prev->next = new_item;
        }
        _len += 1;
        return iterator(new_item, this, false);
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
        item_type* base = position.base();
        if (base->next != nullptr) {
            base->next->prev = base->prev;
            _back = base->next;
        }
        if (base->prev != nullptr) {
            base->prev->next = base->next;
            _front = base->prev;
        }
        ++position;
        delete base;
        _len -= 1;
        return position;
    }

    iterator erase(iterator first, iterator last)
    {
        while (first != last) {
            first = erase(first);
        }
        return last;
    }

    void clear()
    {
        erase(begin(), end());
    }

private:
    size_type _len;
    item_type* _front;
    item_type* _back;
    tag_item_type _ghost;
};

}

#endif //FT_CONTAINERS_LIST_HPP
