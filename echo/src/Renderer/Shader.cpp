#include "ecpch.h"
#include "Renderer.h"
#include "Shader.h"
#include "Platform/Opengl/OpenGLShader.h"

namespace Echo 
{
   Shader* Shader::Create(const std::string &shaderSourcePath)
   {
        switch (Renderer::GetAPI()) {
            case Echo::RendererAPI::API::OpenGL : return new OpenGLShader(shaderSourcePath);
            case Echo::RendererAPI::API::None : EC_ASSERT(1, "None is not supported as an rendering API") return nullptr;
        }
        return nullptr;
   }
}
