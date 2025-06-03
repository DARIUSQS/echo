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

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
        : m_Camera(-1.6f, 1.6f, 0.9f, -0.9f)
    {
        EC_ASSERT(!s_Instance, "Application already created")
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
        
        /// Triangle
        
        float vertices[3 * 4] =  /// Pos Color
        {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
        };

        unsigned int indices[6] = {0, 1, 2, 1, 2, 3};

        m_VertexArray.reset(VertexArray::Create());

        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        m_VertexBuffer->Bind();

        BufferLayout layout( 
        {
            {ShaderDataType::Float3, "Position"},
            // {ShaderDataType::Float4, "Color"}
        });

        m_VertexBuffer->SetLayout(layout);
        
        m_VertexArray->Bind();
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)));
        m_IndexBuffer->Bind();
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

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
            m_Camera.SetPosition({0.0f, 0.0f, 0.0f});
            m_Camera.SetRotation(32.0f);

            Renderer::BeginScene(m_Camera);
            RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
            RenderCommand::Clear();

            Renderer::Submit(m_Shader, m_VertexArray);

            Renderer::EndScene();

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
