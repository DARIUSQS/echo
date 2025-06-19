#include "Renderer.h"
#include "RenderCommand.h"
#include "Shader.h"
#include "Platform/Opengl/OpenGLShader.h"

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

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray> &vao, const glm::mat4& model)
    {
        shader->Bind();
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(m_SceneData->ViewProjectionMatrix, "u_ViewProjection");
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4(model, "u_Model");

        vao->Bind();
        RenderCommand::DrawIndexed(vao);
    }
}
