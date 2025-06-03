#pragma once

#include "RenderAPI.h"
#include "Camera.h"
#include "Shader.h"

namespace Echo 
{
    class Renderer
    {
        public:
            static void BeginScene(OrthographicCamera& camera);
            static void EndScene();

            static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vao);

            inline static RendererAPI::API GetAPI() {return RendererAPI::GetAPI();}

        private:
            struct SceneData 
            {
                glm::mat4 ViewProjectionMatrix;
            };

            static SceneData* m_SceneData;
    };
}
