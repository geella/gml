#ifndef LIB_H
#define LIB_H

#include <string>
#include <iostream>
#include <vector>
#include <map>

#pragma GCC diagnostic ignored "-Wreturn-type"

template < typename TYPE >
struct array {
  std::string type = "array";
	std::vector < TYPE > a;
	std::map < TYPE, TYPE > j;
	int length = 0;
	array( ) { }
	array( std::initializer_list < TYPE > value ) {
		for ( auto i : value ) {
			a.push_back( i );
			j.insert( { length, i } ); 
			length += 1;
		}
	}
	TYPE& operator [ ] ( TYPE value ) { return a[ value.n ]; }
	void push( TYPE value ) {
		a.push_back( value );
		j.insert( { length, value } );
		length += 1;
	}
  auto begin( ) { return j.begin( ); }
  auto end( ) { return j.end( ); }
};

template < typename TYPE >
struct json {
  std::string type = "json";
	std::map < TYPE, TYPE > j;
	json( std::initializer_list < std::pair < TYPE, TYPE > > value ) { 
		for ( auto [ k, v ] : value ) {
			j.insert( { k, v } );
		}
	}
	TYPE& operator [ ] ( TYPE value ) {
		return j[ value ];
	}
	TYPE length( ) {
		return j.size( );
	}
	bool operator == ( const TYPE &other ) const { return j == other.j; }
	bool operator < ( const TYPE &other ) const { return j < other.j; }
	auto begin( ) { return j.begin( ); }
	auto end( ) { return j.end( ); }
};

template < typename TYPE >
struct tuple {
  std::string type = "tuple";
	std::map < TYPE, TYPE > j;
	int length = 0;
	tuple( std::initializer_list < TYPE > value ) { 
		for( auto i : value ) {
			j.insert( { length, i } );
			length += 1;
    }
	}
	TYPE operator [ ] ( TYPE value ) {
		if ( value.n <= length ) {
			return j[ value.n ];
		}
	}
	bool operator == ( const auto &other ) const { return j == other.j; }
	bool operator < ( const auto &other ) const { return j < other.j; }
	auto begin( ) { return j.begin( ); }
	auto end( ) { return j.end( ); }
};

