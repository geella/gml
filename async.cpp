#include "standard.h"

function foo( number value ) -> promise < void > {
	return async( lambda ( ) -> void {
		for ( number i in range( 5 ) ) {
			time.sleep( value );
			console.log( "bar" );
		}
	} );
}

function bar( number value ) -> promise < number > {
	return async( lambda ( ) -> number {
		time.sleep( value );
		console.log( "foo" );
		return value;
	} );
}

function application( ) -> void {

	detach foo( 500 );
	number n = await bar( 1000 );

	async( lambda ( ) -> void {
		for ( number i in range( 2 ) ) {
			time.sleep( 100 );
			console.log( "lambda" );
		}
	} );

	console.log( "last" );

}