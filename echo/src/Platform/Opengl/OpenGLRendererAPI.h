#pragma once 
#include "RenderAPI.h"

namespace Echo 
{
    class OpenGLRendererAPI : public RendererAPI
    {
        public:
            virtual void SetClearColor(const glm::vec4& color) override;
            virtual void Clear() override;

            virtual void DrawIndex(const Ref<VertexArray>& vao) override;
    };
}
