#include "standard.h"

function application( ) -> void {

  boolean b = true;

  if ( b && b == true ) {
    console.log( b );
  }

  b = !b;

  if ( !b && b == false ) {
    console.log( b );
  }

}