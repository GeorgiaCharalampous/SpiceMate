cmake_minimum_required(VERSION 3.10)

#set(CMAKE_CXX_STANDARD 14)

project(Driver_Test)

add_subdirectory(test)
add_subdirectory(src)

#include(GNUInstallDirs)
#add_executable(Driver_Test test_main.cpp)

#set(LIBSRC VL6180x_rpi.cpp VL6180xcallbackChild.cpp)
#set(LIBINCLUDE VL6180x_rpi.h VL6180xcallbackChild.h VL6180xcallbackInterface.h)

#target_link_libraries(Driver_Test PUBLIC src)

#target_include_directories(Driver_Test PUBLIC
#"${PROJECT_BINARY_DIR}"
#"${PROJECT_SOURCE_DIR}/src")