//
// Created by boat on 11/19/20.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include "list.hpp"
#include <functional>

namespace ft {

template <typename K, typename V>
struct pair {
    pair()
        : first()
        , second()
    {
    }
    pair(K k, V v)
        : first(k)
        , second(v)
    {
    }
    typedef K first_type;
    typedef V second_type;
    K first;
    V second;
};

template <typename Key, typename T, typename Compare = std::less<Key> CPP_BAD>
class map {
public:
    typedef Key key_type;
    typedef T mapped_type;
    typedef pair<const key_type, mapped_type> value_type;
    typedef Compare key_compare;

    class value_compare {
        friend class map;

    protected:
        Compare comp;
        value_compare(Compare c)
            : comp(c)
        {
        }

    public:
        typedef bool result_type;
        typedef value_type first_argument_type;
        typedef value_type second_argument_type;
        bool operator()(value_type const& lhs, value_type const& rhs) const
        {
            return comp(lhs.first, rhs.first);
        }
    };

    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef value_type* pointer;
    typedef value_type const* const_pointer;

private:
    typedef list<value_type> list_type;

public:
    typedef typename list_type::iterator iterator;
    typedef typename list_type::const_iterator const_iterator;
    typedef typename list_type::reverse_iterator reverse_iterator;
    typedef typename list_type::const_reverse_iterator const_reverse_iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    explicit map(const key_compare& comp = key_compare())
    {
        (void)comp;
    }

    template <typename InputIterator>
    map(InputIterator first, InputIterator last, key_compare const& comp = key_compare())
    {
        (void)comp;
        insert(first, last);
    }

    map(map const& x)
    {
        insert(x.begin(), x.end());
    }

    map& operator=(map const& x)
    {
        if (this == &x) {
            return *this;
        }
        clear();
        insert(x.begin(), x.end());
        return *this;
    }

    iterator begin() { return _list.begin(); }
    const_iterator begin() const { return _list.begin(); }
    iterator end() { return _list.end(); }
    const_iterator end() const { return _list.end(); }
    reverse_iterator rbegin() { return _list.rbegin(); }
    const_reverse_iterator rbegin() const { return _list.rbegin(); }
    reverse_iterator rend() { return _list.rend(); }
    const_reverse_iterator rend() const { return _list.rend(); }

    bool empty() const
    {
        return _list.empty();
    }

    size_type size() const
    {
        return _list.size();
    }

    size_type max_size() const
    {
        return _list.max_size();
    }

    mapped_type& operator[](key_type const& k)
    {
        pair<iterator, bool> x = insert(value_type(k, mapped_type()));
        return x.first->second;
    }

    pair<iterator, bool> insert(value_type const& val)
    {
        iterator x = find(val.first);
        pair<iterator, bool> p;
        p.second = x == end();
        if (p.second) {
            p.first = _list.insert(end(), val);
            _list.sort(value_comp());
        } else {
            p.first = x;
        }
        return p;
    }

    iterator insert(iterator position, value_type const& val)
    {
        iterator x = find(val.first);
        if (x == end()) {
            x = _list.insert(position, val);
            _list.sort(value_comp());
        }
        return x;
    }

    template <typename InputIterator>
    void insert(InputIterator first, InputIterator last)
    {
        while (first != last) {
            insert(end(), *first);
            ++first;
        }
        _list.sort(value_comp());
    }

    void erase(iterator position)
    {
        _list.erase(position);
    }

    size_type erase(key_type const& k)
    {
        iterator x = find(k);
        if (x == end()) {
            return 0;
        }
        _list.erase(x);
        return 1;
    }

    void erase(iterator first, iterator last)
    {
        while (first != last) {
            first = erase(first);
        }
    }

    void swap(map& x)
    {
        _list.swap(x._list);
    }

    void clear()
    {
        _list.clear();
    }

    key_compare key_comp() const { return key_compare(); }
    value_compare value_comp() const { return value_compare(key_comp()); }

    iterator find(key_type const& k)
    {
        iterator it = begin();
        for (; it != end(); ++it) {
            if (it->first == k) {
                break;
            }
        }
        return it;
    }

    const_iterator find(key_type const& k) const
    {
        const_iterator it = begin();
        for (; it != end(); ++it) {
            if (it->first == k) {
                break;
            }
        }
        return it;
    }

    size_type count(key_type& k) const
    {
        return find(k) == end() ? 0 : 1;
    }

    iterator lower_bound(key_type const& k)
    {
        iterator x = begin();
        while (x != end()) {
            if (!(key_comp()(x->first, k))) {
                break;
            }
            ++x;
        }
        return x;
    }

    const_iterator lower_bound(key_type const& k) const
    {
        const_iterator x = begin();
        while (x != end()) {
            if (!(key_comp()(x->first, k))) {
                break;
            }
            ++x;
        }
        return x;
    }

    iterator upper_bound(key_type const& k)
    {
        iterator x = begin();
        while (x != end()) {
            if (key_comp()(k, x->first)) {
                break;
            }
            ++x;
        }
        return x;
    }

    const_iterator upper_bound(key_type const& k) const
    {
        const_iterator x = begin();
        while (x != end()) {
            if (key_comp()(k, x->first)) {
                break;
            }
            ++x;
        }
        return x;
    }

    pair<const_iterator, const_iterator> equal_range(key_type const& k) const
    {
        return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
    }

    pair<iterator, iterator> equal_range(key_type const& k)
    {
        return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
    }

    friend bool operator==(map const& lhs, map const& rhs) { return lhs._list == rhs._list; }
    friend bool operator!=(map const& lhs, map const& rhs) { return lhs._list != rhs._list; }
    friend bool operator<(map const& lhs, map const& rhs) { return lhs._list < rhs._list; }
    friend bool operator<=(map const& lhs, map const& rhs) { return lhs._list <= rhs._list; }
    friend bool operator>(map const& lhs, map const& rhs) { return lhs._list > rhs._list; }
    friend bool operator>=(map const& lhs, map const& rhs) { return lhs._list >= rhs._list; }

private:
    list<value_type> _list;
};

}

#endif //FT_CONTAINERS_MAP_HPP
