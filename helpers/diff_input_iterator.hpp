//
// Created by boat on 11/13/20.
//

#ifndef FT_CONTAINERS_DIFF_INPUT_ITERATOR_HPP
#define FT_CONTAINERS_DIFF_INPUT_ITERATOR_HPP

namespace ft {
    template <typename Iter>
    typename Iter::difference_type diff_input_iterator(Iter first, Iter last) {
        typename Iter::difference_type n = 0;
        while (first != last) {
            first++;
            n += 1;
        }
        return n;
    }
}

#endif //FT_CONTAINERS_DIFF_INPUT_ITERATOR_HPP
