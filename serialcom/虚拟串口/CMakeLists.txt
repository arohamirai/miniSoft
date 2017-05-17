cmake_minimum_required(VERSION 2.8)
project(myProject)  

find_package( Boost REQUIRED system)
include_directories( ${Boost_INCLUDE_DIR} )
link_directories( ${Boost_LIBRARY_DIRS} )
set( Boost_USE_STATIC_LIBS        OFF )
set( Boost_USE_MULTITHREADED      ON )
set( Boost_USE_STATIC_RUNTIME     OFF )
set( BOOST_ALL_DYN_LINK           ON )

add_executable(myProject serial_com.cpp)  

target_link_libraries(myProject ${Boost_LIBRARIES})
