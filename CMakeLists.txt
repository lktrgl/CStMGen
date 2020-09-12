cmake_minimum_required(VERSION 3.5)

project ( CStMGen )

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

if(NOT IS_SUBPROJECT)
	set ( CMAKE_C_STANDARD 99 )
	set ( CMAKE_CXX_STANDARD 17 )
	set ( CMAKE_C_FLAGS "-Wall -Wextra -Werror -g3 -o0" )
	set ( CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -g3 -o0" )
else()
	set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNDEBUG" )
	set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG" )
endif()

add_subdirectory( contrib/lggm )

include_directories (
     include
     contrib/lggm/include
     )

set (cstmgen_libsources 
     src/CStMGen/cstmgen_main.cpp
     include/CStMGen/cstmgen_main.h
     src/CStMGen/cstmgen_params.cpp
     include/CStMGen/cstmgen_params.h
     )

add_library ( cstmgen
    ${cstmgen_libsources}
     )

if(NOT IS_SUBPROJECT)
	add_executable(cstmgen_app
	     src/app/main.cpp
	     )
	
	target_link_libraries(cstmgen_app
	     cstmgen
	     lggm
	     )
endif()
