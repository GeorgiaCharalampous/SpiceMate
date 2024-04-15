include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/demo")

link_directories("${PROJECT_SOURCE_DIR}/demo")

add_executable(TestDriver demo.cpp)
target_link_libraries(TestDriver gpiod src_Lib)