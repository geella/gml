#ifndef LIB_H
#define LIB_H

#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <future>
#include <thread>
#include <chrono>
#include <functional>

#pragma GCC diagnostic ignored "-Wreturn-type"

// index to elements
// para array necesito saber el type
// operator ( ) for tuple unpack?
// corregir los throw y el stdvector como return
// const para todas las operaciones pero map solo sirve con .at
// nececsito otro nombre para los parametros que no sea value

struct undefined {
	double n;
	std::string s;
	bool b;
  std::string type = "undefined";
	std::map < undefined, undefined > container;
	std::vector < undefined > index;
	int length = 0;

	undefined( ) { }

	undefined( int value ) : n( value ) { type = "number"; }

	undefined( double value ) : n( value ) { type = "number"; }

	undefined( const char* value ) : s( value ) {
		type = "string";
		for ( auto i : s ) { container.insert( { length, i } ); length += 1; }
	}

	undefined( std::string value ) : s( value ) {
		type = "string";
		for ( auto i : s ) { container.insert( { length, i } ); length += 1; }
	}

	undefined( bool value ) : b( value ) { type = "boolean"; }

	undefined( std::initializer_list < undefined > value ) {
		for ( auto i : value ) { index.push_back( i ); container.insert( { length, i } ); length += 1; }
	}

	undefined( std::initializer_list < std::pair < undefined, undefined > > value ) {
		for ( auto [ k, v ] : value ) { index.push_back( k ); container.insert( { k, v } ); length += 1; }
	}

	undefined& operator [ ] ( undefined value ) {
		if ( type == "number" ) { throw "OOOMMMGGG"; }
		else if ( type == "boolean" ) { throw "OOOMMMGGG"; }
		return container[ value ];
	}

	undefined& operator = ( int value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		n = value;
		return *this;
	}

	undefined& operator = ( const char* value ) {
		if ( type == "string" ) { throw "OOOMMMGGG"; }
		s = value;
		return *this;
	}

	undefined& operator = ( bool value ) {
		if ( type == "string" ) { throw "OOOMMMGGG"; }
		b = value;
		return *this;
	}

	undefined& operator = ( undefined value ) {
		if ( value.type == type ) { throw "OOOMMMGGG"; }
		n = value.n;
		s = value.s;
		b = value.b;
		index = value.index;
		container = value.container;
		return *this;
	}

	void operator ++ ( int ) { n++; }

	bool operator == ( const undefined &other ) const {
		if ( type == "number" ) { return n == other.n; }
		else if ( type == "string" ) { return s == other.s; }
		else if ( type == "boolean" ) { return b == other.b; }
		else if ( type == "json" || type == "array" || type == "tuple" ) { return container == other.container; }
	}

	bool operator < ( const undefined &other ) const {
		if ( type == "number" ) { return n < other.n; }
		else if ( type == "string" ) { return s < other.s; }
		else if ( type == "boolean" ) { return b < other.b; }
		else if ( type == "json" || type == "array" || type == "tuple" ) { return container < other.container; }
	}

	auto begin( ) { return index.begin( ); }
	auto end( ) { return index.end( ); }

	// NUMBER
	undefined toString( ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		return std::to_string( n );
	}

	// STRING
	undefined toLower( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		std::string value = "";
		for ( char piece : s ) { value += tolower( piece ); }
		return value;
	}

	undefined toUpper( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		undefined value = "";
		for ( char piece : s ) { value.s += toupper( piece ); }
		return value;
	}

	undefined toCapital( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		undefined value = "";
		for ( char piece : s ) { value.s += tolower( piece ); }
		value.s[ 0 ] = toupper( value.s[ 0 ] );
		return value;
	}

	undefined isLower( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		for ( char piece : s ) { if ( !islower( piece ) ) { return false; } }
		return true;
	}

	undefined isUpper( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		for ( char piece : s ) { if ( !isupper( piece ) ) { return false; } }
		return true;
	}

	undefined isCapital( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		for ( int i = 1; i < s.length( ); i++ ) { if ( !islower( s[ i ] ) ) { return false; } }
		if ( !isupper( s[ 0 ] ) ) { return false; }
		return true;
	}

	undefined endsWith( undefined value ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		int external = value.s.length( ) -1, internal = s.length( ) -1;
		if ( external > internal ) { return false; }
		for ( int i = external; i >= 0; i-- ) { if ( s[ internal ] != value.s[ external ] ) { return false; } external--; internal--; }
		return true;
	}

	undefined startsWith( undefined value ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		int external = value.s.length( ) -1, internal = s.length( ) -1;
		if ( external > internal ) { return false; }
		for ( int i = external; i <= 0; i++ ) { if ( s[ internal ] != value.s[ external ] ) { return false; } external++; internal++; }
		return true;
	}

