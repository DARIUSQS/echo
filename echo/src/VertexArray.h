#pragma once
#include "Buffer.h"

namespace Echo 
{
    class VertexArray 
    {
        public:
            ~VertexArray() {}
            
            virtual void Bind() const = 0;
            virtual void unBind() const = 0;

            static VertexArray* Create();
            virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
            virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& vertexBuffer) = 0;
    };
}
