#ifndef LIB_H
#define LIB_H

#include <string>
#include <iostream>
#include <vector>
#include <map>

#pragma GCC diagnostic ignored "-Wreturn-type"

// GCC OVER CLANG
// index to elements
// agregar length a string
// para array necesito saber el type
// operator ( ) for tuple unpack?

struct Var {
	double n;
	std::string s;
	bool b;
  std::string type = "undefined";
	std::map < Var, Var > container;
	std::vector < Var > index;
	int length = 0;
	Var( ) { }
	Var( int value ) : n( value ) { type = "number"; }
	Var( double value ) : n( value ) { type = "number"; }
	Var( const char* value ) : s( value ) { type = "string"; length = s.length( ); }
	Var( std::string value ) : s( value ) { type = "string"; length = s.length( ); }
	Var( bool value ) : b( value ) { type = "boolean"; }
	Var( std::initializer_list < Var > value ) {
		for ( auto i : value ) {
			index.push_back( i );
			container.insert( { length, i } );
			length += 1;
		}
	}
	Var( std::initializer_list < std::pair < Var, Var > > value ) {
		for ( auto [ k, v ] : value ) {
			index.push_back( k );
			container.insert( { k, v } );
			length += 1;
		}
	}
	Var& operator [ ] ( Var value ) {
		if ( type == "array" || type == "json" || type == "tuple" ) { return container[ value ]; }
	}
	// CONST MAP ONLY WORK WITH .AT( )
	Var operator [ ] ( Var value ) const {
		if ( type == "array" || type == "json" || type == "tuple" ) { return container.at( value ); }
	}
	Var& operator = ( int value ) {
		if ( type == "number" ) {
			n = value;
			return *this;
		}
		throw "OOOMMMGGG";
	}
	Var& operator = ( const char* value ) {
		if ( type == "string" ) {
			s = value;
		} else {
			throw "OOOMMMGGG";
		}
		return *this;
	}
	Var& operator = ( bool value ) {
		if ( type == "string" ) {
			b = value;
		} else {
			throw "OOOMMMGGG";
		}
		return *this;
	}
	Var& operator = ( Var value ) {
		if ( value.type == type ) {
			n = value.n;
			s = value.s;
			b = value.b;
			index = value.index;
			container = value.container;
		} else {
			throw "OOOMMMGGG";
		}
		return *this;
	}
	Var& operator ++ ( int ) { n++; }
	bool operator == ( const Var &other ) const {
		if ( type == "number" ) { return n == other.n; }
		else if ( type == "string" ) { return s == other.s; }
		else if ( type == "boolean" ) { return b == other.b; }
		else if ( type == "json" || type == "array" || type == "tuple" ) { return container == other.container; }
	}
	bool operator < ( const Var &other ) const {
		if ( type == "number" ) { return n < other.n; }
		else if ( type == "string" ) { return s < other.s; }
		else if ( type == "boolean" ) { return b < other.b; }
		else if ( type == "json" || type == "array" || type == "tuple" ) { return container < other.container; }
	}

	auto begin( ) { return index.begin( ); }
	auto end( ) { return index.end( ); }

	// STRING
	Var toLower( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		Var value = "";
		for ( char piece : s ) { value.s += tolower( piece ); }
		return value;
	}

	Var toUpper( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		Var value = "";
		for ( char piece : s ) { value.s += toupper( piece ); }
		return value;
	}

	Var toCapital( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		Var value = "";
		for ( char piece : s ) { value.s += tolower( piece ); }
		value.s[ 0 ] = toupper( value.s[ 0 ] );
		return value;
	}

	Var isLower( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		for ( char piece : s ) { if ( !islower( piece ) ) { return false; } }
		return true;
	}

	Var isUpper( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		for ( char piece : s ) { if ( !isupper( piece ) ) { return false; } }
		return true;
	}

	Var isCapital( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		for ( int i = 1; i < s.length( ); i++ ) { if ( !islower( s[ i ] ) ) { return false; } }
		if ( !isupper( s[ 0 ] ) ) { return false; }
		return true;
	}

	Var endsWith( Var value ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		int external = value.s.length( ) -1, internal = s.length( ) -1;
		if ( external > internal ) { return false; }
		for ( int i = external; i >= 0; i-- ) { if ( s[ internal ] != value.s[ external ] ) { return false; } external--; internal--; }
		return true;
	}

	Var startsWith( Var value ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		int external = value.s.length( ) -1, internal = s.length( ) -1;
		if ( external > internal ) { return false; }
		for ( int i = external; i <= 0; i++ ) { if ( s[ internal ] != value.s[ external ] ) { return false; } external++; internal++; }
		return true;
	}

