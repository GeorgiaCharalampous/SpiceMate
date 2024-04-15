include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/tests")

link_directories("${PROJECT_SOURCE_DIR}/tests")

add_executable(Threshold thresholding.cpp)
target_link_libraries(Threshold src_Lib)