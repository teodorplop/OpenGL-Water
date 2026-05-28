cmake_minimum_required(VERSION 3.15)
project(OpenGL_Water CXX)

# Match your old vcxproj preprocessor flag just in case
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

# Force C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include your local Source directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source)

# Gather all local source files recursively
file(GLOB_RECURSE SOURCE_FILES 
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/Classes/*.cpp"
)

# Define the executable
add_executable(OpenGL_Water ${SOURCE_FILES})

# Link directly to the system-wide Linux libraries you just installed
target_link_libraries(OpenGL_Water PRIVATE
    GL          # Core Linux OpenGL driver
    GLEW        # Replaces glew32.lib
    glut        # Replaces freeglut.lib
    glfw        # Replaces glfw3.lib
    freeimage   # Replaces FreeImage.lib
    m           # Linux standard C++ math library
)