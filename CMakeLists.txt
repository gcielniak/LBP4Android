cmake_minimum_required (VERSION 2.6)
project (LBP4Android)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(LBP4Android LBP4AndroidApp.cpp)
target_link_libraries( LBP4Android ${OpenCV_LIBS} )
