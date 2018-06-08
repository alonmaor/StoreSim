// Queue.hpp

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "DoublyLinkedList.hpp"



template <typename ValueType>
class Queue : private DoublyLinkedList<ValueType>
{
public:
    void enqueue(const ValueType& value);

    void dequeue();
    
    const ValueType& front() const;
    
    using DoublyLinkedList<ValueType>::isEmpty;
    using DoublyLinkedList<ValueType>::size;

    using DoublyLinkedList<ValueType>::constIterator;
    using ConstIterator = typename DoublyLinkedList<ValueType>::ConstIterator;
};



template <typename ValueType>
void Queue<ValueType>::enqueue(const ValueType& value)
{
    this->addToEnd(value);
}


template <typename ValueType>
void Queue<ValueType>::dequeue()
{
    this->removeFromStart();
}


template <typename ValueType>
const ValueType& Queue<ValueType>::front() const
{
    return this->first();
}



#endif

