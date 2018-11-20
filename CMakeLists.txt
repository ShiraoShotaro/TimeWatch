## CMakeLists for TimeWatch System

cmake_minimum_required(VERSION 3.0)
project(TimeWatch)

include_directories(src ${PROJECT_INCLUDE_DIRECTORIES})

### Project Settings

add_executable(TimeWatch src/TimeWatch.cpp src/TimeWatch.hpp test/main.cpp)

# For Multi Platform
if(UNIX) # for Linux

	# Enable C++14 and Multi-thread processing
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -g -O0 -L${CMAKE_SOURCE_DIR}/lib/x86_64-linux-gnu")
	
	# Add X11 multi-thread library
	target_link_libraries(${PROJECT_NAME} X11 pthread)

elseif(WIN32) # for Windows
	
	# Source code are treated as UTF-8 (Must to use UTF-8 BOM)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /source-charset:utf-8")

endif(UNIX)

