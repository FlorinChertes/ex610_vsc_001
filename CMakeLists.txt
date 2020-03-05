cmake_minimum_required (VERSION 3.13)
project (ex610_vsc_001_prj)

IF (MSVC) 
	# require C++20
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")

	# Activate C++ exception handling 
	IF (NOT CMAKE_CXX_FLAGS MATCHES "/EHsc") 
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
	ENDIF ()
ELSE ()
	SET(GCC_STD_CPP_2A_COMPILE_FLAGS "-std=c++2a")
	SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_STD_CPP_2A_COMPILE_FLAGS}")

	SET(GCC_STD_CPP_CONCEPTS_COMPILE_FLAGS "-fconcepts")
	SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_STD_CPP_CONCEPTS_COMPILE_FLAGS}")

	SET(GCC_STD_CPP_PERMISIV_COMPILE_FLAGS "-fpermissive")
	SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_STD_CPP_PERMISIV_COMPILE_FLAGS}")
ENDIF () 

# include directories
SET (INCLUDE_DIRS
	"src/test/inc"
	"src/lib/inc"
)
include_directories(${INCLUDE_DIRS})

# add the executable
add_executable(ex610_vsc_001

	src/main.cpp

	src/test/inc/test_func_01.h
	src/test/src/test_func_01.cpp

	src/lib/inc/person.h
	src/lib/src/person.cpp

)
