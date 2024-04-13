include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/test")

link_directories("${PROJECT_SOURCE_DIR}/test")

add_executable(TestDriver TestServo.cpp)
target_link_libraries(TestDriver src_Lib)