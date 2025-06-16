#pragma once

#include "RenderAPI.h"
#include "Camera.h"
#include "Shader.h"

namespace Echo 
{
    class Renderer
    {
        public:
            static void BeginScene(PerspectiveCamera& camera);
            static void EndScene();

            static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao, const glm::mat4& model = glm::mat4(1.0f));

            inline static RendererAPI::API GetAPI() {return RendererAPI::GetAPI();}

        private:
            struct SceneData 
            {
                glm::mat4 ViewProjectionMatrix;
            };

            static SceneData* m_SceneData;
    };
}
