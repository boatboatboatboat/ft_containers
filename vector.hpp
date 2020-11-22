//
// Created by boat on 10/31/20.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

#include "helpers/enable_if.hpp"
#include "helpers/is_iterator.hpp"
#include "iterator/iterator.hpp"
#include <cstddef>
#include <stdexcept>
#include <stdint.h>

namespace ft {

template <typename T>
class vector {
public:
    typedef T value_type;
    typedef T& reference;
    typedef T const& const_reference;
    typedef T* pointer;
    typedef T const* const_pointer;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef T* iterator;
    typedef T const* const_iterator;
    typedef reverse_ra_iterator<T*> reverse_iterator;
    typedef reverse_ra_iterator<T const*> const_reverse_iterator;

    /// Constructs an empty container, with no elements
    vector()
        : _data(NULL)
        , _size(0)
        , _capacity(0)
    {
    }

    /// Constructs a container with `n` elements.
    /// Each element is a copy of `val`.
    explicit vector(size_type n, value_type const& val = value_type())
        : _size(n)
        , _capacity(n)
    {
        _data = new value_type[_capacity];
        for (size_t idx = 0; idx < _size; idx += 1) {
            _data[idx] = val;
        }
    }

    /// Constructs a container with as many elements as the range [first,last),
    /// with each element constructed from its corresponding element in that range,
    /// in the same order.
    template <typename InputIterator>
    vector(InputIterator first, InputIterator last,
        typename enable_if<is_iterator<InputIterator>::dummy>::type* = 0)
    {
        while (first != last) {
            push_back(*first);
            first++;
        }
    }

    /// Constructs a container with a copy of each of the elements in x, in the same order.
    vector(vector const& x)
        : _size(x._size)
        , _capacity(x._capacity)
    {
        pointer new_data = new value_type[_capacity];
        for (size_t idx = 0; idx < _size; idx += 1) {
            new_data[idx] = x._data[idx];
        }
        _data = new_data;
    }

    /// Copies all the elements from x into the container.
    /// The container preserves its current allocator,
    /// which is used to allocate storage in case of reallocation.
    vector& operator=(vector const& x)
    {
        if (this == &x) {
            return *this;
        }
        delete[] _data;
        _size = x._size;
        _capacity = x._capacity;
        pointer new_data = new value_type[_capacity];
        for (size_t idx = 0; idx < _size; idx += 1) {
            new_data[idx] = x._data[idx];
        }
        _data = new_data;
        return *this;
    }

    /// This destroys all container elements,
    /// and deallocates all the storage capacity allocated by the vector using its allocator.
    ~vector()
    {
        delete[] _data;
    }

    // iterator methods

    iterator begin()
    {
        return this->_data;
    }

    const_iterator begin() const
    {
        return this->_data;
    }

    iterator end()
    {
        return this->_data + _size;
    }
    const_iterator end() const
    {
        return this->_data + _size;
    }

    reverse_iterator rbegin()
    {
        return reverse_iterator(end() - (_size != 0));
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end() - (_size != 0));
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin() - (_size != 0));
    }
    reverse_iterator rend()
    {
        return reverse_iterator(begin() - (_size != 0));
    }

    // capacity methods
    size_type size() const
    {
        return _size;
    }

    size_type max_size() const
    {
        return SIZE_MAX;
    }

    void resize(size_type n, value_type val = value_type())
    {
        reserve(n);
        for (size_t idx = _size; idx < n; idx += 1) {
            push_back(val);
        }
    }

    size_type capacity() const
    {
        return _capacity;
    }

    bool empty() const
    {
        return _size == 0;
    }

    void reserve(size_type n)
    {
        if (n > _capacity) {
            pointer new_data = new value_type[n];
            for (size_t idx = 0; idx < _size; idx += 1) {
                new_data[idx] = _data[idx];
            }
            delete[] _data;
            _data = new_data;
            _capacity = n;
        }
    }

    // element access methods
    reference operator[](size_type n)
    {
        return _data[n];
    }
    const_reference operator[](size_type n) const
    {
        return _data[n];
    }

    reference at(size_type n)
    {
        if (n >= _size) {
            throw std::out_of_range(__FUNCTION__);
        }
        return _data[n];
    }
    const_reference at(size_type n) const
    {
        if (n >= _size) {
            throw std::out_of_range(__FUNCTION__);
        }
        return _data[n];
    }

    reference front()
    {
        return _data[0];
    }
    const_reference front() const
    {
        return _data[0];
    }
    reference back()
    {
        return _data[_size - 1];
    }
    const_reference back() const
    {
        return _data[_size - 1];
    }

    // modifier methods

    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last,
        typename enable_if<is_iterator<InputIterator>::value>::type* = 0)
    {
        clear();
        for (; first != last; first++) {
            push_back(*first);
        }
    }

    void assign(size_type n, value_type const& val)
    {
        clear();
        for (; n > 0; n -= 1) {
            push_back(val);
        }
    }

    void push_back(value_type const& val)
    {
        ensure(1);
        _data[_size] = val;
        _size += 1;
    }

    void pop_back()
    {
        _size -= 1;
    }

