#include "GLFW/glfw3.h"
#include "LinuxInput.h"
#include "Application.h"

namespace Echo
{
    bool InputGlfw::IsKeyPressedImpl(int keycode)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowData());
        auto state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool InputGlfw::IsMouseButtonPressedImpl(int button)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowData());
        return glfwGetMouseButton(window, button);
    }

    std::pair<float, float> InputGlfw::GetMousePosImpl()
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowData());
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return {x,y};
    }

    float InputGlfw::GetMouseXImpl()
    {
        auto[x,y] = GetMousePosImpl();
        return x;
    }

    float InputGlfw::GetMouseYImpl()
    {
        auto[x,y] = GetMousePosImpl();
        return y;
    }
}

