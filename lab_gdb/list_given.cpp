/**
 * @file list_given.cpp
 * Singly Linked List (lab_gdb), given functions.
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 *
 * @author Veer Dedhia
 * @date (modified) Spring 2014
 */

// These are given functions---you do not need to (and should not!) modify them

template <class T>
List<T>::List()
	: head(NULL), length(0)
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
bool List<T>::empty() const
{
	return head == NULL && length == 0;
}

template <class T>
void List<T>::copy(List<T> const & other)
{
	// set up the default, empty list
	head = NULL;
	length = 0;

	// if we have things to copy
	if (!other.empty())
    {
		ListNode * curr = other.head->next;
        head = new ListNode(other.head->data);
        ListNode * me = head;
		length = other.length;

        while (curr != NULL)
        {
            me->next = new ListNode(curr->data);
            me = me->next;
            curr = curr->next;
        }
	}
}

template <class T>
void List<T>::print(ostream & os) const
{
	os << "<";
	ListNode * curr = head;
	while (curr != NULL)
    {
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
	: next(NULL), data(T())
{ /* nothing */ }

template <class T>
List<T>::ListNode::ListNode(const T & ndata)
	: next(NULL), data(ndata)
{ /* nothing */ }

template <class T>
template <class Iter>
List<T>::List(const Iter & begin_iterator, const Iter & end_iterator)
	: head(NULL), length(0)
{
	for (Iter i = begin_iterator; i != end_iterator; ++i)
		insertBack(*i);
}
