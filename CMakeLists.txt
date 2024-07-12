cmake_minimum_required(VERSION 3.10)

project(MC-Clone CXX C)

set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")

file(GLOB_RECURSE
    SOURCE_FILES
    src/*.cpp
    src/*.hpp
)


add_executable(MC-Clone ${SOURCE_FILES})

add_subdirectory(lib/glfw)
add_subdirectory(lib/glm)
add_subdirectory(lib/imgui)
add_subdirectory(lib/glad)
include_directories(src)
include_directories(lib/glfw/include)
include_directories(lib/glad/include)
include_directories(lib/glm/glm)
include_directories(lib/imgui)
include_directories(lib/imgui/backends)

target_link_libraries(MC-Clone glad glfw imgui opengl32 glm gdi32)