#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/Opengl/OpenGLVertexArray.h"

namespace Echo 
{
    VertexArray* VertexArray::Create()
    {
        switch(Renderer::GetAPI()) 
        {
            case RendererAPI::API::None: EC_ASSERT(true, "RendererAPI::None is not currently supported") return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
        }
        return nullptr; 
    }
}
