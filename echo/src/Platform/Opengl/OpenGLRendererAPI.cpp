#include "Platform/Opengl/OpenGLRendererAPI.h"
#include <glad.h>

namespace Echo 
{
    void OpenGLRendererAPI::Init() 
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color) 
    {
        glClearColor(color.r, color.g, color.b, color.w);
    }

    void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndex(const Ref<VertexArray>& vao)
    {
        glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererAPI::DrawUnIndex(const Ref<VertexArray>& vao)
    {
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

}
