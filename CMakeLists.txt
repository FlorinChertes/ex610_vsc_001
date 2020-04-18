cmake_minimum_required (VERSION 3.13)
project (ex610_vsc_001_prj)

IF (MSVC) 
	# require C++20
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")

	# Activate C++ exception handling 
	IF (NOT CMAKE_CXX_FLAGS MATCHES "/EHsc") 
		SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
	ENDIF ()

	message(STATUS "Setting up BOOST for CHFL")
	SET(Boost_INCLUDE_DIR "E:/users/chfl/ms160_app/boost_1_72_0")
	SET(Boost_LIBRARY_DIR "E:/users/chfl/ms160_app/boost_1_72_0/stage/lib")

	include_directories(${Boost_INCLUDE_DIR})
	link_directories(${Boost_LIBRARY_DIR})

	add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
ELSE ()
	SET(GCC_STD_CPP_2A_COMPILE_FLAGS "-std=c++2a")
	SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_STD_CPP_2A_COMPILE_FLAGS}")

	message(STATUS "Setting up BOOST for CHFL")
	set(BOOST_MIN_VERSION "1.54.0")
	find_package(Boost ${BOOST_MIN_VERSION} COMPONENTS serialization system filesystem REQUIRED)

	include_directories(${Boost_INCLUDE_DIR})
	link_directories(${Boost_LIBRARY_DIR})

	add_definitions(-DBOOST_ERROR_CODE_HEADER_ONLY)
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
	src/test/inc/test_func_02.h
	src/test/src/test_func_02.cpp


	src/lib/inc/person.h
	src/lib/src/person.cpp
	src/lib/inc/clip.h
	src/lib/src/clip.cpp

	src/lib/inc/write_to_disk.h
	src/lib/src/write_to_disk.cpp

	src/lib/inc/read_from_disk.h
	src/lib/src/read_from_disk.cpp

	src/lib/inc/component.h
)

target_link_libraries(ex610_vsc_001
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)
