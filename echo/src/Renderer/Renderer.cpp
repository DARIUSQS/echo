#include "Renderer.h"
#include "RenderCommand.h"

namespace Echo
{
    Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray> &vao)
    {
        shader->Bind();
        shader->UploadUniformMat4(m_SceneData->ViewProjectionMatrix, "u_ViewProjection");
        vao->Bind();
        RenderCommand::DrawIndexed(vao);
    }
}
