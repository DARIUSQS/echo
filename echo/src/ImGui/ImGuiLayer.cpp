#include "ImGuiLayer.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Log.h"
#include "Events/Event.h"
#include "Events/MouseEvent.h"
#include <glad.h>
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imguiRendererOpengl3.h"
#include "Application.h"

namespace Echo
{
    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {

    }

    ImGuiLayer::~ImGuiLayer()
    {

    }
    
    void ImGuiLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);

        dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&ImGuiLayer::OnMouseButtonPressedEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&ImGuiLayer::OnMouseButtonReleasedEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseMovedEvent>(std::bind(&ImGuiLayer::OnMouseMovedEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseScrollEvent>(std::bind(&ImGuiLayer::OnMouseScrollEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyEventPressed>(std::bind(&ImGuiLayer::OnKeyPressedEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyEventTyped>(std::bind(&ImGuiLayer::OnKeyTypedEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyEventReleased>(std::bind(&ImGuiLayer::OnKeyReleasedEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&ImGuiLayer::OnWindowResizeEvent, this, std::placeholders::_1));
    }

    void ImGuiLayer::OnUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
        m_Time = time;
    }

    void ImGuiLayer::OnImGuiRender()
    {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::End()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui::LoadIniSettingsFromDisk("imgui.ini");
        ImGui::SaveIniSettingsToMemory();

        ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(Application::Get().GetWindow().GetWindowData()), false);
        ImGui_ImplOpenGL3_Init("#version 410");

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Docking
 
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;
    }
    
    void ImGuiLayer::OnDetach()
    {
        ImGui::SaveIniSettingsToDisk("imgui.ini");
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;

        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = false;

        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());
        return false;
    }

    bool ImGuiLayer::OnMouseScrollEvent(MouseScrollEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.GetXOffset();
        io.MouseWheel += e.GetYOffset();
        return false;
    }
    bool ImGuiLayer::OnKeyPressedEvent(KeyEventPressed& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
        return false;
    }
    bool ImGuiLayer::OnKeyReleasedEvent(KeyEventReleased& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = false;
        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyEventTyped& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        int keycode = e.GetKeyCode();
        if(keycode > 0 && keycode < 0x10000)
            io.AddInputCharacter(keycode);

        return false;
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

        return false;
    }
}
