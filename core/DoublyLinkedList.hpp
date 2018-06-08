#ifndef DOUBLYLINKEDLIST_HPP
#define DOUBLYLINKEDLIST_HPP

#include "EmptyException.hpp"
#include "IteratorException.hpp"


template <typename ValueType>
class DoublyLinkedList
{
public:
    class Iterator;
    class ConstIterator;

private:
    struct Node;


public:
    // Initializes this list to be empty.
    DoublyLinkedList() noexcept;

    // Initializes this list as a copy of an existing one.
    DoublyLinkedList(const DoublyLinkedList& list);

    // Initializes this list from an expiring one.
    DoublyLinkedList(DoublyLinkedList&& list) noexcept;


    // Destroys the contents of this list.
    virtual ~DoublyLinkedList() noexcept;


    // Replaces the contents of this list with a copy of the contents
    // of an existing one.
    DoublyLinkedList& operator=(const DoublyLinkedList& list);

    // Replaces the contents of this list with the contents of an
    // expiring one.
    DoublyLinkedList& operator=(DoublyLinkedList&& list) noexcept;


    // addToStart() adds a value to the start of the list, meaning that
    // it will now be the first value, with all subsequent elements still
    // being in the list (after the new value) in the same order.
    void addToStart(const ValueType& value);

    // addToEnd() adds a value to the end of the list, meaning that
    // it will now be the last value, with all subsequent elements still
    // being in the list (before the new value) in the same order.
    void addToEnd(const ValueType& value);


    // removeFromStart() removes a value from the start of the list, meaning
    // that the list will now contain all of the values *in the same order*
    // that it did before, *except* that the first one will be gone.
    // In the event that the list is empty, an EmptyException will be thrown.
    void removeFromStart();

    // removeFromEnd() removes a value from the end of the list, meaning
    // that the list will now contain all of the values *in the same order*
    // that it did before, *except* that the last one will be gone.
    // In the event that the list is empty, an EmptyException will be thrown.
    void removeFromEnd();


    // first() returns the value at the start of the list.  In the event that
    // the list is empty, an EmptyException will be thrown.  There are two
    // variants of this member function: one for a const DoublyLinkedList and
    // another for a non-const one.
    const ValueType& first() const;
    ValueType& first();


    // last() returns the value at the end of the list.  In the event that
    // the list is empty, an EmptyException will be thrown.  There are two
    // variants of this member function: one for a const DoublyLinkedList and
    // another for a non-const one.
    const ValueType& last() const;
    ValueType& last();


    // isEmpty() returns true if the list has no values in it, false
    // otherwise.
    bool isEmpty() const noexcept;


    // size() returns the number of values in the list.
    unsigned int size() const noexcept;

    Iterator iterator();

    ConstIterator constIterator() const;


public:
    class IteratorBase
    {
    public:
        // Initializes a newly-constructed IteratorBase to operate on
        // the given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        IteratorBase(const DoublyLinkedList& list) noexcept;


        // moveToNext() moves this iterator forward to the next value in
        // the list.  If the iterator is refrering to the last value, it
        // moves to the "past end" position.  If it is already at the
        // "past end" position, an IteratorException will be thrown.
        void moveToNext();


        // moveToPrevious() moves this iterator backward to the previous
        // value in the list.  If the iterator is refrering to the first
        // value, it moves to the "past start" position.  If it is already
        // at the "past start" position, an IteratorException will be thrown.
        void moveToPrevious();


        // isPastStart() returns true if this iterator is in the "past
        // start" position, false otherwise.
        bool isPastStart() const noexcept;


        // isPastEnd() returns true if this iterator is in the "past end"
        // position, false otherwise.
        bool isPastEnd() const noexcept;
    
    protected:
        Node* current;
        bool pastStart = false;
        bool pastEnd = false;
        DoublyLinkedList<ValueType>* plist;
    };


    class ConstIterator : public IteratorBase
    {
    public:
        // Initializes a newly-constructed ConstIterator to operate on
        // the given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        ConstIterator(const DoublyLinkedList& list) noexcept;


        // value() returns the value that the iterator is currently
        // referring to.  If the iterator is in the "past start" or
        // "past end" positions, an IteratorException will be thrown.
        const ValueType& value() const;
    };


    class Iterator : public IteratorBase
    {
    public:
        // Initializes a newly-constructed Iterator to operate on the
        // given list.  It will initially be referring to the first
        // value in the list, unless the list is empty, in which case
        // it will be considered to be both "past start" and "past end".
        Iterator(DoublyLinkedList& list) noexcept;


        // value() returns the value that the iterator is currently
        // referring to.  If the iterator is in the "past start" or
        // "past end" positions, an IteratorException will be thrown.
        ValueType& value() const;


        // insertBefore() inserts a new value into the list before
        // the one to which the iterator currently refers.  If the
        // iterator is in the "past start" position, an IteratorException
        // is thrown.
        void insertBefore(const ValueType& value);


