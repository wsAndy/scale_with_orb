cmake_minimum_required(VERSION 2.8)
project(scale_orb)

include_directories(
${PORJECT_SOURCE_DIR}
)

find_package(OpenCV 2.4.13 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


add_library( scale_orb_lib  SHARED
	src/scale_orb.cpp 
	src/scale_orb.h 
	)
target_link_libraries( scale_orb_lib ${OpenCV_LIBS})


add_executable(scale src/main.cpp )
target_link_libraries(scale scale_orb_lib)

