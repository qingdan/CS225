/**
 * @file frequency.cpp
 * Implementation of the Frequency storage class.
 *
 * @author Chase Geigle
 * @date Summer 2012
 */

#include "frequency.h"

Frequency::Frequency( int freq ) : character( '\0' ), frequency( freq ) {
	// nothing
}

Frequency::Frequency( char c, int freq ) : character( c ), frequency( freq ) {
	// nothing
}

char Frequency::getCharacter() const {
	return character;
}

int Frequency::getFrequency() const {
	return frequency;
}

bool Frequency::operator<( const Frequency & other ) const {
	return frequency < other.frequency;
}
