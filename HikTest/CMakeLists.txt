cmake_minimum_required(VERSION 2.8)
project(HikTest)  

#set(
#    CMAKE_RUNTIME_OUTPUT_DIRECTORY
#    ${CMAKE_HOME_DIRECTORY}/bin
#    )
find_package(OpenCV REQUIRED)
include_directories(${PROJECT_SOURCE_DIR}/include)
#include_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(${PROJECT_SOURCE_DIR}/lib ${PROJECT_SOURCE_DIR}/lib/HCNetSDKCom)

#aux_source_directory(./src DIR_SRCS)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_executable(HikTest  ./src/HikTest.cpp ./src/Hik.cpp)  
target_link_libraries(HikTest ${OpenCV_LIBS}
AudioRender
HCCore
hcnetsdk
hpr
PlayCtrl
SuperRender
analyzedata
HCAlarm
HCCoreDevCfg
HCDisplay
HCGeneralCfgMgr
HCIndustry
HCPlayBack
HCPreview
HCVoiceTalk
iconv2
StreamTransClient
SystemTransform

 )  

