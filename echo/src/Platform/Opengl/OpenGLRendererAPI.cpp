#include "Platform/Opengl/OpenGLRendererAPI.h"
#include <glad.h>

namespace Echo 
{
    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) 
    {
        glClearColor(color.r, color.g, color.b, color.w);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndex(const std::shared_ptr<VertexArray>& vao)
    {
        glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}
