/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
	if(curDim < Dim && curDim >= 0)
	{
		if(first[curDim]!=second[curDim])
			return first[curDim] < second[curDim];
		return first < second;
	}
	return false;
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
	int currDistance = getDistance(target, currentBest);
	int potenDistance = getDistance(target, potential);
	if(currDistance != potenDistance)
		return potenDistance < currDistance;
	return potential < currentBest;
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
	points = newPoints;
    buildTreeHelper(0, points.size()-1, 0);
}

template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
	int left = 0;
    int right = points.size() - 1;
    int minDis = 0;
    bool isFirst = true;
    Point<Dim> currentBest;
    findNearestHelper(query, currentBest, left, right, 0, minDis, isFirst);

    return currentBest;
}

template<int Dim>
int KDTree<Dim>::getDistance(const Point<Dim> & point1, const Point<Dim> & point2) const
{
    int distance = 0;
	for(int i = 0; i < Dim; i++)
		distance += (point1[i]-point2[i])*(point1[i]-point2[i]);
	return distance;
}


template<int Dim>
void KDTree<Dim>::buildTreeHelper(int left, int right, int dimension)
{
    int mindex;
    mindex = (left + right)/2;
    quickSelect(left, right, dimension, mindex);
    if(left < mindex - 1)
        buildTreeHelper(left, mindex - 1, (dimension + 1) % Dim);
    if(right > mindex + 1)
        buildTreeHelper(mindex + 1, right, (dimension + 1) % Dim);
}

template<int Dim>
void KDTree<Dim>::quickSelect(int left, int right, int dimension, int mid_index)
{
    if(left >= right)
        return;
    int pIndex = (left + right)/2;
    pIndex = partition(left, right, pIndex, dimension);
    if(mid_index == pIndex)
        return;
    else if(mid_index < pIndex)
        quickSelect(left, pIndex - 1, dimension, mid_index);
    else
        quickSelect(pIndex + 1, right, dimension, mid_index);
}

template<int Dim>
int KDTree<Dim>::partition(int left, int right, int pivotIndex, int dimension)
{
    Point<Dim> pivotValue = points[pivotIndex];
    std::swap(points[pivotIndex], points[right]);
    int storeIndex = left;
    for(int i = left; i < right; i++)
    {
        if(smallerDimVal(points[i], pivotValue, dimension))
        {
            std::swap(points[storeIndex], points[i]);
            storeIndex++;
        }
    }
    std::swap(points[right], points[storeIndex]);
    return storeIndex;
}

template<int Dim>
void KDTree<Dim>::findNearestHelper(const Point<Dim> & query, Point<Dim> & currentBest,
                                    int left, int right, int dimension, int minDis, bool & isFirst) const
{
      if(left >= right)
    {
        if(isFirst)
        {
            isFirst = false;
            currentBest = points[right];
        }
        else
        {
            if(shouldReplace(query, currentBest, points[left]))
                currentBest = points[left];
        }
        return;
    }
    int mid_index = (left + right)/2;
     if(smallerDimVal(query, points[mid_index], dimension))
    {
        findNearestHelper(query, currentBest, left, mid_index - 1, (dimension + 1)%Dim, minDis, isFirst);
        if(shouldReplace(query, currentBest, points[mid_index]))
            currentBest = points[mid_index];
        minDis = getDistance(currentBest, query);
        if((query[dimension] - points[mid_index][dimension]) * (query[dimension] - points[mid_index][dimension]) <= minDis)
            findNearestHelper(query, currentBest, mid_index + 1, right, (dimension + 1)%Dim, minDis, isFirst);
    }
    else
    {
        findNearestHelper(query, currentBest, mid_index + 1, right, (dimension + 1)%Dim, minDis, isFirst);
        if(shouldReplace(query, currentBest, points[mid_index]))
            currentBest = points[mid_index];
        minDis = getDistance(currentBest, query);
        if((query[dimension] - points[mid_index][dimension]) * (query[dimension] - points[mid_index][dimension]) <= minDis)
            findNearestHelper(query, currentBest, left, mid_index - 1, (dimension + 1)%Dim, minDis, isFirst);   
    }
    return;
}