	undefined isNumeric( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		for ( int i = 0; i <= s.length( ); i++ ) { if ( !isdigit( s[ i ] ) )	{ return false; } }
		return true;
	}

	undefined toNumber( ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		for ( int i = 0; i < s.length( ); i++ ) { if ( !isdigit( s[ i ] ) ) { throw "OOOMMMGGG"; } }
		return atoi( s.c_str( ) );
	}

	undefined replace( undefined value, undefined v ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		while ( true ) { int index = s.find( value.s );
			if ( index != -1 ) { s.replace( index, value.s.length( ), v.s ); }
			else { break; }
		}
		return s;	
	}

	undefined contains( undefined value ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		int index = s.find( value.s );
		if ( index == -1 ) { return false; };
		return true;	
	}

	std::vector < undefined > split( undefined value ) {
		if ( type != "string" && value.type == "string" ) { throw "OOOMMMGGG"; }
		std::string token;
		std::vector < undefined > out;
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
	undefined& operator ! ( ) {
		if ( type != "boolean" ) { throw "OOOMMMGGG"; }
		b = !b;
		return *this;
	};

};

struct number : undefined {
	number( int value ) : undefined( value ) { }
	number( undefined value ) {
		if ( value.type == "number" ) {
			type = value.type;
			n = value.n;
		} else {
			throw "OOOMMMGGG";
		}
	}
};

struct string : undefined {
	string( const char* value ) : undefined( value ) {}
	string( undefined value ) {
		if ( value.type != "string" ) { throw "OOOMMMGGG"; }
		type = value.type;
		s = value.s;
		for ( auto i : s ) {
			container.insert( { length, i } );
			length += 1;
		}
	}
};

struct boolean : undefined {
	boolean( bool value ) : undefined( value ) { }
	boolean( undefined value ) {
		if ( value.type == "boolean" ) {
			type = value.type;
			b = value.b;
		} else {
			throw "OOOMMMGGG";
		}
	}
};

template < typename TYPE >
struct json : undefined {
	json( std::initializer_list < std::pair < undefined, undefined > > value ) : undefined( value ) { type = "json"; }
};

template < typename TYPE >
struct array : undefined {
	array( std::initializer_list < undefined > value ) : undefined( value ) { type = "array"; }
	array( std::vector < undefined > value ) {
		type = "array";
		for ( auto i : value ) {
			index.push_back( i );
			container.insert( { length, i } );
			length += 1;
		}
	}
	array& operator = ( std::vector < undefined > value ) {
		for ( auto i : value ) {
			index.push_back( i );
			container.insert( { length, i } );
			length += 1;
		}
		return *this;
	}

};

template < typename ... TYPES >
struct tuple : undefined {
	tuple( TYPES ... args ) { 
		type = "tuple";
		( index.push_back( args ), ... );
		for ( auto i : index ) { container.insert( { length, i } ); length += 1; }
	}
};

template < typename TYPE >
struct promise {
	std::future < TYPE > data;
	promise( std::future < TYPE > value ) : data( std::move( value ) ) { }
};

template < typename TYPE >
auto _async_( TYPE callback ) {
	return std::async( callback );
}

struct {
	template < typename TYPE >
	TYPE operator << ( std::future < TYPE > value ) {
		return value.get( );
	}
	template < typename TYPE >
	TYPE operator << ( TYPE value ) {
		return value;
	}
} await;

struct {

	std::future < void > v;
	std::future < number > n;
	std::future < string > s;
	std::future < boolean > b;

	void operator << ( promise < void > value ) { v = std::move( value.data ); }
	void operator << ( promise < number > value ) { n = std::move( value.data ); }
	void operator << ( promise < string > value ) { s = std::move( value.data ); }
	void operator << ( promise < boolean > value ) { b = std::move( value.data ); }

} detach;

void sleep( undefined value ) {
	std::this_thread::sleep_for( std::chrono::milliseconds( ( int ) value.n ) );
}

std::vector < int > _range_( int value ) {
	std::vector < int > v;
	for ( int i = 0; i < value; i++ ) { v.push_back( i ); }
	return v;
} 

std::vector < int > _range_( int start, int end ) {
	std::vector < int > v;
	for ( int i = start; i < end; i++ ) { v.push_back( i ); }
	return v;
}

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

	std::string type( undefined data ) {
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
		std::vector < undefined > data;
		( data.push_back( args ), ... );
		std::cout << type( data[ 0 ] );
		for ( int i = 1; i < data.size( ); i++ ) {
			std::cout << " \b " << type( data[ i ] );
		}
		std::cout << std::endl;
	}

} console;

#define lambda [=]
#define in :
#define range _range_
#define function auto
#define await await<<
#define detach detach<<
#define async _async_

void application( );

int main( ) { application( ); return 0; }

#endif // LIB_H
