cmake_minimum_required( VERSION 3.9 )
project( compiler )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_FLAGS "-fconcepts" )
set( SOURCES main.cpp )
#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "../" )
add_executable( compiler ${SOURCES} ) 
