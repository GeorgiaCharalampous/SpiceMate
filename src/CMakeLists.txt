include_directories("${PROJECT_SOURCE_DIR}/src")

add_compile_options(-Wall -Wconversion -Wextra -pedantic)
add_library(src_Lib TestCallback.cpp VL6180xcallbackChild.cpp)

target_link_libraries(src_Lib gpiod)