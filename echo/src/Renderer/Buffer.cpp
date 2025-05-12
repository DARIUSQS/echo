#include "Buffer.h"
#include "Platform/Opengl/OpenGLBuffer.h"
#include "Renderer.h"

namespace Echo 
{
    VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch(Renderer::GetAPI()) 
        {
            case RendererAPI::API::None: EC_ASSERT(true, "RendererAPI::None is not currently supported") return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
        }
        return nullptr; 
    }

    IndexBuffer* IndexBuffer::Create(uint32_t *indices, uint32_t size)
    {
        switch(Renderer::GetAPI()) 
        {
            case RendererAPI::API::None: EC_ASSERT(true, "RendererAPI::None is not currently supported") return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, size);
        }
        return nullptr; 
    }
}
