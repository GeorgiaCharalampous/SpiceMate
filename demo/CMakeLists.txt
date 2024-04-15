include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/demo")

link_directories("${PROJECT_SOURCE_DIR}/demo")

add_executable(DemoDriver demo.cpp)
target_link_libraries(DemoDriver gpiod src_Lib)