#include <iostream>
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    /// @todo Graded in MP3.1
	clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    /// @todo Graded in MP3.1
	ListNode* current = head;
	while(current != NULL)
	{
	ListNode* clear_prev;
	clear_prev = current;	
	current = current->next;
	delete clear_prev;
	}
	tail = NULL;
	length = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata)
{
    /// @todo Graded in MP3.1
	ListNode * Insert_node = new ListNode(ndata);
	if(head != NULL)
	{	
	Insert_node->next = head;
	head->prev = Insert_node;
	head = Insert_node;
	}
	else
	{
	Insert_node->prev = NULL;
	Insert_node->next = NULL;
	head = Insert_node;
	tail = head;
	}
	length++;
	Insert_node = NULL;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack( const T & ndata )
{
    /// @todo Graded in MP3.1
	ListNode * Insert_node = new ListNode(ndata);
	if(tail != NULL)
	{	
	Insert_node->prev = tail;
	tail->next = Insert_node;
	tail = Insert_node;
	}
	else
	{
	Insert_node->prev = NULL;
	Insert_node->next = NULL;
	head = Insert_node;
	tail = head;
	}
	length++;
	Insert_node = NULL;
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{   if (head == NULL||tail == NULL||head == tail)
	return;
    reverse(head, tail);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse( ListNode * & startPoint, ListNode * & endPoint )
{
    /// @todo Graded in MP3.1
    //first find the length of the reverse part
	if(startPoint == endPoint||startPoint == NULL || endPoint == NULL)
        return;
	ListNode * origin_start = startPoint;
	ListNode * origin_start_prev = startPoint->prev;
	ListNode * origin_end = endPoint;
	ListNode * origin_end_next = endPoint->next;
	while(startPoint != endPoint)
		{
		ListNode * temp = startPoint->prev;		
		startPoint->prev = startPoint->next;
		startPoint->next = temp;
		startPoint = startPoint->prev;
		}
	ListNode * temp = startPoint->prev;		
	startPoint->prev = origin_start_prev;
	startPoint->next = temp;
	endPoint = origin_start;
	endPoint->next = origin_end_next;
	if(origin_start_prev == NULL)
	//it starts from the head
		head = startPoint;
	else
		origin_start_prev->next = startPoint;
	if(origin_end_next == NULL)
	//it ends at the tail
		tail = endPoint;
	else
		origin_end_next->prev = endPoint;

}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth( int n )
{
    /// @todo Graded in MP3.1
	if (head == NULL)
	return;
	ListNode * startPoint = head;
	ListNode * endPoint = head;
	while(endPoint->next != NULL&&startPoint->next != NULL)
	{
		endPoint = startPoint;
		for(int i = 0; i < n-1; i++)
		{
		if(endPoint->next != NULL)		
		endPoint = endPoint->next;
		}
		reverse(startPoint, endPoint);
		startPoint = endPoint->next;
	}
	
}


/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall()
{
    /// @todo Graded in MP3.1
	if(head == NULL||head->next == NULL)
	return;
	ListNode* track = head;
	ListNode* hold = track->next;
	while(track->next->next != NULL&& track->next != NULL )
	{
	track = track->next;
	track->prev->next = track->next;
	track->next->prev = track->prev;
	hold = track->next;
	tail->next = track;
	track->prev = tail;
	track->next = NULL;
	tail = track;
	track = hold;
	}
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint)
{
    if (splitPoint > length)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head, splitPoint);

    int oldLength = length;
    if (secondHead == head)
    {
        // current list is going to be empty
        head = NULL;
        tail = NULL;
        length = 0;
    }
    else
    {
        // set up current list
        tail = head;
        while (tail->next != NULL)
            tail = tail->next;
        length = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head = secondHead;
    ret.tail = secondHead;
    if (ret.tail != NULL)
    {
        while (ret.tail->next != NULL)
            ret.tail = ret.tail->next;
    }
    ret.length = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
    /// @todo Graded in MP3.2
	if(start == NULL||splitPoint == 0)
	return start;
    	ListNode* newHead = head;
	for(int i = 0; i < splitPoint; i++)
	newHead = newHead->next;
	newHead->prev->next = NULL;
	newHead->prev = NULL;
	return newHead;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList)
{
    // set up the current list
    head = merge(head, otherList.head);
    tail = head;

    // make sure there is a node in the new list
    if(tail != NULL)
    {
        while (tail->next != NULL)
            tail = tail->next;
    }
    length = length + otherList.length;

    // empty out the parameter list
    otherList.head = NULL;
    otherList.tail = NULL;
    otherList.length = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second)
{
    /// @todo Graded in MP3.2
	if(first == NULL||second == NULL)
	return NULL;
	if(first == second)
	return first;
	ListNode * trackOfFirst = first;
	ListNode * trackOfSecond = second;
	ListNode * newHead = first;
	if(first->data < second->data)
	{
	trackOfFirst = first->next;
	}	
	else
	{
	newHead = second;
	trackOfSecond = second->next;
	}
	ListNode * trackOfResult = newHead;
	while(trackOfFirst != NULL&&trackOfSecond != NULL)
	{
	if(trackOfFirst->data < trackOfSecond->data||trackOfSecond == NULL)
	{
	trackOfResult->next = trackOfFirst;
	trackOfFirst->prev = trackOfResult;
	trackOfResult = trackOfFirst;
	trackOfFirst = trackOfFirst->next;
	}
	else
	{
	trackOfResult->next = trackOfSecond;
	trackOfSecond->prev = trackOfResult;
	trackOfResult = trackOfSecond;
	trackOfSecond = trackOfSecond->next;
	}
	}
	if(trackOfFirst == NULL)
	{
	trackOfResult->next = trackOfSecond;
	trackOfSecond->prev = trackOfResult; 
	}
	else
	{
	trackOfResult->next = trackOfFirst;
	trackOfFirst->prev = trackOfResult; 
	}
	second = NULL;
	return newHead;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort()
{
    if (empty())
        return;
    head = mergesort(head, length);
    tail = head;
    while (tail->next != NULL)
        tail = tail->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode * List<T>::mergesort(ListNode * start, int chainLength)
{
    /// @todo Graded in MP3.2
	ListNode * headForMergesort = start;
   	if (chainLength == 1)
	{start->next = start->prev = NULL;
	return start;}
	else
	{
	ListNode * secondStart = start;
	for(int i = 0; i < chainLength/2; i++)
		secondStart = secondStart->next;
	start = mergesort(start, chainLength/2);
	secondStart = mergesort(secondStart, chainLength-chainLength/2);
	headForMergesort = merge(start, secondStart);
	}
	return headForMergesort;
}
