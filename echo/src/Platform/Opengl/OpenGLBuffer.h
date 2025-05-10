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
            
            virtual const BufferLayout& GetLayout() const override {return m_Layout;};
            virtual void SetLayout(const BufferLayout& layout) override;

        private:
            uint32_t m_RendererID;
            BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
        public:
            OpenGLIndexBuffer(unsigned int* indices, uint32_t size);
            ~OpenGLIndexBuffer();
        
            void Bind() const override;
            void unBind() const override;

        private:
            uint32_t m_RendererID;
    };
}
