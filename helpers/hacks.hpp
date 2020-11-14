//
// Created by boat on 11/13/20.
//

#ifndef FT_CONTAINERS_HACKS_HPP
#define FT_CONTAINERS_HACKS_HPP

#define CPP98_IS_BAD(x, t) reinterpret_cast<x>(const_cast<typename deconst<typeof(t)>::type>(t))

template <typename T> struct deconst { typedef T type; };
template <typename T> struct deconst<T&> { typedef T& type; };
template <typename T> struct deconst<T*> { typedef T* type; };
template <typename T> struct deconst<T const> { typedef T type; };
template <typename T> struct deconst<T const&> { typedef T& type; };
template <typename T> struct deconst<T const*> { typedef T* type; };

#endif //FT_CONTAINERS_HACKS_HPP
