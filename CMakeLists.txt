cmake_minimum_required(VERSION 3.10)
project(kara)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wempty-body -Werror -Wstrict-prototypes -Warray-bounds -g)

# Use stable Homebrew prefixes instead of versioned Cellar paths
set(SDL2_HOME /opt/homebrew/opt/sdl2)
set(SDL2_MIXER_HOME /opt/homebrew/opt/sdl2_mixer)
set(SDL2_IMAGE_HOME /opt/homebrew/opt/sdl2_image)
set(SDL2_TTF_HOME /opt/homebrew/opt/sdl2_ttf)

# Include directories
include_directories(
    ${SDL2_HOME}/include
    ${SDL2_HOME}/include/SDL2
    ${SDL2_MIXER_HOME}/include
    ${SDL2_MIXER_HOME}/include/SDL2
    ${SDL2_IMAGE_HOME}/include
    ${SDL2_IMAGE_HOME}/include/SDL2
    ${SDL2_TTF_HOME}/include
    ${SDL2_TTF_HOME}/include/SDL2
)

# Library paths (use symlinks from /opt/homebrew/lib)
set(SDL2_LIBRARY ${SDL2_HOME}/lib/libSDL2.dylib)
set(SDL2_MIXER_LIBRARY ${SDL2_MIXER_HOME}/lib/libSDL2_mixer.dylib)
set(SDL2_IMAGE_LIBRARY ${SDL2_IMAGE_HOME}/lib/libSDL2_image.dylib)
set(SDL2_TTF_LIBRARY ${SDL2_TTF_HOME}/lib/libSDL2_ttf.dylib)

# Source files
file(GLOB SOURCES src/defs.h src/structs.h src/*.c src/*.h src/*/*.c src/*/*.h)

# Output binary to the project directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SDL2 libraries
target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARY}
    ${SDL2_MIXER_LIBRARY}
    ${SDL2_IMAGE_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    m
)
