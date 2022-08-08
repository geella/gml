#include "standard.h"

function execute( ) -> tuple < number, string > {
  return { 100, "200" };
}

void application( ) {

  tuple < number, string > t = execute( );

  number n = t[ 0 ];
  string s = t[ 1 ];

  console.log( n, s );

}