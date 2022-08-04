#include <iomanip>
#include "standard.h"

int main( ) {

	undefined u;
	number n = 123;
	string s = "abc";
	boolean b = true;

	string str = "Hello World";

	string toLower = str.toLower( );
	string toUpper = str.toUpper( );
	string toCapital = str.toCapital( );

	boolean isLower = str.isLower( );
	boolean isUpper = str.isUpper( );
	boolean isCapital = str.isCapital( );

	boolean endsWith = str.endsWith( "World" );
	boolean startsWith = str.startsWith( "Hello" );

	string replace = str.replace( "or", "" );

	string one = "1";
	number ONE = one.toNumber( );

	array < string > split = str.split( " " );

	console.log( str.contains( "ell" ) );

	console.log( toLower, toUpper, toCapital, replace );
	console.log( isLower, isUpper, isCapital, startsWith, !endsWith );
	console.log( split[ 0 ], split[ 1 ] );
	console.log( str.length );

	console.log( n, s, b );

	array < number > a = { 112, 221 };
	for ( number index in a ) { console.log( index ); }

	tuple < number, string > t = { 100, "200" };
	undefined A = t[ 0 ], B = t[ 1 ];
	
	console.log( A, B );

	json < string > j = {
		{ "n", number( 123 ) },
		{ "s", string( "abc" ) },
		{ "b", boolean( true ) },
		{ "a", array < number > { 11, 22 } },
		{ "j", json < string > {
			{ "one", number( 321 ) },
			{ "two", string( "all" ) },
			{ "tree", boolean( false ) }
		} },
		{ "t", tuple < number, string > { 100, "200" } }
	};

	j[ "n" ] = 1000;

	for ( string key in j ) {
		undefined value = j[ key ];
		console.log( key, value );
		if ( key == "a" ) {
			for ( number index in value ) { console.log( index ); }
			for ( number i = 0; i < value.length; i++ ) { console.log( value[ i ] ); }
		} else if ( key == "j" ) {
			console.log( value[ "tree" ] );
			for ( string index in value ) { console.log( value[ index ] ); }
		} else if ( key == "t" ) {
			undefined A = value[ 0 ], B = value[ 1 ];
			console.log( A, B );
			for ( undefined index in value ) { console.log( index ); }
		}
	}
	
	double aA = 44;
	std::cout << std::to_string( aA ) << std::endl;
	std::cout << std::fixed << std::setprecision(2);
	std::cout << aA << std::endl;
	std::cout << std::fixed << std::setprecision(0);
	std::cout << aA << std::endl;

	return 0;
}