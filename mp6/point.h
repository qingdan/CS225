/**
 * @file point.h
 * Definition of a Point class for k dimensional points.
 *
 * @author Matt Sachtler
 * @date Spring 2009
 */

#ifndef __POINT_H__
#define __POINT_H__

#include <cstdarg>
#include <iostream>
#include <stdexcept>

using std::out_of_range;
using std::cout;
using std::endl;

/**
 * Point class: represents a point in Dim dimensional space.
 *
 * @author Matt Sachtler
 * @date Spring 2009
 */
template<int Dim>
class Point
{
	public:
		static bool enable_mines;

	private:
		double vals[Dim];
		bool am_mine;

	public:
		Point();

		Point(double arr[Dim]);
		Point(double arr[Dim], bool mine);
		template <typename T>
		explicit Point(T x, ...);
		template <typename T>
		explicit Point(T x0, T x1, T x2);

		/**
		 * Gets the value of the Point object in the given dimension
		 * (index). This function is const so we don't modify Points using
		 * this function.
		 *
		 * @param index The dimension of the Point to grab.
		 * @return The value of the Point in the indexth dimension.
		 */
		double operator[](int index) const;

		/**
		 * Gets the value of the Point object in the given dimension
		 * (index). This is the non-const version, so it can be used to
		 * modify Points like so:
		 *
		 *     Point<3> a(1, 2, 3);
		 *     a[0] = 4; // a is now (4, 2, 3)
		 *
		 * @param index The dimension of the Point to grab.
		 * @return The value of the Point in the indexth dimension, by
		 *	reference (so that it may be modified).
		 */
		double & operator[](int index);

		bool operator==(const Point<Dim> p) const;
		bool operator!=(const Point<Dim> p) const;

		/**
		 * Compares whether the given Point is smaller than the current
		 * Point.
		 *
		 * @param p The other point to compare with.
		 * @return A boolean value indicating whether the current Point is
		 *  smaller than the provided Point p.
		 */
		bool operator<(const Point<Dim> p) const;

		bool operator<=(const Point<Dim> p) const;
		bool operator>(const Point<Dim> p) const;
		bool operator>=(const Point<Dim> p) const;

		void set(int index, double val);
		bool is_mine() { return am_mine; }

		void print(std::ostream & out = std::cout) const;
};

template<int Dim>
std::ostream & operator<<(std::ostream & out, const Point<Dim> & p);

#include "point.cpp"

#endif
