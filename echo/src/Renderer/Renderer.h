#pragma once

#include "RenderAPI.h"

namespace Echo 
{
    class Renderer
    {
        public:
            void BeginScene();
            void EndScene();

            static void Submit(const std::shared_ptr<VertexArray>& vao);

            inline static RendererAPI::API GetAPI() {return RendererAPI::GetAPI();}
    };
}
