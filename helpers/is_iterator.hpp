//
// Created by boat on 11/9/20.
//

#ifndef FT_CONTAINERS_IS_ITERATOR_HPP
#define FT_CONTAINERS_IS_ITERATOR_HPP

template <typename T> struct is_iterator {};
template <typename T> struct is_iterator<T*> { static const bool value = true; };

#endif //FT_CONTAINERS_IS_ITERATOR_HPP
