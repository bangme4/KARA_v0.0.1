cmake_minimum_required(VERSION 3.10)
project(kara)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wempty-body -Werror -Wstrict-prototypes -Warray-bounds -g)

include_directories(/opt/homebrew/include/SDL2)

file(GLOB SOURCES src/defs.h src/structs.h src/*.c src/*.h src/*/*.c src/*/*.h)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    /opt/homebrew/lib/libSDL2.dylib
    /opt/homebrew/lib/libSDL2_mixer.dylib
    /opt/homebrew/lib/libSDL2_image.dylib
    /opt/homebrew/lib/libSDL2_ttf.dylib
    m
)
