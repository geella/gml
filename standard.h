#ifndef STANDARD_H
#define STANDARD_H

#include <vector>
#include <future>
#include <chrono>
#include <map>
#include <string>
#include <iostream>
#include <cmath>

#pragma GCC diagnostic ignored "-Wreturn-type"
#define time _time_

// index to elements
// para array necesito saber el type
// operator ( ) for tuple unpack?
// corregir los throw y el std::vector como return
// const para todas las operaciones pero map solo sirve con .at
// nececsito otro nombre para los parametros que no sea value

// operator bool for check if value is empty or bool 
// make private some methods and properties
// undefined operator bool( ); default sin definir
// falta slice
// array push
// Constructor nuevo para todos los tipos menos undefined que acepte undefined mientras sea del mismo tipo
// String.parse() = toJson
// Json o array .toString()
// date dentro de time
// The logical operators work with boolean values:

struct undefined {
	int i;
	double f;
	std::string s;
	bool b;
  std::string type = "undefined";
	bool decimal = false;
	std::map < undefined, undefined > container;
	std::vector < undefined > index;
	int l = 0;
	int precision = 1;

	// Constructors
	undefined( ) { }

	undefined( int value ) : i( value ) { type = "number"; decimal = false; }

	undefined( double value ) : f( value ) { type = "number"; decimal = true; }

	undefined( const char* value ) : s( value ) {
		type = "string";
		for ( auto i : s ) { container.insert( { l, i } ); l += 1; }
	}

	undefined( std::string value ) : s( value ) {
		type = "string";
		for ( auto i : s ) { container.insert( { l, i } ); l += 1; }
	}

	undefined( bool value ) : b( value ) { type = "boolean"; }

	undefined( std::initializer_list < undefined > value ) {
		type = "array";
		for ( auto i : value ) {
			index.push_back( i );
			container.insert( { l, i } );
			l += 1; }
	}

	undefined( std::vector < undefined > value ) {
		type = "array";
		for ( auto i : value ) { index.push_back( i ); container.insert( { l, i } ); l += 1; }
	}

	undefined( std::initializer_list < std::pair < undefined, undefined > > value ) {
		for ( auto [ k, v ] : value ) { index.push_back( k ); container.insert( { k, v } ); l += 1; }
	}

	auto begin( ) { return index.begin( ); }
	auto end( ) { return index.end( ); }

	undefined toString( ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		return decimal ? std::to_string( f ) : std::to_string( i );
	}

	undefined& fixed( int value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		precision = value;
		if ( !decimal ) { decimal = true; f = i; }
		return *this;
	}

	undefined& round( ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		i = decimal ? (int)std::round( f ) : i;
		decimal = false;
		precision = 0;
		return *this;
	}

