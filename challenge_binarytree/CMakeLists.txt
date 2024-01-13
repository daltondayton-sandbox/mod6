# Set minimum CMAKE
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project( BinarySearchTreeChallenge )

# require C++14
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_EXTENSIONS OFF )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( APP_EXECUTABLE BinarySearchTreeTest )

set( LIB_NAME classLibrary )

# Add the class .cpp and .h files
add_library( ${LIB_NAME} INTERFACE )
target_sources(${LIB_NAME} INTERFACE inc/BinaryTree.hpp)

target_include_directories( ${LIB_NAME} INTERFACE inc )
set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

ADD_EXECUTABLE( ${APP_EXECUTABLE} src/BinaryTreeTest.cpp )
TARGET_LINK_LIBRARIES( ${APP_EXECUTABLE} ${LIB_NAME} )

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT ${APP_EXECUTABLE} )

include (CTest)
add_test(${APP_EXECUTABLE}_find ${APP_EXECUTABLE} 1)
add_test(${APP_EXECUTABLE}_output ${APP_EXECUTABLE} 2)
add_test(${APP_EXECUTABLE}_rightmost ${APP_EXECUTABLE} 3)
add_test(${APP_EXECUTABLE}_delete ${APP_EXECUTABLE} 4)
add_test(${APP_EXECUTABLE}_height ${APP_EXECUTABLE} 5)
add_test(${APP_EXECUTABLE}_leaves ${APP_EXECUTABLE} 6)

find_program(VALGRIND "valgrind")
if(VALGRIND)
	add_custom_target(valgrind
		COMMAND "${VALGRIND}" --tool=memcheck --leak-check=yes --show-reachable=yes --error-exitcode=1 $<TARGET_FILE:${APP_EXECUTABLE}>)
endif()
