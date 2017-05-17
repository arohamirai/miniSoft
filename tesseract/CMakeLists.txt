cmake_minimum_required(VERSION 2.8)
project(mytest)  

#set(
#    CMAKE_RUNTIME_OUTPUT_DIRECTORY
#    ${CMAKE_HOME_DIRECTORY}/bin
#    )
find_package(OpenCV REQUIRED) 
#find_package(tesseract REQUIRED)
 
#set(LIB libtesseract)

add_executable(mytest main.cpp)  
target_link_libraries(mytest 
${OpenCV_LIBS}
tesseract
)  

