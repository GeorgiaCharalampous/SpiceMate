cmake_minimum_required(VERSION 3.10)

#set(CMAKE_CXX_STANDARD 14)

project(Driver_Test VERSION 1.0 LANGUAGES CXX)

add_subdirectory(demo)
add_subdirectory(src)
<<<<<<< Updated upstream
add_subdirectory(tests)
=======
enable_testing()
add_test (NAME test1 COMMAND Test1)
>>>>>>> Stashed changes
