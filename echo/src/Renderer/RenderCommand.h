#pragma once 
#include "RenderAPI.h"
#include "VertexArray.h"
namespace Echo 
{
    class RenderCommand 
    {
        public:
            inline static void DrawIndexed(const Ref<VertexArray>& vao)
            {
                s_RendererAPI->DrawIndex(vao);
            }
                
            inline static void Clear()
            {
                s_RendererAPI->Clear();
            }

            inline static void SetClearColor(const glm::vec4& color)
            {
               s_RendererAPI->SetClearColor(color);
            }

        private:
            static RendererAPI* s_RendererAPI;
    };
}
