cmake_minimum_required(VERSION 3.16)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

cmake_policy(SET CMP0069 NEW) 
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

project(Echo)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/stb_image)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/imguiInclude)

add_library(Echo SHARED src/Application.cpp)

# file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "include/*.cpp")

# target_sources(opengl PRIVATE ${SOURCE_FILES})
IF(WIN32)
    target_compile_definitions(Echo PUBLIC EC_PLATFORM_WINDOWS = 1)
    target_compile_definitions(Echo PUBLIC HAZEL_API = 1)
ENDIF()

target_include_directories(Echo PUBLIC "src/")

target_link_libraries(Echo PRIVATE glfw glm glad stb_image imgui)

