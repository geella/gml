#include "standard.h"

function foo( number value ) -> promise < number > {
	return async( lambda ( ) -> number {
		sleep( value );
		console.log( "foo" );
		return value;
	} );
}

function bar( number value ) -> promise < void > {
	return async( lambda ( ) -> void {
		for ( number i in range( 5 ) ) {
			sleep( value );
			console.log( "bar" );
		}
	} );
}

function application( ) -> void {

	detach bar( 500 );
	await foo( 1000 );

	console.log( "main" );

}