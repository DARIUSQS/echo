#pragma once
#include <ecpch.h>
#include "Buffer.h"
#include "VertexArray.h"

namespace Echo 
{
    class OpenGLVertexArray : public VertexArray
    {
        public:
            OpenGLVertexArray();
            ~OpenGLVertexArray();

            virtual void Bind() const override;
            virtual void unBind() const override;

            virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override {return m_IndexBuffer;};

            virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
            virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
        private:
            std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
            std::shared_ptr<IndexBuffer> m_IndexBuffer;
            uint32_t m_RendererID;
    };
}