	// STRING METHODS
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
		// AGREGAR QUE PUEDA CONVERTIR UN STRING A FLOAT
		return atoi( s.c_str( ) );
	}

	undefined replace( undefined value, undefined v ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		std::string tmp = s;
		while ( true ) { int index = tmp.find( value.s );
			if ( index != -1 ) { tmp.replace( index, value.s.length( ), v.s ); }
			else { break; }
		}
		return tmp;	
	}

	undefined contains( undefined value ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		int index = s.find( value.s );
		if ( index == -1 ) { return false; };
		return true;	
	}

	std::vector < undefined > toArray( undefined value ) {
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

	undefined length ( ) {
		if ( type != "string" && type != "array" && type != "json" && type != "tuple" ) { throw "OOOMMMGGG"; }
		return l;
	};

	explicit operator bool( ) {
		if ( type != "boolean" ) { throw "OOOMMMGGG"; }
		return b;
	}

	// Binary Operators
	undefined operator + ( undefined value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		if ( decimal ) { double tmp = value.decimal ? value.f : value.i; return f + tmp;}
		else { int tmp = value.decimal ? value.f : value.i; return i + tmp; }
	}

	undefined operator - ( undefined value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		if ( decimal ) { double tmp = value.decimal ? value.f : value.i; return f - tmp;}
		else { int tmp = value.decimal ? value.f : value.i; return i - tmp; }
	}

	undefined operator * ( undefined value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		if ( decimal ) { double tmp = value.decimal ? value.f : value.i; return f * tmp;}
		else { int tmp = value.decimal ? value.f : value.i; return i * tmp; }
	}

	undefined operator / ( undefined value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		if ( decimal ) { double tmp = value.decimal ? value.f : value.i; return f / tmp;}
		else { int tmp = value.decimal ? value.f : value.i; return i / tmp; }
	}

	// Assignment Operators
	undefined& operator = ( int value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		i = value;
		decimal = false;
		return *this;
	}

	undefined& operator = ( double value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		f = value;
		decimal = true;
		return *this;
	}

	undefined& operator = ( const char* value ) {
		if ( type != "string" ) { throw "OOOMMMGGG"; }
		s = value;
		return *this;
	}

	undefined& operator = ( bool value ) {
		if ( type != "boolean" ) { throw "OOOMMMGGG"; }
		b = value;
		return *this;
	}

	undefined& operator = ( undefined value ) {
		if ( value.type == type ) { throw "OOOMMMGGG"; }
		i = value.i;
		f = value.f;
		decimal = value.decimal;
		s = value.s;
		b = value.b;
		index = value.index;
		container = value.container;
		return *this;
	}

	undefined operator += ( undefined value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		if ( decimal ) { double tmp = value.decimal ? value.f : value.i; return f += tmp;}
		else { int tmp = value.decimal ? value.f : value.i; return i += tmp; }
	}

	undefined operator -= ( undefined value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		if ( decimal ) { double tmp = value.decimal ? value.f : value.i; return f -= tmp;}
		else { int tmp = value.decimal ? value.f : value.i; return i -= tmp; }
	}

	undefined operator *= ( undefined value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		if ( decimal ) { double tmp = value.decimal ? value.f : value.i; return f *= tmp;}
		else { int tmp = value.decimal ? value.f : value.i; return i *= tmp; }
	}

	undefined operator /= ( undefined value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		if ( decimal ) { double tmp = value.decimal ? value.f : value.i; return f /= tmp;}
		else { int tmp = value.decimal ? value.f : value.i; return i /= tmp; }
	}

	// Relational Operators
	bool operator == ( const undefined &other ) const {
		if ( type == "number" ) { if ( decimal ) { return i == other.i; } else { return f == other.f; } } 
		else if ( type == "string" ) { return s == other.s; }
		else if ( type == "boolean" ) { return b == other.b; }
		else if ( type == "json" || type == "array" || type == "tuple" ) { return container == other.container; }
	}

	bool operator < ( const undefined &other ) const {
		if ( type == "number" ) { if ( decimal ) { return i < other.i; } else { return f < other.f; } } 
		else if ( type == "string" ) { return s < other.s; }
		else if ( type == "boolean" ) { return b < other.b; }
		else if ( type == "json" || type == "array" || type == "tuple" ) { return container < other.container; }
	}

	bool operator == ( undefined value ) {
		if ( type == "number" ) {
			if ( decimal ) { double tmp = value.decimal ? value.f : value.i; return f == tmp;}
			else { int tmp = value.decimal ? value.f : value.i; return i == tmp; }
		} else if ( type == "string" ) {
			return s == value.s;
		} else if ( type == "boolean" ) {
			return b == value.b;
		} else if ( type == "array" || type == "tuple" ) {
			return index == value.index;
		} else if ( type == "json" ) {
			return container == container;
		}
	}

	bool operator != ( undefined value ) {
		if ( type == "number" ) {
			if ( decimal ) { double tmp = value.decimal ? value.f : value.i; return f != tmp;}
			else { int tmp = value.decimal ? value.f : value.i; return i != tmp; }
		} else if ( type == "string" ) {
			return s != value.s;
		} else if ( type == "boolean" ) {
			return b != value.b;
		} else if ( type == "array" || type == "tuple" ) {
			return index != value.index;
		} else if ( type == "json" ) {
			return container != container;
		}
	}

	bool operator > ( undefined value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		if ( decimal ) { double tmp = value.decimal ? value.f : value.i; return f > tmp;}
		else { int tmp = value.decimal ? value.f : value.i; return i > tmp; }
	}
	
	bool operator < ( undefined value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		if ( decimal ) { double tmp = value.decimal ? value.f : value.i; return f < tmp;}
		else { int tmp = value.decimal ? value.f : value.i; return i < tmp; }
	}

	bool operator >= ( undefined value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		if ( decimal ) { double tmp = value.decimal ? value.f : value.i; return f >= tmp;}
		else { int tmp = value.decimal ? value.f : value.i; return i >= tmp; }
	}

	bool operator <= ( undefined value ) {
		if ( type != "number" ) { throw "OOOMMMGGG"; }
		if ( decimal ) { double tmp = value.decimal ? value.f : value.i; return f <= tmp;}
		else { int tmp = value.decimal ? value.f : value.i; return i <= tmp; }
	}

	// Unary Operators
	bool operator ! ( ) {
		if ( type != "boolean" ) { throw "OOOMMMGGG"; }
		return !b ? true : false;
	};

	// Increment and Decrement Operators
	void operator ++ ( int ) {
		 i++;
	}

	void operator -- ( int ) {
		i--;
	}

	// Subscripting Operator
	undefined& operator [ ] ( undefined value ) {
		if ( type == "number" ) { throw "OOOMMMGGG"; }
		else if ( type == "string" ) { throw "OOOMMMGGG"; }
		else if ( type == "boolean" ) { throw "OOOMMMGGG"; }
		else if ( type == "array" || type == "tuple" ) { return index[ value.i ]; }
		else if ( type == "json" ) { return container[ value ]; }
	}

	// Function Call Operator
  void operator ( ) ( ) {
	}

};

