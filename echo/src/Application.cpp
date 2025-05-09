#include "ecpch.h"
#include <glad.h>
#include "Application.h"
#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include <GLFW/glfw3.h>
#include "Renderer/Shader.h"
#include "Buffer.h"

namespace Echo {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application() 
    {
        EC_ASSERT(!s_Instance, "Application already created")
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
        
        /// Triangle
        
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);

        float vertices[3 * 3] = 
        {
            -0.5f, -0.5f, 0.0f, 
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f
        };

        unsigned int indices[3] = {0, 1, 2};

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        m_VertexBuffer->Bind();

        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        m_Shader.reset(new Shader("Assets/Shaders/test.shader"));
        m_Shader->Compile();
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

        while(m_Running)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1);
            glClear(GL_COLOR_BUFFER_BIT); 
 
            m_Shader->Bind();
            glBindVertexArray(m_VAO);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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
