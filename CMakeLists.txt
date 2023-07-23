cmake_minimum_required(VERSION 3.25)
project(Lab2ConwayGOF)

set(CMAKE_PREFIX_PATH "C:/Libs/SDL2" ${CMAKE_PREFIX_PATH})
set(SDL_MAIN_HANDLED ON)
find_package(SDL2 REQUIRED)
set(EXECUTABLE_NAME "Lab2ConwayGOF")

set(CMAKE_CXX_STANDARD 23)

add_executable(Lab2ConwayGOF main.cpp color.h)

set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINK_FLAGS "-Wl,-subsystem,console")
target_include_directories(Lab2ConwayGOF PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(Lab2ConwayGOF PRIVATE ${SDL2_LIBRARIES})
