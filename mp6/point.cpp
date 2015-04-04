/* point.cpp
	Implementation of Point class

	Written by Matt Sachtler for CS225 MP6
	Spring 2009
	Revision history:
		3/21/2009		Created
*/

template<int Dim>
bool Point<Dim>::enable_mines = false;

/* Point constructor. Initializes everything to 0.
 */
template<int Dim>
Point<Dim>::Point()
	: am_mine(false)
{
	for(int i = 0; i < Dim; ++i)
		vals[i] = 0;
}

/* Point constructor
	Copy the array of points in
*/
template<int Dim>
Point<Dim>::Point(double arr[Dim])
	: am_mine(false)
{
	for(int i = 0; i < Dim; ++i)
		vals[i] = arr[i];
}

/* Point constructor
	Copy the array of points in
	set mine flag
*/
template<int Dim>
Point<Dim>::Point(double arr[Dim], bool mine)
	: am_mine(mine)
{
	for(int i = 0; i < Dim; ++i)
		vals[i] = arr[i];
}

template<int Dim>
template <typename T>
Point<Dim>::Point(T x0, T x1, T x2)
	: am_mine(false)
{
	vals[0] = x0;
	vals[1] = x1;
	vals[2] = x2;
}

template<int Dim>
template <typename T>
Point<Dim>::Point(T x, ...)
	: am_mine(false)
{
	vals[0] = x;
	va_list ap;
	va_start(ap, x);
	for (int i = 1; i < Dim; i++)
		vals[i] = va_arg(ap, T);
	va_end(ap);
}

template<int Dim>
double Point<Dim>::operator[](int index) const
{
	if (enable_mines && am_mine)
		cout << "Hit mine " << *this << endl;

	if (index >= Dim)
	{
		out_of_range e("Point index out of range");
		throw e;
	}
	return vals[index];
}

template<int Dim>
double & Point<Dim>::operator[](int index)
{
	if (enable_mines && am_mine)
		cout << "Hit mine " << *this << endl;

	if (index >= Dim)
	{
		out_of_range e("Point index out of range");
		throw e;
	}
	return vals[index];
}

template<int Dim>
void Point<Dim>::set(int index, double val)
{
	if (index >= Dim)
	{
		out_of_range e("Point index out of range");
		throw e;
	}
	vals[index] = val;
}

template<int Dim>
void Point<Dim>::print(std::ostream & out /* = cout */) const
{
	out << (am_mine ? '{' : '(');

	for (int i = 0; i < Dim - 1; ++i)
		out << vals[i] << ", ";
	out << vals[Dim - 1];
	
	out << (am_mine ? '}' : ')');
}

template<int Dim>
std::ostream & operator<<(std::ostream & out, const Point<Dim> & p)
{
	p.print(out);
	return out;
}

template<int Dim>
bool Point<Dim>::operator==(const Point<Dim> p) const
{
	return !(*this != p);
}

template<int Dim>
bool Point<Dim>::operator!=(const Point<Dim> p) const
{
	bool eq = true;
	for(int i = 0; i < Dim; ++i)
		eq &= (vals[i] == p.vals[i]);
	return !eq;
}

template<int Dim>
bool Point<Dim>::operator<(const Point<Dim> p) const
{
	bool less = false;
	for(int i = 0; i < Dim; ++i){
		less = vals[i] < p[i];
		if(vals[i] != p[i])
			break;
	}
	return less;
}

template<int Dim>
bool Point<Dim>::operator<=(const Point<Dim> p) const
{
	return (*this < p) || (*this == p);
}

template<int Dim>
bool Point<Dim>::operator>(const Point<Dim> p) const
{
	return !(*this < p);
}

template<int Dim>
bool Point<Dim>::operator>=(const Point<Dim> p) const
{
	return (*this > p) || (*this == p);
}


