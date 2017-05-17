cmake_minimum_required(VERSION 2.8)
project(screenSnap)  


include(CheckCXXCompilerFlag)  
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)  
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)  
if(COMPILER_SUPPORTS_CXX11)  
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")  
elseif(COMPILER_SUPPORTS_CXX0X)  
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")  
else()  
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")  
endif() 

#指定编译类型
SET(CMAKE_BUILE_TYPE DEBUG)
#指定编译器
SET(CMAKE_CXX_FLAGS_DEBUG "-g++ -Wall")  # CMAKE_CXX_FLAGS_DEBUG ----  C++ 编译器

#添加子目录,有几个写几个
#ADD_SUBDIRECTORY(include)



# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK2_INCLUDE_DIRS})

# Add other flags to the compiler
add_definitions(${GTK2_CFLAGS_OTHER})




find_package(OpenCV REQUIRED)





add_executable(screenSnap main.cpp
	#screenshoteditor.c
	#screenshoteditor-helpers.c
	)
target_link_libraries(screenSnap 
	${OpenCV_LIBS}
	${GTK2_LIBRARIES} 
	)

