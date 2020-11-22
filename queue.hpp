//
// Created by boat on 11/20/20.
//

#ifndef FT_CONTAINERS_QUEUE_HPP
#define FT_CONTAINERS_QUEUE_HPP

#include "list.hpp"

namespace ft {
template <typename T, typename Container = list<T> CPP_BAD>
class queue {
public:
    typedef T value_type;
    typedef Container container_type;
    typedef typename container_type::size_type size_type;

    explicit queue(container_type const& ctnr = container_type())
        : _container(ctnr)
    {
    }

    bool empty() const { return _container.empty(); }
    size_type size() const { return _container.size(); }
    value_type& front() { return _container.front(); }
    value_type const& front() const { return _container.front(); }
    value_type& back() { return _container.back(); }
    value_type const& back() const { return _container.back(); }
    void push(value_type const& val) { _container.push_back(val); }
    void pop() { _container.pop_front(); }

    friend bool operator==(queue const& lhs, queue const& rhs)
    {
        return lhs._container == rhs._container;
    }
    friend bool operator!=(queue const& lhs, queue const& rhs)
    {
        return lhs._container != rhs._container;
    }
    friend bool operator<(queue const& lhs, queue const& rhs)
    {
        return lhs._container < rhs._container;
    }
    friend bool operator<=(queue const& lhs, queue const& rhs)
    {
        return lhs._container <= rhs._container;
    }
    friend bool operator>(queue const& lhs, queue const& rhs)
    {
        return lhs._container > rhs._container;
    }
    friend bool operator>=(queue const& lhs, queue const& rhs)
    {
        return lhs._container >= rhs._container;
    }

private:
    container_type _container;
};

}

#endif //FT_CONTAINERS_QUEUE_HPP
