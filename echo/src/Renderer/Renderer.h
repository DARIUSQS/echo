#pragma once

#include "RenderAPI.h"
#include "Camera.h"
#include "Shader.h"

namespace Echo 
{
    class Renderer
    {
        public:
            static void Init();
            static void OnWindowResize(uint32_t width, uint32_t height);

            static void BeginScene(const Camera& camera);
            static void EndScene();

            static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vao, const glm::mat4& model = glm::mat4(1.0f));
            static void SubmitUnindexed(const Ref<Shader>& shader, const Ref<VertexArray>& vao, const glm::mat4& model = glm::mat4(1.0f));

            inline static RendererAPI::API GetAPI() {return RendererAPI::GetAPI();}

        private:
            struct SceneData 
            {
                glm::mat4 ViewProjectionMatrix;
            };

            static SceneData* m_SceneData;
    };
}
