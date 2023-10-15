cmake_minimum_required(VERSION 3.12)

project(1b)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include SDL
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)


# Create a list of your source files in the src directory
set(SOURCES
    src/main.cpp
    src/Entity.cpp
    src/Player.cpp
    src/Box.cpp
    src/MathUtils.cpp
    #    src/Player.cpp
    #    src/World.cpp
    #    src/Game.cpp
    # Add more source files as needed
)

# Create the executable
add_executable(1b ${SOURCES})

# Link SDL2 libraries
target_link_libraries(1b
  SDL2::Main
    SDL2::Image
    SDL2::TTF
)


target_compile_options(1b PRIVATE
    -O3         # Optimization level 3
    -Wall       # Enable all warnings
    -Wextra     # Enable extra warnings
    -pedantic   # Enable pedantic mode
    # Add more flags as needed
)

# Include header files for SDL2, SDL_image, and SDL_ttf
target_include_directories(1b PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    src
)


