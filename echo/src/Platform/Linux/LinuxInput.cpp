#include "GLFW/glfw3.h"
#include "InputTemplate.h"
#include "Application.h"

namespace Echo
{
    bool Input::IsKeyPressed(int keycode)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowData());
        auto state = glfwGetKey(window, keycode);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool Input::IsMouseButtonPressed(int button)
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowData());
        return glfwGetMouseButton(window, button);
    }

    std::pair<float, float> Input::GetMousePos()
    {
        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowData());
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return {x,y};
    }

    float Input::GetMouseX()
    {
        auto[x,y] = Input::GetMousePos();
        return x;
    }

    float Input::GetMouseY()
    {
        auto[x,y] = Input::GetMousePos();
        return y;
    }
}

