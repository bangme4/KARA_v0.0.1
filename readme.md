Kara Game - Build and Run Instructions
This guide provides step-by-step instructions for building and running the Kara game on both macOS and Windows platforms.

Table of Contents

    Prerequisites

    Building on macOS

    Building on Windows

    Running the Game

    Troubleshooting

Prerequisites

For macOS

    CMake (version 3.10 or higher)

    Homebrew package manager

    SDL2 libraries:

        SDL2

        SDL2_mixer

        SDL2_image

        SDL2_ttf

For Windows
CMake (version 3.10 or higher)

    Visual Studio (2019 or later recommended)

    SDL2 development libraries (32-bit or 64-bit matching your system)

        SDL2

        SDL2_mixer

        SDL2_image

        SDL2_ttf

Building on macOS
Install Homebrew (if not already installed):

bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
Install required dependencies:

bash
brew install cmake sdl2 sdl2_mixer sdl2_image sdl2_ttf
Clone the repository (if not already done):

bash
git clone [repository-url]
cd kara
Create a build directory:

bash
mkdir build
cd build
Run CMake and build the project:

bash
cmake ..
make
The executable will be generated in the project root directory.

Building on Windows
Install Visual Studio with C++ development tools.

Install CMake and add it to your system PATH.

Download SDL2 development libraries from https://www.libsdl.org/download-2.0.php and other SDL components:

SDL2 (https://www.libsdl.org/download-2.0.php)

SDL2_mixer (https://www.libsdl.org/projects/SDL_mixer/)

SDL2_image (https://www.libsdl.org/projects/SDL_image/)

SDL2_ttf (https://www.libsdl.org/projects/SDL_ttf/)

Extract the SDL libraries to a known location (e.g., C:\SDL2).

Modify the CMakeLists.txt to point to your Windows SDL2 paths:

cmake

# Example Windows paths - adjust according to your installation

set(SDL2_LIBRARY C:/SDL2/lib/x64/SDL2.lib)
set(SDL2_MIXER_LIBRARY C:/SDL2_mixer/lib/x64/SDL2_mixer.lib)
set(SDL2_IMAGE_LIBRARY C:/SDL2_image/lib/x64/SDL2_image.lib)
set(SDL2_TTF_LIBRARY C:/SDL2_ttf/lib/x64/SDL2_ttf.lib)

include_directories(
C:/SDL2/include
C:/SDL2_mixer/include
C:/SDL2_image/include
C:/SDL2_ttf/include
)
Open a command prompt in the project directory:

cmd
mkdir build
cd build
cmake .. -G "Visual Studio 16 2019" -A x64
Open the generated solution file in Visual Studio and build the project.

Running the Game
On macOS
After building, the executable will be named kara. Run it from the terminal:

bash
./kara
Or by double-clicking the executable in Finder.

On Windows
After building, the executable will be named kara.exe. You can:

Run it from the command prompt

Double-click the executable in File Explorer

Run it from Visual Studio

Note: You'll need to ensure all required SDL2 DLLs are in the same directory as the executable or in your system PATH.

Troubleshooting
Common macOS Issues
Library not found errors:

Ensure Homebrew installed all SDL2 components correctly

Verify the paths in CMakeLists.txt match your Homebrew installation paths

Run brew info sdl2 to check the installed version and path

Permission denied when running:

bash
chmod +x kara
Common Windows Issues
Missing DLL errors:

Copy the following DLLs to the same directory as your executable:

SDL2.dll

SDL2_mixer.dll

SDL2_image.dll

SDL2_ttf.dll

Plus any additional dependency DLLs these require

CMake can't find SDL2:

Verify your include paths and library paths are correct

Ensure you downloaded the development libraries (not just the runtime binaries)

32-bit vs 64-bit mismatch:

Ensure all libraries and your build target match (all 32-bit or all 64-bit)
