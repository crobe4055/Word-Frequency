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
#ifndef WORDSCOLLECTION_H_
#define WORDSCOLLECTION_H_

#include <string>
#include <queue>

namespace FREQPROJ {


class wordscollection {
public:
	wordscollection() {
		//Empty queue
		words = std::queue<std::string>();
	}

	wordscollection( std::string& );

	wordscollection( char * );

	~wordscollection() {
		//words queue will be destroyed by queue destructor
	}

	bool tokenizeFile( std::string& );

	bool tokenizeFile( char * );

	std::string getNextToken();

	bool hasTokens() const;
private:
	std::queue<std::string> words;
};

} /* namespace FREQPROJ */

#endif /* WORDSCOLLECTION_H_ */
