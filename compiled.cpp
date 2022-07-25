#include "standard.h"

int main( ) {

	var u = Var( );
	var n = Var( 123 );
	var s = Var( "abc" );
	var b = Var( true );

	console.log( n, s, b );

	var a = array < Var > { 1, 2 };
	for ( var [ index, value ] in a ) { console.log( index, value ); }

	var t = tuple < Var > { 100, "200" };
	var A = t[ 0 ], B = t[ 1 ];
	
	console.log( A, B );

	var j = json < Var > {
		{ "n", 100 },
		{ "s", "abc" },
		{ "b", true },
		{ "a", array < Var > { 11, 22 } },
		{ "j", json < Var > { { "x", 1 }, { "y", 2 } } },
		{ "t", tuple < Var > { 100, "200" } }
	};

	for ( var [ key, value ] in j ) {
		console.log( key, value );
		if ( key == "a" ) {
			for ( var [ i, v ] in value ) { console.log( i, v ); }
			for ( var i = 0; i < value.length; i++ ) { console.log( value[ i ] ); }
		} else if ( key == "j" ) {
			console.log( value[ "x" ] );
			for ( var [ k, v ] in value ) { console.log( k, v ); }
		} else if ( key == "t" ) {
			var A = value[ 0 ], B = value[ 1 ];
			console.log( A, B );
			for ( var [ i, v ] in value ) { console.log( i, v ); }
		}
	}

	return 0;
}


// crear number bool undefined y string como clases que le asignen a var