struct number : undefined {
	number( int value ) : undefined( value ) { }
	number( double value ) : undefined( value ) { }
	number( undefined value ) {
		if ( value.type == "number" ) {
			type = value.type;
			i = value.i;
			f = value.f;
			decimal = value.decimal;
		} else {
			throw "OOOMMMGGG";
		}
	}
	number& operator = ( int value ) {
		i = value;
		decimal = false;
		return *this;
	}
	number& operator = ( double value ) {
		f = value;
		decimal = true;
		return *this;
	}
};

struct string : undefined {
	string( const char* value ) : undefined( value ) {}
	string( undefined value ) {
		if ( value.type != "string" ) { throw "OOOMMMGGG"; }
		type = value.type;
		s = value.s;
		for ( auto i : s ) {
			container.insert( { l, i } );
			l += 1;
		}
	}
	string& operator = ( const char* value ) {
		s = value;
		return *this;
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
	boolean& operator = ( bool value ) {
		b = value;
		return *this;
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
			container.insert( { l, i } );
			l += 1;
		}
	}
	array& operator = ( std::vector < undefined > value ) {
		for ( auto i : value ) {
			index.push_back( i );
			container.insert( { l, i } );
			l += 1;
		}
		return *this;
	}
	// ACONDICONAR
	//array( undefined value ) { }
};

template < typename ... TYPES >
struct tuple : undefined {
	tuple( TYPES ... args ) { 
		type = "tuple";
		( index.push_back( args ), ... );
		for ( auto i : index ) { container.insert( { l, i } ); l += 1; }
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
	TYPE operator << ( promise < TYPE > value ) {
		return value.data.get( );
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

struct {
	void sleep( number value ) {
		int i = value.decimal ? value.i : ( int ) value.i;
		std::this_thread::sleep_for( std::chrono::milliseconds( i ) );
	}
	double clock( ) {
		return std::chrono::duration_cast < std::chrono::milliseconds > ( 
			std::chrono::time_point_cast < std::chrono::milliseconds > ( 
				std::chrono::high_resolution_clock::now( ) 
			).time_since_epoch( ) 
		).count( );
	}
} time;

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

	std::string number( double data, int precision ) {
		std::string value;
		std::string tmp = std::to_string( data );

		for ( int i = 0; i < tmp.length( ); i++ ) { 
			if ( tmp[ i ] == '.' ) {
				if ( precision != 0 ) {
					for ( int j = i; j < i+precision+1; j++ ) { value += tmp[ j ]; }
				}
				break;
			} else {
				value += tmp[ i ];
			}
		}
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
			if ( data.decimal ) { value = number( data.f, data.precision ); } else { value = number( data.i ); }
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

// array < string > argv
void application( );

int main( ) { application( ); return 0; }

#endif // STANDARD_H


/*
struct Date {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

	Date( ) {
		std::time_t end_time = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now( ) );
		std::tm *tm = std::localtime( &end_time );
		year = tm->tm_year + 1900;
		month = tm->tm_mon;
		day = tm->tm_mday;
		hour = tm->tm_hour;
		minute = tm->tm_min;
		second = tm->tm_sec;
	}

};
*/