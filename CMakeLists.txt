cmake_minimum_required(VERSION 3.12)
project(OpenGLApp)

# Set the C++ standard to C++17 for all targets in this project
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the source files from the source directory
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/*.cpp" "${CMAKE_SOURCE_DIR}/*.h" "${CMAKE_SOURCE_DIR}/imgui/*.cpp" "${CMAKE_SOURCE_DIR}/imgui/*.h" "glad.c")
message(${SOURCES})

# Add the executable target and link libraries
add_executable(OpenGLApp ${SOURCES})

# Set the additional include directories
target_include_directories(OpenGLApp PRIVATE
    "${CMAKE_SOURCE_DIR}/Libraries/include"
    "${CMAKE_SOURCE_DIR}/imgui"   # Assuming imgui is in the same directory as CMakeLists.txt
    # Add other include directories here if needed
)
# print out the include directories
get_target_property(OpenGLApp_INCLUDE_DIRS OpenGLApp INCLUDE_DIRECTORIES)
message(STATUS "Include directories for OpenGLApp: ${OpenGLApp_INCLUDE_DIRS}")

# Use find_library to locate opengl32.lib
find_library(OPENGL_LIB NAMES opengl32.lib)
if (NOT OPENGL_LIB)
    message(FATAL_ERROR "OpenGL library (opengl32.lib) not found.")
endif()
# Set the path to glfw3.lib
set(GLFW_LIB "${CMAKE_SOURCE_DIR}/Libraries/lib/glfw3.lib")
# Set the required libraries to link
target_link_libraries(OpenGLApp PRIVATE
    ${GLFW_LIB}
    ${OPENGL_LIB}
)
