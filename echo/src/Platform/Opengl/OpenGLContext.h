#pragma once 
#include "Renderer/RenderContext.h"

struct GLFWwindow;

namespace Echo
{
    class OpenGLContext : public RenderContext
    {
        public: 
            OpenGLContext(GLFWwindow* windowHandle);
            void Init() override;
            void SwapBuffers() override;
        private:
            GLFWwindow* m_WindowHandle;
    };
}
