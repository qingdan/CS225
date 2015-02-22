/**
 * @file list.cpp
 * Singly Linked List (lab_gdb).
 *
 * @author Chase Geigle
 * @date (created) Fall 2011
 * @date (modified) Spring 2012, Fall 2012
 *
 * @author Jack Toole
 * @date (modified) Fall 2011
 *
 * @author Veer Dedhia
 * @date (modified) Spring 2014
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List()
{
    clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear()
{
    // @todo Graded in lab_gdb
    // Write this function based on mp3
	
    /// @todo Graded in MP3.1
	ListNode* current = head;
	while(current != NULL)
	{
	ListNode* clear_prev;
	clear_prev = current;	
	current = current->next;
	delete clear_prev;
	}
	head = NULL;
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
	head = Insert_node;
	}
	else
	{
	Insert_node->next = NULL;
	head = Insert_node;
	}
	length++;
	Insert_node = NULL;
}

 /* Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
*/
template <class T>
void List<T>::insertBack( const T & ndata )
{
    // @todo Graded in lab_gdb
    // NOTE: Do not use this implementation for MP3!
    ListNode * temp = head;
    ListNode * temp2 = head;

    if (temp == NULL)
    {
        head = new ListNode(ndata);
	length = 1;
    }
    else
    {
        while (temp->next != NULL)
            temp = temp->next;
        temp2 = new ListNode(ndata);
	temp->next = temp2;
        length++;
    }
}


/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse()
{   if(head == NULL)
	return;
    ListNode * origin_head = head;
    head = reverse(head, NULL, length);
    origin_head->next = NULL;
}

/**
 * Helper function to recursively reverse the enitre sequence of
 * linked memory inside a List.
 *
 * @param curr The current node we are reversing
 * @param prev The node that should be placed before the current node in the
 * final reversed list
 * @param len The length of the remaining list to be reversed
 */
template <class T>
typename List<T>::ListNode* List<T>::reverse( ListNode * curr, ListNode * prev, int len )
{
    // @todo Graded in lab_gdb
    ListNode * temp;
    ListNode * beforeLast = head;
    while(beforeLast->next->next != NULL)
	beforeLast = beforeLast->next;
    if (len == 1)
    {
        curr->next = beforeLast;
	head = curr;
        return curr;
    }
    else
    {	
        prev = curr->next;
	temp = reverse(prev, prev->next, len-1);
        prev->next = curr;
	if(curr == beforeLast->next)
	curr->next = NULL;
        return temp;
    }
}

/**
 * Shuffles the current list by applying a perfect shuffle once. This entails
 * splitting the list in half, then interleaving the two halves.
 * For example:
 * start : < 1, 2, 3, 4, 5 >
 * split : < 1, 2, 3 >    < 4, 5 >
 * final : < 1, 4, 2, 5, 3 >
 */
template <class T>
void List<T>::shuffle()
{
    // @todo Graded in lab_gdb

    // Find the center, and split the list in half
    // one should point at the start of the first half-list
    // two should point at the start of the second half-list
    if(head == NULL)
	return;
    ListNode * one, * two, * prev, * temp;
    one = two = prev = temp = head;
    int i = 0;

    for (i = 0; i < length/2; i++)
    {
        prev = two;
        two = two->next;
    }
    if(i*2 != length)
    {
    prev = two;
    two = two->next;
    }
    prev->next = NULL;

    // interleave
    while (two->next != NULL)
    {
        temp = one->next;
        one->next = two;
        two = two->next;
        one->next->next = temp;
	one = temp;
    }
	if(i*2 != length)
	{
	temp = one->next;
	one->next = two;
	one->next->next = temp;
	temp->next = NULL;
	}
	else
	{
	temp->next = two;
	two->next = NULL;
	}	
}


