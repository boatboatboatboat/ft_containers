//
// Created by boat on 11/13/20.
//

#ifndef FT_CONTAINERS_HACKS_HPP
#define FT_CONTAINERS_HACKS_HPP

#include <stddef.h>

#define CPP98_IS_BAD(x, t) reinterpret_cast<x>(const_cast<typename deconst<typeof(t)>::type>(t))
#define CPP_BAD
#undef nullptr
#define nullptr NULL

template <typename T> struct deconst { typedef T type; };
template <typename T> struct deconst<T&> { typedef T& type; };
template <typename T> struct deconst<T*> { typedef T* type; };
template <typename T> struct deconst<T const> { typedef T type; };
template <typename T> struct deconst<T const&> { typedef T& type; };
template <typename T> struct deconst<T const*> { typedef T* type; };

#endif //FT_CONTAINERS_HACKS_HPP