private:
    void fuck_cpp_98(iterator position, ptrdiff_t shift)
    {
        if (shift > 0) {
            for (iterator x = end(); x >= position; x--) {
                x[shift] = x[0];
            }
        } else if (shift < 0) {
            for (; position != end(); position++) {
                position[0] = position[-shift];
            }
        }
    }
    void ensure(size_t n)
    {
        size_t min = _size + n;
        if (min > _capacity) {
            size_t x = _capacity ? _capacity : 8;
            while (min > x) {
                x *= 2;
            }
            reserve(x);
        }
    }

public:
    iterator insert(iterator position, value_type const& val)
    {
        if (position == end()) {
            push_back(val);
        } else {
            if ((_size + 1) == _capacity) {
                ensure(1);
            }
            fuck_cpp_98(position, 1);
            *position = val;
            _size += 1;
        }
        return ++position;
    }

    void insert(iterator position, size_type n, value_type const& val)
    {
        if (position == end()) {
            for (; n > 0; n -= 1) {
                push_back(val);
            }
        } else {
            if ((_size + n) == _capacity) {
                ensure(n);
            }
            fuck_cpp_98(position, n);
            for (size_t idx = 0; idx < n; idx += 1) {
                position[idx] = val;
            }
            _size += n;
        }
    }

    template <typename InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last,
        typename enable_if<is_iterator<InputIterator>::value>::type* = 0)
    {
        while (first != last) {
            insert(position, *first);
            position++;
            first++;
        }
    }

    iterator erase(iterator position)
    {
        fuck_cpp_98(position, -1);
        _size -= 1;
        return position;
    }

    iterator erase(iterator first, iterator last)
    {
        difference_type diff = last - first;
        fuck_cpp_98(first, -diff);
        _size -= last - first;
        return first;
    }

    void swap(vector& x)
    {
        pointer tdata = x._data;
        size_type tsize = x._size;
        size_type tcap = x._capacity;
        x._data = _data;
        x._size = _size;
        x._capacity = _capacity;
        _data = tdata;
        _size = tsize;
        _capacity = tcap;
    }

    void clear()
    {
        delete[] _data;
        _data = NULL;
        _size = 0;
        _capacity = 0;
    }

    friend bool operator==(vector const& lhs, vector const& rhs)
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

    friend bool operator!=(vector const& lhs, vector const& rhs) { return !(lhs == rhs); }

    friend bool operator<(vector const& lhs, vector const& rhs)
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

    friend bool operator>(vector const& lhs, vector const& rhs) { return rhs < lhs; }
    friend bool operator<=(vector const& lhs, vector const& rhs) { return !(lhs > rhs); }
    friend bool operator>=(vector const& lhs, vector const& rhs) { return !(lhs < rhs); }

private:
    pointer _data;
    size_type _size;
    size_type _capacity;
};

}

template <typename T>
void swap(ft::vector<T>& a, ft::vector<T>& b)
{
    a.swap(b);
}

#endif //FT_CONTAINERS_VECTOR_HPP
