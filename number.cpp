#include "standard.h"

function application( ) -> void {

	number one = 100;
	number two = 2.0;
	string three = "3";

	two.fixed( 2 );

	console.log( two );
	console.log( three.toNumber( ) );

	console.log( one > 2 );
	console.log( one >= 2 );
	console.log( one == 2 );
	console.log( one < 2 );
	console.log( one <= 2 );
	console.log( one + 1 );
	console.log( one - 1 );
	console.log( one * 2 );
	console.log( one / 2 );
	console.log( one += 1 );

}