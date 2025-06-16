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

namespace Echo {
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        EC_ASSERT(!s_Instance, "Application already created")
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));
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

            for(Layer* layer : m_LayerStack) layer->OnUpdate();

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
