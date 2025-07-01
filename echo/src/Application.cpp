#include "ecpch.h"
#include <glad.h>
#include "Application.h"
#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include <GLFW/glfw3.h>
#include "Renderer/Shader.h" 
#include "Buffer.h"
#include "Renderer.h"
#include "RenderCommand.h"

#include <imgui/imgui.h>

#include "imgui/backends/imgui_impl_glfw.h"
#include "ImGui/imguiRendererOpengl3.h"

namespace Echo {
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        EC_ASSERT(!s_Instance, "Application already created")
        s_Instance = this;

        m_Window = Scope<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
            
        Renderer::Init();

        m_Window->LockCursor();
        glEnable(GL_DEPTH_TEST);
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if(e.m_Handled) break;
        }
    }

    Application::~Application() {}
    
    void Application::Run()
    {
        while(m_Running)
        {
            float time = (float)glfwGetTime();
            DeltaTime::SetTime(time);

            for(Layer* layer : m_LayerStack) 
            {
                layer->OnUpdate();
            }

            m_ImGuiLayer->Begin();

            for(Layer* layer : m_LayerStack) 
            {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();

            m_Window->OnUpdate();    
        }

    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        glViewport(0, 0, e.GetWidth(), e.GetHeight());
        return true;
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}
