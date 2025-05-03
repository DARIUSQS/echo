#include "ecpch.h"
#include "OpenGLContext.h"
#include <glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

namespace Echo
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {

    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        EC_ASSERT(status, "Failed to initialize glad");   
    }
    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}
