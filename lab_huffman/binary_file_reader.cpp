/**
 * @file binary_file_reader.cpp
 * Implementation of a binary file class for input operations.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#include <iostream>
#include "binary_file_reader.h"

using namespace std;

BinaryFileReader::BinaryFileReader( const string & fileName ) : 
		file( fileName, ios::binary ),
		currentByte('\0'), currentBit(-1), numRead(0) {
	file.seekg( -1, ios::end );
	maxBytes = file.tellg();
	paddingBits = static_cast<int>( file.get() );
	file.seekg( 0, ios::beg );
}

BinaryFileReader::~BinaryFileReader() {
	close();
}

void BinaryFileReader::close() {
	if( file.is_open() )
		file.close();
}

bool BinaryFileReader::hasBits() const {
	return (numRead != maxBytes) || (currentBit >= paddingBits);
}

bool BinaryFileReader::hasBytes() const {
	return (numRead != maxBytes) || currentBit == 7;
}

bool BinaryFileReader::getNextBit() {
	if( needsNextByte() )
		readNextByte();
	bool ret = ((currentByte >> currentBit) & 1) == 1;
	--currentBit;
	return ret;
}

char BinaryFileReader::getNextByte() {
	char ret = 0;
	for( int currBit = 0; currBit < 8 && hasBits(); ++currBit )
		ret = ret | getNextBit() << (7 - currBit);
	return ret;
}

bool BinaryFileReader::needsNextByte() const {
	return currentBit == -1;
}

void BinaryFileReader::readNextByte() {
	// read a single byte
	file.read( &currentByte, 1 );
	currentBit = 7;
	++numRead;
}

void BinaryFileReader::reset() {
	file.seekg( 0, ios::beg );
	currentBit = -1;
	currentByte = '\0';
}
