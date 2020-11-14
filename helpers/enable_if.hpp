//
// Created by boat on 11/9/20.
//

#ifndef FT_CONTAINERS_ENABLE_IF_HPP
#define FT_CONTAINERS_ENABLE_IF_HPP

template <bool _t, typename _u = void>
struct enable_if {
};

template <typename T>
struct enable_if<true, T> {
    typedef T type;
};

#endif //FT_CONTAINERS_ENABLE_IF_HPP
