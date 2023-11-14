cmake_minimum_required(VERSION 3.26)
project(lab3)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS
        solution/src/*.c
        solution/src/*.h
        include/*.h
)

add_executable(image-transformer ${sources}
        libraries/image.h
        libraries/bmp_io.h
        src/transform.c
        libraries/transform.h
        src/handle_errors.c
        libraries/handle_errors.h
        libraries/utils.h
        libraries/exit_codes.h
        src/bmp_io.c
        src/handle_errors.c
        src/transform.c
        src/utils.c
        src/main.c
)
target_include_directories(image-transformer PRIVATE src include)
