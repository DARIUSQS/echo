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

add_library(Echo STATIC
                        src/Application.cpp
                        src/DeltaTime.cpp
                        src/Log.cpp
                        src/InputTemplate.cpp
                        src/Platform/Linux/LinuxWindow.cpp
                        src/Platform/Linux/LinuxInput.cpp
                        src/Platform/Opengl/OpenGLContext.cpp
                        src/Layer.cpp
                        src/LayerStack.cpp
                        src/ImGui/imguiRendererOpengl3.cpp
                        src/ImGui/ImGuiLayer.cpp
                        src/Renderer/Shader.cpp
                        src/Renderer/Buffer.cpp
                        src/Platform/Opengl/OpenGLBuffer.cpp
                        src/Renderer/Renderer.cpp
                        src/Renderer/RenderAPI.cpp
                        src/Renderer/RenderCommand.cpp
                        src/Platform/Opengl/OpenGLVertexArray.cpp
                        src/Platform/Opengl/OpenGLRendererAPI.cpp
                        src/Platform/Opengl/OpenGLShader.cpp
                        src/Renderer/VertexArray.cpp
                        src/Renderer/Camera.cpp
                    )

# IF(WIN32)
#     target_compile_definitions(Echo PUBLIC EC_PLATFORM_WINDOWS = 1)
#     target_compile_definitions(Echo PUBLIC HAZEL_API = 1)
# ENDIF()

target_include_directories(Echo PUBLIC "src/")
target_include_directories(Echo PUBLIC "src/Renderer/")

target_precompile_headers(Echo PUBLIC "src/ecpch.h")

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

target_link_libraries(Echo PUBLIC glm spdlog glfw glad stb_image imgui)

