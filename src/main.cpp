#include <Echo.h>
#include "DeltaTime.h"

class ExempleLayer : public Echo::Layer
{
public:
    ExempleLayer()
        : Layer("Exemple"), m_Camera(glm::radians(60.f), 16.0f/9.0f, 0.1f, 100.0f), m_PlayerDir(0.0f), m_PlayerSpeed(2.0f), m_PlayerPos({0.0f, 0.0f, -1.0f})
    {
        float vertices[3 * 8] = 
        {
            -0.5f, -0.5f, 0.0f, /// 1
            0.5f, -0.5f, 0.0f, /// 2
            -0.5f, 0.5f, 0.0f, /// 3
            0.5f, 0.5f, 0.0f, /// 4
            0.5f, 0.5f, -1.0f, 
            0.5f, -0.5f, -1.0f, 
            -0.5f, 0.5f, -1.0f, 
            -0.5f, -0.5f, -1.0f
        };
        
        unsigned int indices[36] = {0, 1, 2, 1, 2, 3, 3, 1, 5, 3, 5, 4, 1, 0, 5, 0, 5, 7, 2, 0, 7, 7, 2, 6, 2, 3, 4, 2, 6, 4, 5, 4, 6, 6, 7, 5};


        m_VertexArray.reset(Echo::VertexArray::Create());

        m_VertexBuffer.reset(Echo::VertexBuffer::Create(vertices, sizeof(vertices)));
        m_VertexBuffer->Bind();

        Echo::BufferLayout layout({

                {Echo::ShaderDataType::Float3, "Position"},
        });
        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->Bind();
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        m_IndexBuffer.reset(Echo::IndexBuffer::Create(indices, sizeof(indices)));
        m_IndexBuffer->Bind();
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        m_Shader.reset(new Echo::Shader("Assets/Shaders/test.shader"));
        m_Shader->Compile();
    }

    void OnUpdate() override
    {
        m_Camera.SetRotation(Echo::Input::GetMouseX(), Echo::Input::GetMouseY(), 0.1f);

        EC_WARN(m_Camera.GetRotation());

        m_Camera.SetPosition(m_PlayerPos);

        m_PlayerDir = {0.0f, 0.0f, 0.0f};
        if(Echo::Input::IsKeyPressed(EC_KEY_W)) m_PlayerDir += m_Camera.GetCameraFront();
        if(Echo::Input::IsKeyPressed(EC_KEY_D)) m_PlayerDir += glm::cross(m_Camera.GetCameraFront(), m_Camera.GetCameraUp());
        if(Echo::Input::IsKeyPressed(EC_KEY_S)) m_PlayerDir -= m_Camera.GetCameraFront();
        if(Echo::Input::IsKeyPressed(EC_KEY_A)) m_PlayerDir -= glm::cross(m_Camera.GetCameraFront(), m_Camera.GetCameraUp());;
        if(glm::length(m_PlayerDir)) m_PlayerDir = glm::normalize(m_PlayerDir);
        
        m_PlayerPos += m_PlayerDir * m_PlayerSpeed * Echo::DeltaTime::Seconds();   

        Echo::Renderer::BeginScene(m_Camera);
        Echo::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Echo::RenderCommand::Clear();
    
        Echo::Renderer::Submit(m_Shader, m_VertexArray);

        Echo::Renderer::EndScene();
    }

    void OnEvent(Echo::Event& event) override
    {

    }

private:

    glm::vec3 m_PlayerDir;
    glm::vec3 m_PlayerPos;
    float m_PlayerSpeed;

    Echo::PerspectiveCamera m_Camera;
    std::shared_ptr<Echo::Shader> m_Shader;
    std::shared_ptr<Echo::VertexArray> m_VertexArray;
    std::shared_ptr<Echo::VertexBuffer> m_VertexBuffer;
    std::shared_ptr<Echo::IndexBuffer> m_IndexBuffer;
};

class Sandbox : public Echo::Application
{
public:
    Sandbox()
    {
        PushLayer(new Echo::ImGuiLayer());
        PushLayer(new ExempleLayer());
    }
    
    ~Sandbox()
    {

    }
};

Echo::Application* Echo::CreateApplication()
{
    return new Sandbox();
}
