#include "standard.h"

function foo( number value ) -> void {
	for ( number i in range( 5 ) ) {
		time.sleep( value );
		console.log( "bar" );
	}
}

function bar( number value ) -> number {
	time.sleep( value );
	console.log( "foo" );
	return value;
}

function application( ) -> void {
	
	foo( 500 );
	number n = bar( 1000 );

	lambda ( ) -> void {
		for ( number i in range( 2 ) ) {
			time.sleep( 100 );
			console.log( "lambda" );
		}
	} ( );

	console.log( "main" );

}