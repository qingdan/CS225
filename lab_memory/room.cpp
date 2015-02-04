#include <iostream>
#include "room.h"

/**
 * Room Default Constructor
 * Creates a blank (uninitialized) room
 */
Room::Room()
    : capacity(0), count(0), max_letters(26), letters(NULL), letterCount(0)
{ }

/**
 * Main Room constructor
 * Creates an empty room with the given name and capacity
 */
Room::Room(const string & init_name, int init_capacity)
	: name(init_name), capacity(init_capacity), count(0), max_letters(26), letterCount(0)
{
	letters = new Letter[max_letters];
}

/**
 * Room copy constructor
 */
Room::Room(const Room & other)
{
	copy(other);
}

/**
 * Room assignment operator
 */
Room & Room::operator=(const Room & other)
{
	if (this != &other)
	{
		clear();
		copy(other);
	}
	return *this;
}

/**
 * Room destructor
 */
Room::~Room()
{
	clear();
}

/**
 * Allocates a letter group to this room
 */
void Room::addLetter(const Letter & L)
{
	letters[letterCount++] = L;
	count += L.count;
}

/**
 * Returns the number of empty seats remaining in the room after current
 * allocations
 */
int Room::spaceRemaining()
{
	return capacity - count;
}

/**
 * Outputs the room to cout
 */
void Room::print()
{
	cout << name << " (" << count << "/" << capacity << "):";
	for (int L = 0; L < letterCount; L++)
		cout << " " << letters[L].letter;
	cout << endl;
}

/**
 * Destructor/assignment operator clear helper function
 */
void Room::clear()
{
	if (letters != NULL)
		delete letters;
}

/**
 * Cctor/assignment operator copy helper function
 */
void Room::copy(const Room & other)
{
	name        = other.name;
	capacity    = other.capacity;
	count       = other.count;
	letterCount = other.letterCount;
	letters     = other.letters;
}

