#ifndef LIB_H
#define LIB_H

#include <string>
#include <iostream>
#include <vector>
#include <map>

#pragma GCC diagnostic ignored "-Wreturn-type"

struct Var {
	int n;
	std::string s;
	bool b;
  std::string type = "undefined";
	std::map < Var, Var > container;
	std::vector < Var > index;
	int length = 0;
	Var( ) { }
	Var( int value ) : n( value ) { type = "number"; }
	Var( const char* value ) : s( value ) { type = "string"; }
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
	Var& operator = ( int value ) {
		if ( type == "number" ) {
			n = value;
		} else {
			throw "OOOMMMGGG";
		}
		return *this;
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
	auto begin( ) {
		return index.begin( );
	}
	auto end( ) {
		return index.end( );
	}
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
	std::string yellow = "\033[93m";
	std::string blue = "\033[94m";
	std::string green = "\033[32m";
	std::string purple = "\033[95m";
	std::string end = "\033[0m";

	std::string number( int data ) {
		std::string value = std::to_string( data );
		return std::string( yellow + value + end );
	}

	std::string string( std::string data ) {
		return std::string( green + data + end );
	}

	std::string boolean( bool data ) {
		std::string value = ( data ) ? "true" : "false";
		return std::string( blue + value + end );
	}

	std::string container( std::string data ) {
		return std::string( purple + data + end );
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
#define const const auto

#endif // LIB_H