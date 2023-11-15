cmake_minimum_required(VERSION 3.26)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS
        solution/src/*.c
        solution/src/*.h
        include/*.h
)

add_executable(image-transformer ${sources}
        src/transform.c
        include/bmp_io_formats.h
        src/transform.c
        include/transform.h
        src/handle_errors.c
        include/handle_errors.h
        include/utils.h
        src/bmp_io_formats.c
        src/handle_errors.c
        src/transform.c
        src/utils.c
        src/main.c
)
target_include_directories(image-transformer PRIVATE src include)
