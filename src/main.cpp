#include <Echo.h>
#include "InputTemplate.h"

class ExempleLayer : public Echo::Layer
{
public:
    ExempleLayer()
        : Layer("Exemple"), m_Camera(-1.6f, 1.6f, 0.9f, -0.9f), m_CameraPos(0.0f), m_PlayerSpeed(-0.01f)
    {
        float vertices[4 * 4] = 
        {
            -0.5f, -0.5f, 0.0f, 
            0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.0f
        };
        
        unsigned int indices[6] = {0, 1, 2, 1, 2, 3};


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
        if(Echo::Input::IsKeyPressed(EC_KEY_W)) m_CameraPos.y += m_PlayerSpeed;
        if(Echo::Input::IsKeyPressed(EC_KEY_D)) m_CameraPos.x += m_PlayerSpeed;
        if(Echo::Input::IsKeyPressed(EC_KEY_S)) m_CameraPos.y -= m_PlayerSpeed; 
        if(Echo::Input::IsKeyPressed(EC_KEY_A)) m_CameraPos.x -= m_PlayerSpeed;

        m_Camera.SetPosition(m_CameraPos);


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

    glm::vec3 m_CameraPos;
    float m_PlayerSpeed;

    Echo::OrthographicCamera m_Camera;
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
