#pragma once
#include "Buffer.h"

namespace Echo 
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
        public:
            OpenGLVertexBuffer(float* vertices, uint32_t size);
            ~OpenGLVertexBuffer();
        
            void Bind() const override;
            void unBind() const override;

        private:
            uint32_t m_RendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
        public:
            OpenGLIndexBuffer(uint32_t* indices, uint32_t size);
            ~OpenGLIndexBuffer();
        
            void Bind() const override;
            void unBind() const override;

        private:
            uint32_t m_RendererID;
    };
}
