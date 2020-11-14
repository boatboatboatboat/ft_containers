//
// Created by boat on 11/13/20.
//

#ifndef FT_CONTAINERS_TYPE_DEREFERENCE_HPP
#define FT_CONTAINERS_TYPE_DEREFERENCE_HPP

template <typename T>
struct type_dereference {
    typedef T type;
};
template <typename T>
struct type_dereference<T&> {
    typedef T type;
};
template <typename T>
struct type_dereference<T*> {
    typedef T type;
};

#endif //FT_CONTAINERS_TYPE_DEREFERENCE_HPP
