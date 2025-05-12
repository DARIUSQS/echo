#include "Renderer.h"
#include "RenderCommand.h"

namespace Echo
{
    void Renderer::BeginScene()
    {

    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const std::shared_ptr<VertexArray> &vao)
    {
        RenderCommand::DrawIndexed(vao);
    }
}
