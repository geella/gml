#include "standard.h"

function application( ) -> void {

	string s = "Hello World";

	console.log( s.toLower( ) );
	console.log( s.toUpper( ) );
	console.log( s.toCapital( ) );
	console.log( s.isLower( ) );
	console.log( s.isUpper( ) ); 
	console.log( s.isCapital( ) );
	console.log( s.endsWith( "World" ) );
	console.log( s.startsWith( "Hello" ) );
	console.log( s.contains( "ell" ) );
	console.log( s.length( ).toString( ) );
	console.log( s.replace( "or", "" ) );
	console.log( s.isNumeric( ) );
	console.log( s.toArray( " " ) );

}