struct Var {
	int n;
	std::string s;
	bool b;
  std::string type = "undefined";
	std::map < Var, Var > j;
	std::vector < Var > a;
	std::vector < Var > t;
	int length = 0;
	Var( ) { }
	Var( int value ) : n( value ) { type = "number"; }
	Var( const char* value ) : s( value ) { type = "string"; }
	Var( bool value ) : b( value ) { type = "boolean"; }
	Var( json < Var > value ) {
		type = "json";
		for ( auto [ k, v ] : value ) {
			j.insert( { k, v } );
			length += 1;
		}
	}
	Var( array < Var > value ) {
		type = "array";
		for ( auto [ i, v ] : value ) {
			a.push_back( v );
			j.insert( { i, v } );
			length += 1;
		}
	}
	Var( tuple < Var > value ) {
		type = "tuple";
		for ( auto [ k, v ] : value ) {
			t.push_back( v );
			j.insert( { length, v } );
			length += 1;
		}
	}
	Var& operator [ ] ( Var value ) {
		if ( type == "array" ) { return a[ value.n ]; }
		else if ( type == "json" ) {
			if ( value.type == "string" ) {
				return j[ value ];
			} else if ( value.type == "number" ) {
				throw "OOOMMMGGG";
			} 
		} else if ( type == "tuple" ) {
			if ( value.n <= length ) {
				return j[ value.n ];
			}
		}
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
	bool operator == ( const Var &other ) const {
		if ( type == "number" ) { return n == other.n; }
		else if ( type == "string" ) { return s == other.s; }
		else if ( type == "boolean" ) { return b == other.b; }
		else if ( type == "json" ) { return j == other.j; }
		else if ( type == "array" ) { return a == other.a; }
	}
	bool operator < ( const Var &other ) const {
		if ( type == "number" ) { return n < other.n; }
		else if ( type == "string" ) { return s < other.s; }
		else if ( type == "boolean" ) { return b < other.b; }
		else if ( type == "json" ) { return j < other.j; }
		else if ( type == "array" ) { return a < other.a; }
	}
	auto begin( ) {
		return j.begin( );
	}
	auto end( ) {
		return j.end( );
	}
};

struct {
	void log( Var v1 ) {
		if ( v1.type == "number" ) {
			std::cout << "\033[93m" << v1.n << "\033[0m\n";
		} else if ( v1.type == "string" ) {
			std::cout << "\033[32m" << v1.s << "\033[0m\n";
		} else if ( v1.type == "boolean" ) {
			std::string data = ( v1.b ) ? "true" : "false";
			std::cout << "\033[94m" << data << "\033[0m\n";
		} else {
			std::cout << "\033[95m" << v1.type << "\033[0m\n";
		} 
	}
	void log( Var v1, Var v2 ) {
		if ( v1.type == "number" ) {
			std::cout << "\033[93m" << v1.n << "\033[0m ";
		} else if ( v1.type == "string" ) {
			std::cout << "\033[32m" << v1.s << "\033[0m ";
		} else if ( v1.type == "boolean" ) {
			std::string data = ( v2.b ) ? "true" : "false";
			std::cout << "\033[94m" << data << "\033[0m ";
		} else {
			std::cout << "\033[95m" << v1.type << "\033[0m ";
		}

		if ( v2.type == "number" ) {
			std::cout << " \b" << "\033[93m" << v2.n << "\033[0m\n";
		} else if ( v2.type == "string" ) {
			std::cout << " \b" << "\033[32m" << v2.s << "\033[0m\n";
		} else if ( v2.type == "boolean" ) {
			std::string data = ( v2.b ) ? "true" : "false";
			std::cout << " \b" << "\033[94m" << data << "\033[0m\n";
		} else {
			std::cout << " \b" << "\033[95m" << v2.type << "\033[0m\n";
		}
	}
	void log( Var v1, Var v2, Var v3 ) {
		if ( v1.type == "number" ) {
			std::cout << "\033[93m" << v1.n << "\033[0m ";
		} else if ( v1.type == "string" ) {
			std::cout << "\033[32m" << v1.s << "\033[0m ";
		} else if ( v1.type == "boolean" ) {
			std::string data = ( v2.b ) ? "true" : "false";
			std::cout << "\033[94m" << data << "\033[0m ";
		} else {
			std::cout << "\033[95m" << v1.type << "\033[0m ";
		}
		
		if ( v2.type == "number" ) {
			std::cout << " \b" << "\033[93m" << v2.n << "\033[0m ";
		} else if ( v2.type == "string" ) {
			std::cout << " \b" << "\033[32m" << v2.s << "\033[0m ";
		} else if ( v2.type == "boolean" ) {
			std::string data = ( v2.b ) ? "true" : "false";
			std::cout << " \b" << "\033[94m" << data << "\033[0m ";
		} else {
			std::cout << " \b" << "\033[95m" << v2.type << "\033[0m ";
		}
		
		if ( v3.type == "number" ) {
			std::cout << " \b" << "\033[93m" << v3.n << "\033[0m\n";
		} else if ( v3.type == "string" ) {
			std::cout << " \b" << "\033[32m" << v3.s << "\033[0m\n";
		} else if ( v3.type == "boolean" ) {
			std::string data = ( v3.b ) ? "true" : "false";
			std::cout << " \b" << "\033[94m" << data << "\033[0m\n";
		} else {
			std::cout << " \b" << "\033[95m" << v3.type << "\033[0m\n";
		}
	}
} console;


#define in :
#define var auto
#define const const auto

#endif // LIB_H

/*
template < typename T >
struct Iterator {
	T* data;

	Iterator( T* value ) : data( value ) {}

	T& operator* ( ) const { return *data; }
	T* operator-> ( ) const { return data; }

	Iterator& operator++ ( ) { data++; return *this; }
	Iterator& operator-- ( ) { data--; return *this; }

	T operator- ( const Iterator& it ) const { return this->data - it.data; }

	Iterator operator+ ( const T& diff ) const { return Iterator( data + diff ); }
	Iterator operator- ( const T& diff ) const { return Iterator( data - diff ); }

	T& operator[] ( const T& offset ) const { return *( *this + offset ); }

	bool operator== ( const Iterator& it ) const { return data == it.data; }
	bool operator!= ( const Iterator& it ) const { return data != it.data; }
	bool operator< ( const Iterator& it ) const { return data < it.data; }
	bool operator> ( const Iterator& it ) const { return data > it.data; }
	bool operator>= ( const Iterator& it ) const { return !(data < it.data); }
	bool operator<= ( const Iterator& it ) const { return !(data > it.data); }

	operator Iterator < const T > ( ) const { return Iterator < const T > ( data ); }
};

Iterator < Var > begin( ) {
	if ( type == "array" ) { return Iterator < Var > ( &a[ 0 ] ); }
	else if ( type == "json" ) { return Iterator < Var > ( &t[ 0 ] ); }
}
Iterator < Var > end( ) {
	if ( type == "array" ) { return Iterator < Var > ( &a[ length ] ); }
	else if ( type == "json" ) { return Iterator < Var > ( &t[ length ] ); }
}
*/