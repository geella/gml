#include <iostream>
#include <fstream>
#include <string>

#include <vector>

using namespace std;

class Tokenizer {

};

class Lexer {

};

class Parser {

};

bool isNumber( char value ) {
	return isdigit( value );
}

int main( ) {

	string source;
	ifstream file( "../main.qly" );

	if ( file.is_open( ) ) {
		for ( string line; getline( file, line ); ) {
			source += line + '\n';
		}
	}

	char space = ' ';
	char tab = '\t';
	char endline = '\n';
	char slash = '/';
	char singlequote = '\'';
	char doublequote = '\"';

	char leftparen = '(';
	char rightparen = ')';
	char leftsquare = '[';
	char rightsquare = ']';
	char leftcurly = '{';
	char rightcurly = '}';
	char lessthan = '<';
	char greaterthan = '>';
	char equal = '=';
	char plus = '+';
	char minus = '-';
	char asterisk = '*';
	char dot = '.';
	char comma = ',';
	char colon = ':';
	char semicolon = ';';

	vector < char > symbols = {
		leftparen, rightparen, leftsquare, rightsquare, leftcurly, rightcurly, lessthan, greaterthan, equal, plus, minus, asterisk, dot, comma, colon, semicolon
	};

	bool linecomment = true;
	bool multilinecomment = true;

	bool pass = true;
	bool singlepass = true;
	bool doublepass = true;
	vector < string > tokens;
	string token;
	string tmp;

	// REMOVE COMMENTS
	for ( int i = 0; i < source.length( ); i++ ) {
		// BACK CURRENT AND NEXT CHARACTER
		char back = source[ i-1 ], current = source[ i ], next = source[ i+1 ];

		// INLINE COMMNET
		if ( linecomment && multilinecomment && current == '/' && next == '/' ) { linecomment = false; }
		else if ( !linecomment && current == '\n' ) { linecomment = true; continue; }
		
		// MULTILINE COMMENT
		if ( multilinecomment && linecomment && current == '/' && next == '*' ) { multilinecomment = false; }
		else if ( !multilinecomment && current == '/' && back == '*' ) { multilinecomment = true; continue; }

		// AVOID IF IS COMMENT
		if ( !linecomment || !multilinecomment ) { continue; }

		// AVOID TABS AND NEWLINES
		if ( current == '\n' || current == '\t' ) { current = space; }

		tmp += current;
	}

	source = tmp;
	tmp = "";

	// APPEND SPACES BEETWEN SYMBOLS
	for ( int i = 0; i < source.length( ); i++ ) {
		// BACK CURRENT AND NEXT CHARACTER
		char back = source[ i-1 ], current = source[ i ], next = source[ i+1 ];

		// AVOID MULTIPLE SPACES
		if ( current == space && next == space ) { continue; }

		// APPEND TO
		tmp += current;

		// STRING WITH SYMBOLS || current == doublequote
		if ( current == singlequote ) { singlepass = !singlepass; }
		if ( current == doublequote ) { doublepass = !doublepass; }

		// AVOID IF IS STRING
		if ( !singlepass || !doublepass ) { continue; }

		// NUMBER WITH DOTS
		if ( isNumber( current ) && next == dot ) { continue; }
		else if ( current == dot && isNumber( next ) ) { continue; }

		for ( int j = 0; j < symbols.size( ); j++ ) {
			// SYMBOL CHARACTER
			char symbol = symbols[ j ];

			// APPEND SPACE NEXT TO SYMBOL
			if ( current != space && next == symbol || current == symbol && next != space ) { tmp += space; }
		}
		
	}

	source = tmp;

	for ( int i = 0; i < source.length( ); i++ ) {
		char back = source[ i-1 ], current = source[ i ], next = source[ i+1 ];

		if ( current == space && next == space ) { continue; }

		if ( current == space ) { tokens.push_back( token ); token = ""; continue; }

		token += current;

	}

	for ( int i = 0; i < tokens.size( ); i++ ) { cout << tokens[ i ] << endl; }

}
