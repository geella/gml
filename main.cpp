#include <iostream>
#include <fstream>
#include <string>

#include <sstream>

using namespace std;

class Tokenizer {

};

class Lexer {

};

class Parser {

};

int main( ) {

	string source;
	ifstream file( "../main.qly" );

	if ( file.is_open( ) ) {
		for ( string line; getline( file, line ); ) {
			source += line;
		}
	}

	cout << source << endl;

	return 0;
}