include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/tests")

link_directories("${PROJECT_SOURCE_DIR}/tests")

add_executable(Threshold thresholding.cpp)
target_link_libraries(Threshold src_Lib)

// Attempt at using CMake to generate unit tests. 
add_executable(TestDriver test_main.cpp)
target_link_libraries(TestDriver gpiod src_Lib)

// add_executable(Test1 test1.cpp)
// add_test(NAME Test1 COMMAND Test1)




