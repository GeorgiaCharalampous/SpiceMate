include_directories("${PROJECT_SOURCE_DIR}/src")

add_compile_options(-Wall -Wconversion -Wextra -pedantic)
add_library(src_Lib VL6180x_rpi.cpp VL6180xcallbackChild.cpp DataProcess.cpp DPcallbackChild.cpp VIBRO4_rpi.cpp Servo_Driver.cpp Actuation.cpp)

target_link_libraries(src_Lib gpiod)