        // insertAfter() inserts a new value into the list after
        // the one to which the iterator currently refers.  If the
        // iterator is in the "past end" position, an IteratorException
        // is thrown.
        void insertAfter(const ValueType& value);


        // remove() removes the value to which this iterator refers,
        // moving the iterator to refer to either the value after it
        // (if moveToNextAfterward is true) or before it (if
        // moveToNextAfterward is false).  If the iterator is in the
        // "past start" or "past end" position, an IteratorException
        // is thrown.
        void remove(bool moveToNextAfterward = true);
    };


private:
    // A structure that contains the vital parts of a Node in a
    // doubly-linked list, the value and two pointers: one pointing
    // to the previous node (or nullptr if there isn't one) and
    // one pointing to the next node (or nullptr if there isn't
    // one).
    struct Node
    {
        ValueType value;
        Node* prev = nullptr;
        Node* next = nullptr;
    };


    // You can feel free to add private member variables and member
    // functions here; there's a pretty good chance you'll need some.
    Node* head = nullptr;
    Node* tail = nullptr;
    int qSize = 0;
    void deleteList();
    void copyList(const DoublyLinkedList& list);
    void removeNode(Node* rmv_node);
};



template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList() noexcept
{
}


template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(const DoublyLinkedList& list)
{
    copyList(list);
}


