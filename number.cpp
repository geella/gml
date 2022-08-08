#include "standard.h"

struct Date {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;

	Date( ) {
		std::time_t end_time = std::chrono::system_clock::to_time_t( std::chrono::system_clock::now( ) );
		std::tm *tm = std::localtime( &end_time );
		year = tm->tm_year + 1900;
		month = tm->tm_mon;
		day = tm->tm_mday;
		hour = tm->tm_hour;
		minute = tm->tm_min;
		second = tm->tm_sec;
	}

};

function application( ) -> void {

	number one = 100;
	number two = 2.4;
	string three = "3";

	console.log( two );
	two.fixed( 2 );
	console.log( two );
	two.round( );
	console.log( two );

	console.log( three.toNumber( ) );

	console.log( one > 2 );
	console.log( one >= 2 );
	console.log( one == 2 );
	console.log( one != 2 );
	console.log( one < 2 );
	console.log( one <= 2 );
	console.log( one + 1 );
	console.log( one - 1 );
	console.log( one * 2 );
	console.log( one / 2 );
	console.log( one += 1 );

	Date date = Date( );
	console.log( date.year );
}