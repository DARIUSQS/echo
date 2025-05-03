#include "ecpch.h"
#include <glad.h>
#include "Application.h"
#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include <GLFW/glfw3.h>

namespace Echo {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application() 
    {
        EC_ASSERT(!s_Instance, "Application already created")
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

        for(auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if(e.m_Handled) break;
        }

        // EC_CORE_TRACE("{0}", e);      
    }

    Application::~Application() {}
    
    void Application::Run()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1);

        while(m_Running)
        {
            glClear(GL_COLOR_BUFFER_BIT);

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
        /// Resize
        return true;
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}
