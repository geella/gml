#include "standard.h"

function foo( number value ) -> promise < number > {
	return std::async( [ value ] ( ) {
		sleep( value );
		console.log( "foo" );
		return value;
	} );
}

function bar( number value ) -> promise < void > {
	return std::async( [ value ] ( ) {
		for ( number i in range( 5 ) ) {
			sleep( value );
			console.log( "bar" );
		}
	} );
}

function application( ) -> number {

	detach bar( 500 );
	await foo( 1000 );
	//detach foo( 1000 );
	//await bar( 1000 );
	console.log( "main" );

	return 0;
}


