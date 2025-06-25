#include <Echo.h>

class ExempleLayer : public Echo::Layer
{
public:
    ExempleLayer()
        : Layer("Exemple"), m_Camera(glm::radians(60.f), 16.0f/9.0f, 0.1f, 100.0f), m_PlayerDir(0.0f), m_PlayerSpeed(2.0f), m_PlayerPos({0.0f, 0.0f, -1.0f}), isPaused(false), m_Color({0.4f, 0.3f, 0.2f})
    {
        float vertices[16 * 5] = 
        {
            ////  Position //// /// Tex Coords ///
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, /// 1 left bot  0
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  /// 2 right bot 1
            0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  /// 2 left bot  2
            -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,  /// 3 left top  3
            -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,  /// 3 left bot  4
            0.5f, 0.5f, 0.0f, 1.0f, 1.0f, /// 4 right top   5
            0.5f, 0.5f, 0.0f, 0.0f, 1.0f, /// 4 left top    6
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, /// 4 right bot   7
            0.5f, 0.5f, -1.0f, 1.0f, 1.0f, /// 5 right top  8
            0.5f, -0.5f, -1.0f, 1.0f, 0.0f, /// 6 right bot 9
            0.5f, -0.5f, -1.0f, 1.0f, 1.0f, /// 6 right top 10
            -0.5f, 0.5f, -1.0f, 0.0f, 1.0f, /// 7 left top  11
            -0.5f, 0.5f, -1.0f, 1.0f, 1.0f, /// 7 right top 12
            -0.5f, -0.5f, -1.0f, 0.0f, 1.0f, ///8 left top   13
            -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, ///8 left bot   14
            -0.5f, -0.5f, -1.0f, 1.0f, 0.0f ///8 right bot   15
        };
        
        unsigned int indices[36] = {0, 1, 3, 1, 3, 5, 0, 1, 13, 1, 13, 10, 2, 9, 6, 9, 6, 8, 4, 7, 11, 7, 11, 8, 0, 15, 3, 15, 3, 12, 14, 9, 11, 9, 11, 8};


        m_VertexArray.reset(Echo::VertexArray::Create());

        m_VertexBuffer.reset(Echo::VertexBuffer::Create(vertices, sizeof(vertices)));
        m_VertexBuffer->Bind();

        Echo::BufferLayout layout({
                {Echo::ShaderDataType::Float3, "Position"},
                {Echo::ShaderDataType::Float2, "Tex Coords"},
        });
        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->Bind();
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        m_IndexBuffer.reset(Echo::IndexBuffer::Create(indices, sizeof(indices)));
        m_IndexBuffer->Bind();
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        m_Shader.reset(Echo::Shader::Create("Assets/Shaders/test.shader"));
        m_BoxTexture = Echo::Texture2D::Create("Assets/Textures/tex.png");
        m_TransparentTexture = Echo::Texture2D::Create("Assets/Textures/transparent.png");
       
        std::dynamic_pointer_cast<Echo::OpenGLShader>(m_Shader)->Bind();
        std::dynamic_pointer_cast<Echo::OpenGLShader>(m_Shader)->UploadUniformInt(0, "u_Texture");
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

        Echo::Renderer::BeginScene(m_Camera);
        Echo::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Echo::RenderCommand::Clear();

        m_BoxTexture->Bind(0);
        Echo::Renderer::Submit(m_Shader, m_VertexArray);
        m_TransparentTexture->Bind(0);
        Echo::Renderer::Submit(m_Shader, m_VertexArray, glm::translate(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 0.0f)));

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
    Echo::Ref<Echo::Texture2D> m_BoxTexture, m_TransparentTexture;
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
