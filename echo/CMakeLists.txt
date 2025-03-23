cmake_minimum_required(VERSION 3.16)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fPIC" )

set(CMAKE_CXX_STANDARD 17)

cmake_policy(SET CMP0069 NEW) 
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

project(Echo)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/stb_image)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/imguiInclude)

add_library(Echo SHARED 
                        src/Application.cpp
                        src/Log.cpp
                        src/Platform/Linux/LinuxWindow.cpp
                        src/Platform/Opengl/imguiRendererOpengl3.cpp
                        src/Layer.cpp
                        src/LayerStack.cpp
                        src/ImGui/ImGuiLayer.cpp)

# IF(WIN32)
#     target_compile_definitions(Echo PUBLIC EC_PLATFORM_WINDOWS = 1)
#     target_compile_definitions(Echo PUBLIC HAZEL_API = 1)
# ENDIF()

target_include_directories(Echo PUBLIC "src/")

target_precompile_headers(Echo PRIVATE "src/ecpch.h")

# add_library(Echo)

# target_sources(Echo PRIVATE
#     src/Application.cpp
#     src/Log.cpp
#     src/Application.h
#     src/Core.h
#     src/Echo.h
#     src/EntryPoint.h
#     src/Log.h
# )

target_link_libraries(Echo PRIVATE spdlog glfw glm glad stb_image imgui)

