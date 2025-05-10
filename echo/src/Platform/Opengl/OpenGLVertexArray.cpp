#include "OpenGLVertexArray.h"
#include <glad.h>

namespace Echo 
{
    static uint32_t ShaderDataTypeOpenGLType(ShaderDataType type)
    {
        switch (type) 
        {
            case ShaderDataType::Float: return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Mat3: return GL_FLOAT;
            case ShaderDataType::Mat4: return GL_FLOAT;
            case ShaderDataType::Int: return GL_INT;
            case ShaderDataType::Int2: return GL_INT;
            case ShaderDataType::Int3: return GL_INT;
            case ShaderDataType::Int4: return GL_INT;
            case ShaderDataType::Bool: return GL_BOOL;
        }
        EC_ASSERT(false, "Unknown ShaderDataType");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }
    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }
    void OpenGLVertexArray::unBind() const
    {
        glBindVertexArray(0);
    }
    void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        m_VertexBuffers.push_back(vertexBuffer); 
        Bind();
        vertexBuffer->Bind();
        BufferLayout layout = vertexBuffer->GetLayout();
        int index = 0;
        for(const auto& element : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.size, ShaderDataTypeOpenGLType(element.type), GL_FALSE, vertexBuffer->GetLayout().GetStride(), (void*)element.offset);
            EC_INFO("{0} {1} {2} {3} {4}", element.size, vertexBuffer->GetLayout().GetStride(), element.offset, index, ShaderDataTypeOpenGLType(element.type));
            index++;
        }

    }
    void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        Bind();
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }
}
