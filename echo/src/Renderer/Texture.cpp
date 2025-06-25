#include "Texture.h"
#include "Platform/Opengl/OpenGLTexture.h"
#include "Renderer.h"

namespace Echo 
{
    Ref<Texture2D> Texture2D::Create(const std::string& path)
    {
        switch(Renderer::GetAPI()) 
        {
            case RendererAPI::API::None: EC_ASSERT(true, "RendererAPI::None is not currently supported") return nullptr;
            case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
        }
        return nullptr; 
    }
}
