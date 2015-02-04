#include "letter.h"

/**
 * Letter constructor. Initializes the letter to '-' with 0 students
 * The letter should be set by the client
 */
Letter::Letter()
	: letter('-'), count(0)
{ }

/**
 * Adds one additional student to the letter group
 */
void Letter::addStudent()
{
	count++;
}

/**
 * Comparator for letters (to allow for sorting)
 */
bool Letter::operator<(const Letter & other) const
{
	return count > other.count;
}
