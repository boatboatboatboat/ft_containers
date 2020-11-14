//
// Created by boat on 10/31/20.
//

#ifndef FT_CONTAINERS_ITERATOR_IPP
#define FT_CONTAINERS_ITERATOR_IPP

#include "iterator.hpp"

namespace ft {

template <typename Iterator>
reverse_bd_iterator<Iterator>::reverse_bd_iterator()
    : _iterator(Iterator())
{
}

template <typename Iterator>
reverse_bd_iterator<Iterator>::reverse_bd_iterator(iterator_type iterator)
    : _iterator(iterator)
{
}

template <typename Iterator>
template <typename Iter>
reverse_bd_iterator<Iterator>::reverse_bd_iterator(reverse_bd_iterator<Iter> const& rev_it)
    : _iterator(rev_it._iterator)
{
}

template <typename Iterator>
template <typename Iter>
reverse_bd_iterator<Iterator>& reverse_bd_iterator<Iterator>::operator=(const reverse_bd_iterator<Iter>& rev_it)
{
    _iterator = rev_it._iterator;
    return *this;
}

template <typename Iterator>
reverse_bd_iterator<Iterator>::~reverse_bd_iterator()
{
}

template <typename Iterator>
typename reverse_bd_iterator<Iterator>::iterator_type reverse_bd_iterator<Iterator>::base() const
{
    return _iterator;
}

template <typename Iterator>
typename reverse_ra_iterator<Iterator>::self_type& reverse_ra_iterator<Iterator>::operator+=(ptrdiff_t n)
{
    _iterator -= n;
    return *this;
}

template <typename Iterator>
typename reverse_ra_iterator<Iterator>::self_type reverse_ra_iterator<Iterator>::operator+(ptrdiff_t n) const
{
    return _iterator - n;
}

template <typename Iterator>
typename reverse_ra_iterator<Iterator>::self_type& reverse_ra_iterator<Iterator>::operator-=(ptrdiff_t n)
{
    _iterator += n;
    return *this;
}

template <typename Iterator>
typename reverse_ra_iterator<Iterator>::self_type reverse_ra_iterator<Iterator>::operator-(ptrdiff_t n) const
{
    return _iterator + n;
}

template <typename Iterator>
typename reverse_ra_iterator<Iterator>::self_type reverse_ra_iterator<Iterator>::operator-(iterator_type other) const
{
    return this->_iterator + other._iterator;
}

template <typename Iterator>
typename reverse_ra_iterator<Iterator>::reference reverse_ra_iterator<Iterator>::operator[](ptrdiff_t n)
{
    return this->_iterator[n];
}

template <typename Iterator>
typename reverse_ra_iterator<Iterator>::const_reference reverse_ra_iterator<Iterator>::operator[](ptrdiff_t n) const
{
    return this->_iterator[n];
}

template <typename Iterator>
typename reverse_bd_iterator<Iterator>::reference reverse_bd_iterator<Iterator>::operator*()
{
    return *_iterator;
}

template <typename Iterator>
typename reverse_bd_iterator<Iterator>::const_reference reverse_bd_iterator<Iterator>::operator*() const
{
    return *_iterator;
}

template <typename Iterator>
typename reverse_bd_iterator<Iterator>::pointer_type reverse_bd_iterator<Iterator>::operator->()
{
    return _iterator;
}

template <typename Iterator>
typename reverse_bd_iterator<Iterator>::const_pointer_type reverse_bd_iterator<Iterator>::operator->() const
{
    return _iterator;
}

template <typename Iterator>
bool reverse_bd_iterator<Iterator>::operator==(const reverse_bd_iterator::self_type& other) const
{
    return _iterator == other._iterator;
}

template <typename Iterator>
bool reverse_bd_iterator<Iterator>::operator!=(const reverse_bd_iterator::self_type& other) const
{
    return !(*this == other);
}

template <typename Iterator>
bool reverse_ra_iterator<Iterator>::operator<(self_type const& rhs) const
{
    return _iterator >= rhs._iterator;
}

template <typename Iterator>
bool reverse_ra_iterator<Iterator>::operator>=(self_type const& rhs) const
{
    return !(*this < rhs);
}

template <typename Iterator>
bool reverse_ra_iterator<Iterator>::operator<=(self_type const& rhs) const
{
    return !(*this > rhs);
}

template <typename Iterator>
bool reverse_ra_iterator<Iterator>::operator>(const reverse_ra_iterator::self_type& rhs) const
{
    return rhs < *this;
}

template <typename Iterator>
typename reverse_bd_iterator<Iterator>::self_type reverse_bd_iterator<Iterator>::operator++(int)
{
    _iterator++;
    return *this;
}

template <typename Iterator>
typename reverse_bd_iterator<Iterator>::self_type& reverse_bd_iterator<Iterator>::operator++()
{
    reverse_bd_iterator<Iterator> old_type(*this);
    _iterator++;
    return old_type;
}

template <typename Iterator>
typename reverse_bd_iterator<Iterator>::self_type reverse_bd_iterator<Iterator>::operator--(int)
{
    _iterator--;
    return *this;
}

template <typename Iterator>
typename reverse_bd_iterator<Iterator>::self_type& reverse_bd_iterator<Iterator>::operator--()
{
    reverse_bd_iterator<Iterator> old_type(*this);
    _iterator--;
    return old_type;
}

}

#endif //FT_CONTAINERS_ITERATOR_IPP
