//
// Created by boat on 11/9/20.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "vector.hpp"

namespace ft {

template <typename T, typename Container = vector<T>>
class stack {
public:
    typedef T value_type;
    typedef Container container_type;
    typedef size_t size_type;

    stack(container_type const& container = container_type())
        : _container(container)
    {
    }

    bool empty() const
    {
        return _container.empty();
    }

    size_type size() const
    {
        return _container.size();
    }

    value_type& top()
    {
        return _container.back();
    }

    value_type const& top() const
    {
        return _container.back();
    }

    void push(value_type const& val)
    {
        _container.push_back(val);
    }

    void pop()
    {
        _container.pop_back();
    }

    bool operator==(stack const& rhs) const
    {
        return _container == rhs._container;
    }

    bool operator!=(stack const& rhs) const
    {
        return _container != rhs._container;
    }

    bool operator<(stack const& rhs) const
    {
        return _container < rhs._container;
    }

    bool operator<=(stack const& rhs) const
    {
        return _container <= rhs._container;
    }

    bool operator>=(stack const& rhs) const
    {
        return _container >= rhs._container;
    }

    bool operator>(stack const& rhs) const
    {
        return _container > rhs._container;
    }

private:
    container_type _container;
};

}

#endif //FT_CONTAINERS_STACK_HPP
