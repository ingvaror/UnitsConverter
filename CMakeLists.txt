cmake_minimum_required(VERSION 3.1.0)

project(UnitsConverter)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	set(CMAKE_CXX_FLAGS_RELEASE "/std:c++17 /bigobj")
	set(CMAKE_CXX_FLAGS_DEBUG "/std:c++17 /ZI /Od /bigobj")
else()
	set(CMAKE_CXX_FLAGS_RELEASE "-std=c++17 -fPIC -O3")
	set(CMAKE_CXX_FLAGS_DEBUG "-std=c++17 -fPIC -O0 -g -fpermissive")
endif()

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS system filesystem) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets Gui REQUIRED)

add_executable(UnitsConverter
    main.cpp
)
target_link_libraries(UnitsConverter ${Boost_LIBRARIES})
