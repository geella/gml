#include "standard.h"

void application( ) {

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
			for ( number i = 0; i < value.length( ); i++ ) { console.log( i, value[ i ] ); }
		} else if ( key == "j" ) {
			console.log( value[ "tree" ] );
			for ( string index in value ) { console.log( index, value[ index ] ); }
		} else if ( key == "t" ) {
			undefined A = value[ 0 ], B = value[ 1 ];
			console.log( A, B );
			for ( undefined index in value ) { console.log( index ); }
		}
	}

}