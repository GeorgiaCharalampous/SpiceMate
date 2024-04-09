include_directories("${PROJECT_SOURCE_DIR}/src")

add_compile_options(-Wall -Wconversion -Wextra -pedantic)
add_library(src_Lib Vibro_rpi.cpp)

target_link_libraries(src_Lib gpiod)