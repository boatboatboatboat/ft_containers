//
// Created by boat on 11/18/20.
//

#ifndef FT_CONTAINERS_NEWERLIST_HPP
#define FT_CONTAINERS_NEWERLIST_HPP

namespace ft {

class AbstractNode {
public:
    virtual ~AbstractNode() { }

private:
};

class HeadNode : public AbstractNode {
public:
    HeadNode();

    AbstractNode* next() const
    {
        return _next;
    }

private:
    AbstractNode* _next;
};

class TailNode : public AbstractNode {
public:
    TailNode();
    AbstractNode* prev() const
    {
        return _prev;
    }

private:
    AbstractNode* _prev;
};

template <typename T>
class ValueNode : public AbstractNode {
public:
    ValueNode(T inner)
        : _inner(inner)
    {
    }
    AbstractNode* prev() const { return _prev; }
    AbstractNode* next() const { return _next; }

private:
    T _inner;
    AbstractNode* _prev;
    AbstractNode* _next;
};

template <typename T>
class InnerList {
public:
private:
};

template <typename T>
class InnerListIterator {
public:
    typedef InnerList<T> list_type;

private:
    AbstractNode* _current_node;
    list_type* _parent;
};

}

#endif //FT_CONTAINERS_NEWERLIST_HPP
