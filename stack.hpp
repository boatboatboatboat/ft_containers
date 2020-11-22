//
// Created by boat on 11/9/20.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include "helpers/hacks.hpp"
#include "vector.hpp"

namespace ft {

template <typename T, typename Container = vector<T> CPP_BAD>
class stack {
public:
    typedef T value_type;
    typedef Container container_type;
    typedef typename Container::size_type size_type;

    explicit stack(container_type const& container = container_type())
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

    friend bool operator==(stack const& lhs, stack const& rhs)
    {
        return lhs._container == rhs._container;
    }
    friend bool operator!=(stack const& lhs, stack const& rhs)
    {
        return lhs._container != rhs._container;
    }
    friend bool operator<(stack const& lhs, stack const& rhs)
    {
        return lhs._container < rhs._container;
    }
    friend bool operator<=(stack const& lhs, stack const& rhs)
    {
        return lhs._container <= rhs._container;
    }
    friend bool operator>(stack const& lhs, stack const& rhs)
    {
        return lhs._container > rhs._container;
    }
    friend bool operator>=(stack const& lhs, stack const& rhs)
    {
        return lhs._container >= rhs._container;
    }

private:
    container_type _container;
};

}
#endif //FT_CONTAINERS_STACK_HPP
