//
// wordscollection.cpp
//
//  Created on: Oct 26, 2016
//      Author: S. Miller
//
// Constructor
//	wordscollection( std::string& filename )
//     Precondition: Filename is a local file that EXISTS and is readable, file should be a text file
//     Postcondition: File is read into the objects queue for later processing
//
//	bool tokenizeFile( std::string& filename )
//     Precondition: Filename is a local file that EXISTS and is readable, file should be a text file
//     Postcondition: File is read into the objects queue for later processing
//
//	bool tokenizeFile( char * filename  )
//		Convenience function if you wanted to pass a hardcoded filename string (cstr) to tokenize, otherwise same as above
//     Precondition: Filename is a local file that EXISTS and is readable, file should be a text file
//     Postcondition: File is read into the objects queue for later processing
//
//	std::string getNextToken();
//     Precondition: WORD Tokens are STILL available in the queue
//     Postcondition: Next token is POPPED from QUEUE and returned
//
//	bool hasTokens() const;
//     Precondition: N/A
//     Postcondition: True if the WORD token queue is NOT empty
//

#include <fstream>
#include <stdexcept>
#include "wordscollection.h"

namespace FREQPROJ {

wordscollection::wordscollection( std::string& f) {
	tokenizeFile(f);
}

wordscollection::wordscollection( char * f) {
	std::string s(f);
	tokenizeFile( s );
}

bool wordscollection::tokenizeFile(std::string& filename) {
	std::string s,sWord;
	std::ifstream fin;

	fin.open( filename.c_str(), std::ifstream::in);
	if ( !fin.fail() ) {

		while ( fin ) {
			s = "";

			while ( fin && !isalpha(fin.peek())  )
				fin.ignore();

			if ( fin && isalpha(fin.peek()) ) {
				//fin.ignore();
				//Possible HTML Tagname, tagnames end in >, SPACE, [, or newline (carriage return too)
				while ( fin && isalpha(fin.peek()) )
					s += tolower(fin.get());

				//Got word
				words.push(s);

			}
		}

	} else {
		throw std::runtime_error("Unable to open/read file!");
	}
	fin.close();
	return true;
}

bool wordscollection::tokenizeFile( char * filename ) {
	std::string s(filename);
	return tokenizeFile( s );
}

std::string wordscollection::getNextToken() {
	if ( hasTokens() ) {
		std::string s = words.front();
		words.pop();
		return s;
	} else {
		throw std::runtime_error("Tokens underflow!");
	}
	return ""; //To appease the compiler
}

bool wordscollection::hasTokens() const {
	return !words.empty();
}


} /* namespace FREQPROJ */
