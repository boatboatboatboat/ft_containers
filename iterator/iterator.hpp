//
// Created by boat on 10/31/20.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include "../helpers/type_dereference.hpp"
#include <cstddef>

namespace ft {

template <typename Iterator>
class reverse_bd_iterator {
public:
    typedef Iterator iterator_type;
    typedef typename type_dereference<iterator_type>::type value_type;
    typedef value_type& reference;
    typedef value_type const& const_reference;
    typedef value_type* pointer_type;
    typedef value_type const* const_pointer_type;
    typedef reverse_bd_iterator<Iterator> self_type;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    iterator_type base() const
    {
        return _iterator;
    }

    reverse_bd_iterator()
        : _iterator(Iterator())
    {
    }
    explicit reverse_bd_iterator(iterator_type iterator)
        : _iterator(iterator)
    {
    }
    template <typename Iter>
    reverse_bd_iterator(reverse_bd_iterator<Iter> const& rev_it)
        : _iterator(rev_it.base())
    {
    }
    template <typename Iter>
    reverse_bd_iterator& operator=(reverse_bd_iterator<Iter> const& rev_it)
    {
        _iterator = rev_it.base();
        return *this;
    }

    bool operator==(self_type const& other) const
    {
        return _iterator == other._iterator;
    }
    bool operator!=(self_type const& other) const
    {
        return !(*this == other);
    }

    self_type& operator++()
    {
        _iterator--;
        return *this;
    }
    self_type operator++(int)
    {
        reverse_bd_iterator<Iterator> old_type(*this);
        _iterator--;
        return old_type;
    }
    self_type& operator--()
    {
        _iterator++;
        return *this;
    }
    self_type operator--(int)
    {
        reverse_bd_iterator<Iterator> old_type(*this);
        _iterator++;
        return old_type;
    }

    reference operator*() { return *_iterator; }
    const_reference operator*() const { return *_iterator; }
    pointer_type operator->() { return &*_iterator; }
    const_pointer_type operator->() const { return &*_iterator; }

protected:
    iterator_type _iterator;
};

template <typename Iterator>
class reverse_ra_iterator : public reverse_bd_iterator<Iterator> {
public:
    typedef Iterator iterator_type;
    typedef typename type_dereference<iterator_type>::type value_type;
    typedef typename reverse_bd_iterator<Iterator>::reference reference;
    typedef typename reverse_bd_iterator<Iterator>::const_reference const_reference;
    typedef typename reverse_bd_iterator<Iterator>::pointer_type pointer_type;
    typedef typename reverse_bd_iterator<Iterator>::const_pointer_type const_pointer_type;
    typedef reverse_ra_iterator<Iterator> self_type;
    typedef typename reverse_bd_iterator<Iterator>::difference_type difference_type;
    typedef typename reverse_bd_iterator<Iterator>::size_type size_type;

    reverse_ra_iterator()
        : reverse_bd_iterator<Iterator>(0)
    {
    }
    explicit reverse_ra_iterator(iterator_type iterator)
        : reverse_bd_iterator<Iterator>(iterator)
    {
    }
    template <typename Iter>
    reverse_ra_iterator(reverse_ra_iterator<Iter> const& rev_it)
        : reverse_bd_iterator<Iterator>(rev_it._iterator)
    {
    }
    template <typename Iter>
    reverse_ra_iterator& operator=(reverse_ra_iterator<Iter> const& rev_it)
    {
        reverse_bd_iterator<Iterator>::_iterator = rev_it._iterator;
    }
    ~reverse_ra_iterator()
    {
    }

    // comparators
    bool operator<(self_type const& rhs) const
    {
        return reverse_bd_iterator<Iterator>::_iterator >= rhs._iterator;
    }
    bool operator>(self_type const& rhs) const
    {
        return rhs < *this;
    }
    bool operator>=(self_type const& rhs) const
    {
        return !(*this < rhs);
    }
    bool operator<=(self_type const& rhs) const
    {
        return !(*this > rhs);
    }

    self_type& operator+=(difference_type n)
    {
        reverse_bd_iterator<Iterator>::_iterator -= n;
        return *this;
    }
    self_type operator+(difference_type n) const
    {
        return self_type(reverse_bd_iterator<Iterator>::_iterator - n);
    }
    self_type& operator-=(difference_type n)
    {
        reverse_bd_iterator<Iterator>::_iterator += n;
        return *this;
    }
    self_type operator-(difference_type n) const
    {
        return self_type(reverse_bd_iterator<Iterator>::_iterator + n);
    }
    self_type operator-(iterator_type other) const
    {
        return self_type(reverse_bd_iterator<Iterator>::_iterator + other.base());
    }
    reference operator[](difference_type n)
    {
        return reverse_bd_iterator<Iterator>::_iterator[-n];
    }
    const_reference operator[](difference_type n) const
    {
        return reverse_bd_iterator<Iterator>::_iterator[-n];
    }
};

}

#endif //FT_CONTAINERS_ITERATOR_HPP
