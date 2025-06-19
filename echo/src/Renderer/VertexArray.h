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
            
            virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0; 

            static VertexArray* Create();
            virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
            virtual void SetIndexBuffer(const Ref<IndexBuffer>& vertexBuffer) = 0;
    };
}
