cmake_minimum_required(VERSION 3.16)

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# cmake_policy(SET CMP0069 NEW) 
# set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
# set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

IF(WIN32)
    add_compile_definitions(PLATFORM_WINDOWS)
ENDIF()

project(sandbox)

add_subdirectory(echo)

add_executable(sandbox src/main.cpp)

# file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "include/*.cpp")

# target_sources(opengl PRIVATE ${SOURCE_FILES})

target_include_directories(sandbox PUBLIC "src/")

target_link_libraries(sandbox PUBLIC Echo)