template <typename ValueType>
DoublyLinkedList<ValueType>::DoublyLinkedList(DoublyLinkedList&& list) noexcept
{
	Node* tempT = tail;
	tail = list.tail;
	list.tail = tempT;

	Node* tempH = head;
	head = list.head;
	list.head = tempH;

	int tempQ = qSize;
	qSize = list.qSize;
	list.qSize = tempQ;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::~DoublyLinkedList() noexcept
{
	if (head != nullptr){
		while(head->next != nullptr){
			head = head->next;
			delete head->prev;
		}
		delete head;
	}
}


template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(const DoublyLinkedList& list)
{
	deleteList();
	copyList(list);
    return *this;
}


template <typename ValueType>
DoublyLinkedList<ValueType>& DoublyLinkedList<ValueType>::operator=(DoublyLinkedList&& list) noexcept
{
	Node* tempT = tail;
	tail = list.tail;
	list.tail = tempT;

	Node* tempH = head;
	head = list.head;
	list.head = tempH;

	int tempQ = qSize;
	qSize = list.qSize;
	list.qSize = tempQ;
    return *this;
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::addToStart(const ValueType& value)
{
	Node* nodePtr = nullptr;
	try{
		nodePtr = new Node;
		if (head == nullptr){
		head = nodePtr;
		tail = nodePtr;
		head->value = value;
		}
		else{
			head->prev = nodePtr;
			head->prev->value = value;
			head->prev->next = head;
			head = head->prev;
		}
		qSize++;
	}catch(...){
		delete nodePtr;
		throw;
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::addToEnd(const ValueType& value)
{
	Node *nodePtr = nullptr;
	try{
		nodePtr = new Node;
		if (tail == nullptr){
			head = nodePtr;
			tail = nodePtr;
			tail->value = value;
		}
		else{
			tail->next = nodePtr;
			tail->next->value = value;
			tail->next->prev = tail;
			tail = tail->next;
		}
		qSize++;
	}catch(...){
		delete nodePtr;
		throw;
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromStart()
{
	if (head != nullptr){
		if (head->next != nullptr){
			head = head->next;
			delete head->prev;
			head->prev = nullptr;
		}
		else{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		qSize--;
	}
	else{
		throw EmptyException();
	}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::removeFromEnd()
{
	if (tail != nullptr){
		if (tail->prev != nullptr){
			tail = tail->prev;
			delete tail->next;
			tail->next = nullptr;
		}
		else{
			delete tail;
			head = nullptr;
			tail = nullptr;
		}
		qSize--;
	}
	else{
		throw EmptyException();
	}
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::first() const
{
	if (head == nullptr)
		throw EmptyException();
	else
    	return head->value;
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::first()
{
	if (head == nullptr)
		throw EmptyException();
	else
    	return head->value;
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::last() const
{
	if (tail == nullptr)
		throw EmptyException();
	else
    	return tail->value;
}


template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::last()
{
	if (tail == nullptr)
		throw EmptyException();
	else
    	return tail->value;
}


template <typename ValueType>
unsigned int DoublyLinkedList<ValueType>::size() const noexcept
{
    return qSize;
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::isEmpty() const noexcept
{
    return qSize==0;
}


template <typename ValueType>
typename DoublyLinkedList<ValueType>::Iterator DoublyLinkedList<ValueType>::iterator()
{
    return Iterator{*this};
}


template <typename ValueType>
typename DoublyLinkedList<ValueType>::ConstIterator DoublyLinkedList<ValueType>::constIterator() const
{
    return ConstIterator{*this};
}


template <typename ValueType>
DoublyLinkedList<ValueType>::IteratorBase::IteratorBase(const DoublyLinkedList& list) noexcept
{
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToNext()
{
	if (this->isPastStart()){
		pastStart = false;
		current = current->next;
	}
	else if (this->isPastEnd()){
		throw IteratorException();
	}
	else{
		if (this->current->next == nullptr)
			pastEnd = true;
		else
			this->current = this->current->next;
	}

}


template <typename ValueType>
void DoublyLinkedList<ValueType>::IteratorBase::moveToPrevious()
{
	if (this->isPastEnd()){
		pastEnd = false;
		current = current->prev;
	}
	else if (this->isPastStart()){
		throw IteratorException();
	}
	else{
		if (current->prev == nullptr)
			pastStart = true;
		else
			current = current->prev;
	}
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::IteratorBase::isPastStart() const noexcept
{
    return pastStart;
}


template <typename ValueType>
bool DoublyLinkedList<ValueType>::IteratorBase::isPastEnd() const noexcept
{
    return pastEnd;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::ConstIterator::ConstIterator(const DoublyLinkedList& list) noexcept
    : IteratorBase{list}
{
	this->current = list.head;
	if (this->current == nullptr){
		this->pastStart = true;
		this->pastEnd = true;
	}
	else{
		this->pastStart = false;
		this->pastStart = false;
	}
}


template <typename ValueType>
const ValueType& DoublyLinkedList<ValueType>::ConstIterator::value() const
{
	if (this->isPastEnd() || this->isPastStart())
		throw IteratorException();
    return this->current->value;
}


template <typename ValueType>
DoublyLinkedList<ValueType>::Iterator::Iterator(DoublyLinkedList& list) noexcept
    : IteratorBase{list}
{
	this->current = list.head;
	if (this->current == nullptr){
		this->pastStart = true;
		this->pastEnd = true;
	}
	else{
		this->pastStart = false;
		this->pastStart = false;
	}
}



template <typename ValueType>
ValueType& DoublyLinkedList<ValueType>::Iterator::value() const
{
	if (this->isPastEnd() || this->isPastStart())
		throw IteratorException();
    return this->current->value;
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertBefore(const ValueType& value)
{
	if (this->isPastStart())
		throw IteratorException();
	else if (this->current->prev == nullptr){
		this->plist->addToStart(value);
	}
	else{
		Node* nodePtr = nullptr;
		try{
			nodePtr = new Node;
		}
		catch(...){
			delete nodePtr;
			throw;
		}
		this->current->prev->next = nodePtr;
		this->current->prev->next->next = this->current;
		this->current->prev->next->prev = this->current->prev;
		this->current->prev = this->current->prev->next;
		this->current->prev->value = value;
		this->plist->qSize++;
		}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::insertAfter(const ValueType& value)
{
	if (this->isPastEnd())
		throw IteratorException();
	else if (this->current->next == nullptr){
		this->plist->addToEnd(value);
	}
	else{
		this->current->next->prev = new Node;
		this->current->next->prev->prev = this->current;
		this->current->next->prev->next = this->current->next;
		this->current->next = this->current->next->prev;
		this->current->next->value = value;
		this->plist->qSize++;
		}
}


template <typename ValueType>
void DoublyLinkedList<ValueType>::Iterator::remove(bool moveToNextAfterward)
{
	if (this->current == nullptr)
		throw IteratorException();
	else if (this->current->next == nullptr){
		this->plist->removeNode(this->current);
		this->current = this->plist->tail;
	}
	else if (this->current->prev == nullptr){
		this->plist->removeNode(this->current);
		this->current = this->plist->head;
	}
	else{
		if (moveToNextAfterward){
			this->current = this->current->next;
			this->current->prev = this->current->prev->prev;
			delete this->current->prev->next;
			this->current->prev->next = this->current;
		}
		else{
			this->current = this->current->prev;
			this->current->next = this->current->next->next;
			delete this->current->next->prev;
			this->current->next->prev = this->current;
		}
	}
}

template <typename ValueType>
void DoublyLinkedList<ValueType>::deleteList(){
	while(head->next != nullptr){
		head = head->next;
		delete head->prev;
	}
	delete head;
}

template <typename ValueType>
void DoublyLinkedList<ValueType>::copyList(const DoublyLinkedList& list){
	if (list.head != nullptr){
		try{
	        head = new Node;
	        head->value = list.head->value;
	    }catch(...){
	        throw;
	    }
	    Node* curr1 = list.head->next;
	    Node* curr2 = head;
	    while(curr1 != nullptr){
	        try{
	            curr2->next = new Node;
	            curr2->next->value = curr1->value;
	            curr2->next->prev = curr2;

	        }catch(...) {
	            throw;
	        }
	        curr1 = curr1->next;
	        curr2 = curr2->next;
	    }
	    tail = curr2;
	    qSize = list.qSize;
	}
}

template <typename ValueType>
void DoublyLinkedList<ValueType>::removeNode(Node* rmv_node){
	delete rmv_node;
	qSize--;
}

#endif

