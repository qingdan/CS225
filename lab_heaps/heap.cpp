/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const {
    /// @todo Update to return the index you are choosing to be your root.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the left child.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the right child.
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent( size_t currentIdx ) const {
    /// @todo Update to return the index of the parent.
    return 0;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild( size_t currentIdx ) const {
    /// @todo Update to return whether the given node has a child
    return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild( size_t currentIdx ) const {
    /// @todo Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    return 0;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown( size_t currentIdx ) {
    /// @todo Implement the heapifyDown algorithm.
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp( size_t currentIdx ) {
    if( currentIdx == root() )
        return;
    size_t parentIdx = parent( currentIdx );
    if( higherPriority( _elems[ currentIdx ], _elems[ parentIdx ] ) ) {
        std::swap( _elems[ currentIdx ], _elems[ parentIdx ] );
        heapifyUp( parentIdx );
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() {
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap( const std::vector<T> & elems ) {
    /// @todo Construct a heap using the buildHeap algorithm
}

template <class T, class Compare>
T heap<T, Compare>::pop() {
    /// @todo Remove, and return, the element with highest priority
    return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const {
    /// @todo Return, but do not remove, the element with highest priority
    return T();
}

template <class T, class Compare>
void heap<T, Compare>::push( const T & elem ) {
    /// @todo Add elem to the heap
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const {
    /// @todo Determine if the heap is empty
    return true;
}
