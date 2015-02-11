/**
 * @file list_given.cpp
 * Doubly Linked List (MP 3), given functions.
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

// These are given functions---you do not need to (and should not!) modify them

template <class T>
List<T>::List()
	: head(NULL), tail(NULL), length(0)
{ /* nothing */ }

template <class T>
int List<T>::size() const
{
	return length;
}

template <class T>
List<T>::List(List<T> const & other)
{
	copy(other);
}

template <class T>
List<T> & List<T>::operator=(List<T> const & rhs)
{
	if (this != &rhs)
	{
		clear();
		copy(rhs);
	}
	return *this;
}

template <class T>
bool List<T>::empty() const {
	return head == NULL && tail == NULL && length == 0;
}

template <class T>
void List<T>::copy(List<T> const & other) {
	// set up the default, empty list
	head = NULL;
	tail = NULL;
	length = 0;

	// if we have things to copy
	if (!other.empty())  {
		ListNode * curr = other.head;
		ListNode * prev = NULL;
		// iterate down the parameter list
		while (curr != NULL)  {
			ListNode * node = new ListNode(curr->data);

			// set the head of the new list
			if (head == NULL) 
				head = node;

			// correct pointer of the previous node if it exists
			if (prev != NULL) 
				prev->next = node;
			
			node->prev = prev;

			prev = node;
			curr = curr->next;
		}

		// prev will contain our new tail---set it up accordingly
		tail = prev;
		tail->next = NULL;

		length = other.length;
	}
}

template <class T>
void List<T>::print(ostream & os) const
{
	os << "<";
	ListNode * curr = head;
	while (curr != NULL) {
		os << " " << curr->data;
		curr = curr->next;
	}
	os << " >";
}

// overloaded operator<<
template <class T>
ostream & operator<<(ostream & os, const List<T> & list)
{
	list.print(os);
	return os;
}

// ListNode constructors
template <class T>
List<T>::ListNode::ListNode()
	: next(NULL), prev(NULL), data(T())
{ /* nothing */ }

template <class T>
List<T>::ListNode::ListNode(const T & ndata)
	: next(NULL), prev(NULL), data(ndata)
{ /* nothing */ }

template <class T>
template <class Iter>
List<T>::List(const Iter & begin_iterator, const Iter & end_iterator)
	: head(NULL), tail(NULL), length(0)
{
	for (Iter i = begin_iterator; i != end_iterator; ++i)
		insertBack(*i);
}