	Var isNumeric( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		for ( int i = 0; i <= s.length( ); i++ ) { if ( !isdigit( s[ i ] ) )	{ return false; } }
		return true;
	}

	Var toNumber( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		for ( int i = 0; i < s.length( ); i++ ) { if ( !isdigit( s[ i ] ) ) { throw "OOOMMMGGG"; } }
		return atoi( s.c_str( ) );
	}

	Var replace( Var value, Var v ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		while ( true ) { int index = s.find( value.s );
			if ( index != -1 ) { s.replace( index, value.s.length( ), v.s ); }
			else { break; }
		}
		return s;	
	}

	Var contains( Var value ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		int index = s.find( value.s );
		if ( index == -1 ) { return false; };
		return true;	
	}

	std::vector < Var > split( Var value ) {
		if ( type != "string" && value.type == "string" ) { throw "OOOMMMGGG"; }
		std::string token;
		std::vector < Var > out;
		char delimiter = value.s[ 0 ];
		for ( int i = 0; i <= s.length( ); i++ ) {
			char back = s[ i-1 ], current = s[ i ], next = s[ i+1 ];
			//if ( current == ' ' && next == ' ' ) { continue; }
			if ( current == delimiter || i == s.length( ) ) { out.push_back( token ); token = ""; continue; }
			token += current;
		}
		return out;
	}

	// BOOLEAN
	Var& operator ! ( ) {
		if ( type != "boolean" ) { throw "OOOMMMGGG"; }
		if ( b == true ) { b = false; } else { b = true; }
		return *this;
	};

};

struct undefined : Var {
	undefined( ) { }
	undefined( Var value ) : Var( value ) { }
};

struct number : Var {
	number( int value ) : Var( value ) { }
	number( Var value ) {
		if ( value.type == "number" ) {
			type = value.type;
			n = value.n;
		} else {
			throw "OOOMMMGGG";
		}
	}
};

struct string : Var {
	string( const char* value ) : Var( value ) { }
	string( Var value ) {
		if ( value.type == "string" ) {
			type = value.type;
			s = value.s;
		} else {
			throw "OOOMMMGGG";
		}
	}
};

struct boolean : Var {
	boolean( bool value ) : Var( value ) { }
	boolean( Var value ) {
		if ( value.type == "boolean" ) {
			type = value.type;
			b = value.b;
		} else {
			throw "OOOMMMGGG";
		}
	}
};

template < typename TYPE >
struct json : Var {
	json( std::initializer_list < std::pair < Var, Var > > value ) : Var( value ) { type = "json"; }
};

template < typename TYPE >
struct array : Var {
	array( std::initializer_list < Var > value ) : Var( value ) { type = "array"; }
	array( std::vector < Var > value ) {
		type = "array";
		for ( auto i : value ) {
			index.push_back( i );
			container.insert( { length, i } );
			length += 1;
		}
	}
	array& operator = ( std::vector < Var > value ) {
		for ( auto i : value ) {
			index.push_back( i );
			container.insert( { length, i } );
			length += 1;
		}
		return *this;
	}

};

template < typename ... TYPES >
struct tuple : Var {
	tuple( TYPES ... args ) { 
		type = "tuple";
		( index.push_back( args ), ... );
		for ( auto i : index ) { container.insert( { length, i } ); length += 1; }
	}
};

struct {
	std::string y = "\033[93m", b = "\033[94m", g = "\033[32m", p = "\033[95m", e = "\033[0m";

	std::string number( int data ) {
		std::string value = std::to_string( data );
		return std::string( y + value + e );
	}

	std::string string( std::string data ) {
		return std::string( g + data + e );
	}

	std::string boolean( bool data ) {
		std::string value = ( data ) ? "true" : "false";
		return std::string( b + value + e );
	}

	std::string container( std::string data ) {
		return std::string( p + data + e );
	}

	std::string type( Var data ) {
		std::string value;
		if ( data.type == "number" ) {
			value = number( data.n );
		} else if ( data.type == "string" ) {
			value = string( data.s );
		} else if ( data.type == "boolean" ) {
			value = boolean( data.b );
		} else {
			value = container( data.type );
		}
		return value;
	}

	template < typename ... TYPES >
	void log( TYPES ... args ) { 
		std::vector < Var > data;
		( data.push_back( args ), ... );
		std::cout << type( data[ 0 ] );
		for ( int i = 1; i < data.size( ); i++ ) {
			std::cout << " \b " << type( data[ i ] );
		}
		std::cout << std::endl;
	}

} console;


#define in :
#define var auto
//#define const const auto

#endif // LIB_H