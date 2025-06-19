#include <Echo.h>

class ExempleLayer : public Echo::Layer
{
public:
    ExempleLayer()
        : Layer("Exemple"), m_Camera(glm::radians(60.f), 16.0f/9.0f, 0.1f, 100.0f), m_PlayerDir(0.0f), m_PlayerSpeed(2.0f), m_PlayerPos({0.0f, 0.0f, -1.0f}), isPaused(false), m_Color({0.4f, 0.3f, 0.2f})
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

        m_Shader.reset(Echo::Shader::Create("Assets/Shaders/test.shader"));
    }

    void OnUpdate() override
    {
        if(!isPaused) m_Camera.SetRotation(Echo::Input::GetMouseX(), Echo::Input::GetMouseY(), 0.1f);

        m_Camera.SetPosition(m_PlayerPos);

        m_PlayerDir = {0.0f, 0.0f, 0.0f};
        if(Echo::Input::IsKeyPressed(EC_KEY_W)) m_PlayerDir += m_Camera.GetCameraFront();
        if(Echo::Input::IsKeyPressed(EC_KEY_D)) m_PlayerDir += glm::cross(m_Camera.GetCameraFront(), m_Camera.GetCameraUp());
        if(Echo::Input::IsKeyPressed(EC_KEY_S)) m_PlayerDir -= m_Camera.GetCameraFront();
        if(Echo::Input::IsKeyPressed(EC_KEY_A)) m_PlayerDir -= glm::cross(m_Camera.GetCameraFront(), m_Camera.GetCameraUp());;
        if(Echo::Input::IsKeyPressed(EC_KEY_E)) m_PlayerDir += m_Camera.GetCameraUp();
        if(Echo::Input::IsKeyPressed(EC_KEY_Q)) m_PlayerDir -= m_Camera.GetCameraUp();
        if(Echo::Input::IsKeyPressed(EC_KEY_LEFT_SHIFT)) m_RunningMult = 2.0f;
        else m_RunningMult = 1.0f;

        if(glm::length(m_PlayerDir)) m_PlayerDir = glm::normalize(m_PlayerDir);
        
        m_PlayerPos += m_PlayerDir * m_PlayerSpeed * m_RunningMult * Echo::DeltaTime::Seconds();   

        ///// SHADER COLOR

        std::dynamic_pointer_cast<Echo::OpenGLShader>(m_Shader)->UploadUniformVec4(glm::vec4(m_Color, 1.0f), "u_Color");

        Echo::Renderer::BeginScene(m_Camera);
        Echo::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Echo::RenderCommand::Clear();
    
        Echo::Renderer::Submit(m_Shader, m_VertexArray);

        Echo::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Color");
        ImGui::ColorPicker3("Pick Color", glm::value_ptr(m_Color));
        ImGui::Separator();
        Echo::CameraRotation rot = m_Camera.GetRotation();
        ImGui::InputDouble("Pitch", &rot.pitch);
        ImGui::InputDouble("Yaw", &rot.yaw);
        ImGui::InputDouble("Roll", &rot.roll);
        ImGui::End();
    }

    void OnEvent(Echo::Event& event) override
    {
        Echo::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Echo::KeyEventPressed>(BIND_EVENT_FN(ExempleLayer::OnKeyPressedEvent));
    }

    bool OnKeyPressedEvent(Echo::KeyEventPressed& event)
    {
        if(event.GetKeyCode() == EC_KEY_P)
        {
            if(!isPaused) Echo::Application::Get().GetWindow().UnlockCursor();
            else Echo::Application::Get().GetWindow().LockCursor();
            isPaused = !isPaused;
        }
        return 0;
    }

private:

    glm::vec3 m_PlayerDir;
    glm::vec3 m_PlayerPos;
    glm::vec3 m_Color;
    float m_PlayerSpeed;
    float m_RunningMult;
    bool isPaused;


    Echo::PerspectiveCamera m_Camera;
    Echo::Ref<Echo::Shader> m_Shader;
    Echo::Ref<Echo::VertexArray> m_VertexArray;
    Echo::Ref<Echo::VertexBuffer> m_VertexBuffer;
    Echo::Ref<Echo::IndexBuffer> m_IndexBuffer;
};

class Sandbox : public Echo::Application
{
public:
    Sandbox()
    {
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
