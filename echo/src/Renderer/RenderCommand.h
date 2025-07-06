#pragma once 
#include "RenderAPI.h"
#include "VertexArray.h"
namespace Echo 
{
    class RenderCommand 
    {
        public:
            inline static void Init()
            {
                s_RendererAPI->Init();
            }

            inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
            {
                s_RendererAPI->SetViewport(x, y, width, height);
            }

            inline static void DrawIndexed(const Ref<VertexArray>& vao)
            {
                s_RendererAPI->DrawIndex(vao);
            }

            inline static void DrawUnIndexed(const Ref<VertexArray>& vao)
            {
                s_RendererAPI->DrawUnIndex(vao);
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
