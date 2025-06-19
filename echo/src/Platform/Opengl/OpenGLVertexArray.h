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

            virtual const Ref<IndexBuffer>& GetIndexBuffer() const override {return m_IndexBuffer;};

            virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
            virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
        private:
            std::vector<Ref<VertexBuffer>> m_VertexBuffers;
            Ref<IndexBuffer> m_IndexBuffer;
            uint32_t m_RendererID;
    };
}
