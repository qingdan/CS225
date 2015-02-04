#include <algorithm>
#include <vector>
#include <iostream>
#include <utility>

#include "allocator.h"
#include "fileio.h"

using namespace std;

/**
 * Allocator constructor
 */
Allocator::Allocator(const string & studentFile, const string & roomFile)
{
	createLetterGroups();
	loadStudents(studentFile);
	loadRooms(roomFile);
}

/**
 * Allocates the array of letters
 */
void Allocator::createLetterGroups()
{
	// Make letters (A - Z lettergroups)
	alpha = new Letter[26];
	for (int i = 0; i < 26; i++)
		alpha[i].letter = 'A' + i;
}

/**
 * Reads the students from the students file and places them in their letter
 * groups.
 */
void Allocator::loadStudents(const string & file)
{
	// Read in students
	fileio::loadStudents(file);
	studentCount = fileio::getNumStudents();

	for (int i = 0; i < studentCount; i++)
	{
		string name = fileio::nextStudent();
		char letter = name[0];
		int index = (int)letter - 'A';
		alpha[index].addStudent();
	}
}

/**
 * Reads rooms from the rooms file
 */
void Allocator::loadRooms(const string & file)
{
	// Read in rooms
	fileio::loadRooms(file);
	rooms = new Room[roomCount];

	totalCapacity = 0;
	int i = 0;
	while (fileio::areMoreRooms())
	{
		i++;
		rooms[i] = fileio::nextRoom();
		totalCapacity += rooms[i].capacity;
	}
}

void Allocator::printStudents()
{
	// Output number of each last letter name
	cout << "Student counts (" << studentCount << " total)" << endl;
	for (int i = 0; i < 26; i++)
		cout << alpha[i].letter << ": " << alpha[i].count << endl;
}

/**
 * Main allocation function
 * Allocates student letter groups to rooms
 */
void Allocator::allocate()
{
	// Perform the allocation
	int border = solve();

	// Check for an error
	if (border < 0)
	{
		cerr << endl << "Cannot allocate all students." << endl << endl;
		exit(-1);
	}
}

/**
 * Prints the rooms and their fullness
 */
void Allocator::printRooms()
{
	// Output the allocation
	cout << "Room Allocation (" << studentCount << "/" << totalCapacity << ")" << endl;
	for (int i = 0; i < roomCount; i++)
		rooms[i].print();
}

/**
 * Calculates the allocation
 */
int Allocator::solve()
{
	stable_sort(alpha, alpha + 26);
	
	for (int L = 0; L < 26; L++)
	{
		Room * r = largestOpening();
		r->addLetter(alpha[L]);
	}
	
	return minSpaceRemaining();
}

/**
 * Returns the amount of seats remaining in the room with the fewest
 * spare seats
 */
int Allocator::minSpaceRemaining()
{
	int border = 1000000;
	for (int i = 0; i < roomCount; i++)
		if (rooms[i].spaceRemaining() < border)
			border = rooms[i].spaceRemaining();
	return border;
}

/**
 * Return the room with the largest number of open seasts
 */
Room * Allocator::largestOpening()
{
	int index = 0;
	int max_remaining = 0;
	for (int i = 0; i < roomCount; i++)
	{
		if (rooms[i].spaceRemaining() > max_remaining)
		{
			index = i;
			max_remaining = rooms[i].spaceRemaining();
		}
	}
	return &rooms[index];
}
