include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/test")

link_directories("${PROJECT_SOURCE_DIR}/test")

add_executable(TestDriver test_main.cpp)
target_link_libraries(TestDriver gpiod src_Lib)

add_executable (Test1 test1.cpp)
add_test (NAME Test1 COMMAND Test1)
