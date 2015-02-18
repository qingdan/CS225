// Created by Jack Toole, Fall 2011
// Modified by Veer Dedhia, Spring 2014

// Iterator code, initially from C++ reference:
// http://www.cplusplus.com/reference/std/iterator/iterator/
class ListIterator : public std::iterator<std::forward_iterator_tag, T>
{
	ListNode* p;
	public:
	ListIterator() : p(NULL) { }
	ListIterator(ListNode * x) : p(x) { }
	ListIterator& operator++()   { p = p->next; return *this; } // Pre-Increment
	ListIterator operator++(int) { ListNode* r = p; p = p->next; return ListIterator(r); } // Post-Increment
	bool operator==(const ListIterator& rhs) { return p == rhs.p; }
	bool operator!=(const ListIterator& rhs) { return p != rhs.p; }
	const T & operator*() { return p->data; }
	const T * operator->() { return &(p->data); }
};
typedef ListIterator iterator;
typedef ListIterator const_iterator;

const_iterator         begin()  const { return ListIterator(head); }
const_iterator         end()    const { return ListIterator(NULL); }

// Iterator constructor
template <class Iter>
List(const Iter & start, const Iter & end);
