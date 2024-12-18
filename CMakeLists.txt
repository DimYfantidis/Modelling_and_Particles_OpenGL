# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Define the project name and language
project(modelling_and_particles LANGUAGES C)

# Specify include directories
include_directories(
    include
    dependencies/freeglut/include
)

# Specify the library directories
link_directories(dependencies/freeglut/lib/x64)

# Add source files
file(GLOB SOURCES "src/*.c")

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} freeglut)

# Post-build step to copy the DLL
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${CMAKE_SOURCE_DIR}/dependencies/freeglut/bin/x64/freeglut.dll"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
