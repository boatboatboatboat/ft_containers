//
// Created by Djevayo Pattij on 11/18/20.
//

#include "list.hpp"

namespace ft {

AbstractNode::~AbstractNode() { }

HeadNode::HeadNode(AbstractNode* next)
    : _next(next)
{
}

AbstractNode const* HeadNode::next() const
{
    return const_cast<AbstractNode const*>(_next);
}

AbstractNode*& HeadNode::next()
{
    return _next;
}

HeadNode::~HeadNode() { }

void HeadNode::insert_after(AbstractNode* node)
{
    TailNode* next_node = dynamic_cast<TailNode*>(_next);
    next_node->prev() = node;
    {
        HeadNode* active_node = dynamic_cast<HeadNode*>(node);
        active_node->next() = next_node;
    }
    {
        TailNode* active_node = dynamic_cast<TailNode*>(node);
        active_node->prev() = this;
    }
    _next = node;
}

TailNode::TailNode(AbstractNode* previous)
    : _prev(previous)
{
}

TailNode::~TailNode() { }

void TailNode::insert_before(AbstractNode* node)
{
    HeadNode* previous_node = dynamic_cast<HeadNode*>(_prev);
    previous_node->next() = node;
    {
        TailNode* active_node = dynamic_cast<TailNode*>(node);
        active_node->prev() = previous_node;
    }
    {
        HeadNode* active_node = dynamic_cast<HeadNode*>(node);
        active_node->next() = this;
    }
    _prev = node;
}

}
