//
// Created by boat on 11/19/20.
//

#ifndef FT_CONTAINERS_SWAP_HPP
#define FT_CONTAINERS_SWAP_HPP

template <typename T>
void swap(T& a, T& b)
{
    T c(a);
    a = b;
    b = c;
}

#endif //FT_CONTAINERS_SWAP_HPP
