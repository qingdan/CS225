/**
 * @file binary_file_writer.cpp
 * Implementation of a binary file class for output operations.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#include <iostream>
#include "binary_file_writer.h"

using namespace std;

/**
 * Constructs a new BinaryFileWriter by opening the given filename.
 *
 * @param fileName File to be opened.
 */
BinaryFileWriter::BinaryFileWriter( const std::string & fileName ) : 
		file( fileName, ios::binary ), currentByte( '\0' ), currentBit( 7 ) {
	/* nothing */
}

BinaryFileWriter::~BinaryFileWriter() {
	close();
}

void BinaryFileWriter::close() {
	if( !file.is_open() )
		return;
	if( currentBit != 7 ) {
		char paddingBitsAsChar = static_cast<char>(currentBit + 1);
		// write out the last partial byte
		writeCurrentByte();
		currentByte = paddingBitsAsChar;
		writeCurrentByte();
	} else {
		// write out number of padding bits (0 in this case)
		currentByte = 0;
		writeCurrentByte();
	}
	file.close();
}

void BinaryFileWriter::writeBit( bool bit ) {
	currentByte = currentByte | (static_cast<char>(bit) << currentBit);
	--currentBit;
	if( currentBit == -1 )
		writeCurrentByte();
}

void BinaryFileWriter::writeByte( char byte ) {
	for( int i = 0; i < 8; ++i )
		writeBit( ( ( byte >> ( 7 - i ) ) & 1 ) == 1 );
}

void BinaryFileWriter::writeCurrentByte() {
	currentBit = 7;
	file.write( &currentByte, 1 );
	currentByte = '\0';
}
