#include "Renderer.h"
#include "RenderCommand.h"
#include "Shader.h"

namespace Echo
{
    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(const Camera& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray> &vao, const glm::mat4& model)
    {
        shader->Bind();
        shader->UploadUniformMat4(m_SceneData->ViewProjectionMatrix, "u_ViewProjection");
        shader->UploadUniformMat4(model, "u_Model");

        vao->Bind();
        RenderCommand::DrawIndexed(vao);
    }
}
