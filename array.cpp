#include "standard.h"

void application( ) {

	string s = "Hello World";

	array < string > a = s.toArray( " " );

  for ( string index in a ) { console.log( index ); }

  array < number > numbers = { 10, 20, 30 };

	for ( number i = 0; i < numbers.length( ); i++ ) { console.log( i, numbers[ i ] ); }

}