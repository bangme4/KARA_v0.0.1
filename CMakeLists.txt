cmake_minimum_required(VERSION 3.10)
Project (kara)

# Use absolute paths to SDL2 libraries
set(SDL2_LIBRARY /opt/homebrew/Cellar/sdl2/2.32.4/lib/libSDL2.dylib)
set(SDL2_MIXER_LIBRARY /opt/homebrew/Cellar/sdl2_mixer/2.8.1_1/lib/libSDL2_mixer.dylib)
set(SDL2_IMAGE_LIBRARY /opt/homebrew/Cellar/sdl2_image/2.8.8/lib/libSDL2_image.dylib)
set(SDL2_TTF_LIBRARY /opt/homebrew/Cellar/sdl2_ttf/2.24.0/lib/libSDL2_ttf.dylib)

add_compile_options(-Wall -Wempty-body -Werror -Wstrict-prototypes -Warray-bounds -g)

# Add include directories
include_directories(
    /opt/homebrew/Cellar/sdl2/2.32.4/include
    /opt/homebrew/Cellar/sdl2/2.32.4/include/SDL2
    /opt/homebrew/Cellar/sdl2_mixer/2.8.1_1/include
    /opt/homebrew/Cellar/sdl2_mixer/2.8.1_1/include/SDL2
    /opt/homebrew/Cellar/sdl2_image/2.8.8/include
    /opt/homebrew/Cellar/sdl2_image/2.8.8/include/SDL2
    /opt/homebrew/Cellar/sdl2_ttf/2.24.0/include
    /opt/homebrew/Cellar/sdl2_ttf/2.24.0/include/SDL2
)

file(GLOB SOURCES   src/defs.h src/structs.h src/*.c src/*.h src/*/*.c src/*/*.h)

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

Add_Executable (${CMAKE_PROJECT_NAME} ${SOURCES})
set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)

# Add Homebrew library paths
link_directories(/opt/homebrew/lib)

target_link_libraries(
    ${CMAKE_PROJECT_NAME}
    ${SDL2_LIBRARY}
    ${SDL2_MIXER_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    m
    # efence
)
