#include <Echo.h>
#include "DeltaTime.h"

class ExempleLayer : public Echo::Layer
{
public:
    ExempleLayer()
        : Layer("Exemple"), m_Camera(glm::radians(90.f), 16.0f/9.0f, 0.1f, 100.0f), m_PlayerDir(0.0f), m_PlayerSpeed(2.0f)
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

        m_Camera.SetPosition({0.0f, 0.0f, 10.0f});
    }

    void OnUpdate() override
    {

        // EC_WARN("DeltaTime: {0}", Echo::DeltaTime::Miliseconds());

        m_Camera.SetRotation(Echo::Input::GetMouseX(), Echo::Input::GetMouseY());

        Echo::CameraRotation rot;
        EC_WARN("{0}, {1}, {2}", m_Camera.GetPosition().x, m_Camera.GetPosition().y, m_Camera.GetPosition().z);

        m_PlayerDir = {0.0f, 0.0f, 0.0f};
        if(Echo::Input::IsKeyPressed(EC_KEY_W)) m_PlayerDir.y ++;
        if(Echo::Input::IsKeyPressed(EC_KEY_D)) m_PlayerDir.x ++;
        if(Echo::Input::IsKeyPressed(EC_KEY_S)) m_PlayerDir.y --;
        if(Echo::Input::IsKeyPressed(EC_KEY_A)) m_PlayerDir.x --;
        if(glm::length(m_PlayerDir)) m_PlayerDir = glm::normalize(m_PlayerDir);
        
        m_PlayerPos += m_PlayerDir * m_PlayerSpeed * Echo::DeltaTime::Seconds();
        // m_Camera.SetPosition(m_Camera.GetPosition() + m_CameraDir * m_PlayerSpeed * Echo::DeltaTime::Seconds());
    
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_PlayerPos);

        Echo::Renderer::BeginScene(m_Camera);
        Echo::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Echo::RenderCommand::Clear();

        Echo::Renderer::Submit(m_Shader, m_VertexArray, model);

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
