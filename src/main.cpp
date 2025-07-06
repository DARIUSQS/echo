#include <Echo.h>

class ExempleLayer : public Echo::Layer
{
public:
    ExempleLayer()
        : Layer("Exemple"), m_CameraController(16.0f / 9.0f, 45.0f, 0.1f, 100.0f), isPaused(false), m_Color({0.4f, 0.3f, 0.2f})
    {
    float vertices[36 * 8] = 
    {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
        }; 
        
        unsigned int indices[36] = {
        0, 8, 6,
        8, 11, 6,
        0, 3, 6,
        3, 4, 6,
        0, 8, 2, 
        8, 15, 2,
        1, 14, 5, 
        14, 5, 13,
        7, 12, 5, 
        12, 5, 13,
        9, 14, 10,
        14, 10, 13
        };

        m_VertexArray.reset(Echo::VertexArray::Create());

        m_VertexBuffer.reset(Echo::VertexBuffer::Create(vertices, sizeof(vertices)));
        m_VertexBuffer->Bind();

        Echo::BufferLayout layout({
                {Echo::ShaderDataType::Float3, "Position"},
                {Echo::ShaderDataType::Float3, "Normals"},
                {Echo::ShaderDataType::Float2, "Tex Coords"},
        });
        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->Bind();
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        m_IndexBuffer.reset(Echo::IndexBuffer::Create(indices, sizeof(indices)));
        m_IndexBuffer->Bind();
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);

        m_Shader.reset(Echo::Shader::Create("Assets/Shaders/test.shader"));
        m_LightShader.reset(Echo::Shader::Create("Assets/Shaders/light.shader"));

        m_BoxTexture = Echo::Texture2D::Create("Assets/Textures/tex.png");
        m_TransparentTexture = Echo::Texture2D::Create("Assets/Textures/transparent.png");
       
        std::dynamic_pointer_cast<Echo::OpenGLShader>(m_Shader)->Bind();
        std::dynamic_pointer_cast<Echo::OpenGLShader>(m_Shader)->UploadUniformFloat(0, "u_Texture");

        std::dynamic_pointer_cast<Echo::OpenGLShader>(m_Shader)->Bind();
        std::dynamic_pointer_cast<Echo::OpenGLShader>(m_Shader)->UploadUniformVec3(glm::vec3(1.0f, 1.0f, 1.0f), "u_LightPos");
    }

    void OnUpdate() override
    {
        if(!isPaused) m_CameraController.OnUpdate();

        ///// SHADER COLOR
        Echo::Renderer::BeginScene(m_CameraController.GetCamera());
        Echo::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
        Echo::RenderCommand::Clear();

        m_BoxTexture->Bind(0);
        Echo::Renderer::SubmitUnindexed(m_Shader, m_VertexArray);
        Echo::Renderer::SubmitUnindexed(m_Shader, m_VertexArray, glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 3.0f, 1.0f)));

        m_TransparentTexture->Bind(0);
        Echo::Renderer::SubmitUnindexed(m_Shader, m_VertexArray, glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 5.0f, 0.0f)));

        Echo::Renderer::SubmitUnindexed(m_LightShader, m_VertexArray, glm::translate(glm::mat4(1.0f), m_lightPos) *
                                                             glm::scale(glm::mat4(1.0f), glm::vec3(0.5, 0.5f, 0.5f)));

        Echo::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Control Panel");
        float cameraPos[3] = {
            m_CameraController.GetCamera().GetPosition().x,
            m_CameraController.GetCamera().GetPosition().y,
            m_CameraController.GetCamera().GetPosition().z};

        ImGui::InputFloat3("Camera Position", cameraPos);
        std::dynamic_pointer_cast<Echo::OpenGLShader>(m_Shader)->UploadUniformVec3(m_CameraController.GetCamera().GetPosition(), "u_CameraPos");

        ImGui::Separator();
        Echo::CameraRotation rot = m_CameraController.GetCamera().GetRotation();
        ImGui::InputDouble("Pitch", &rot.pitch);
        ImGui::InputDouble("Yaw", &rot.yaw);
        ImGui::InputDouble("Roll", &rot.roll);

        ImGui::Separator();
        static float test[2] = {25.0f, 75.0f};
        ImGui::Text("Zoom: ");
        if(ImGui::InputFloat2("Min/Max Zoom", test,"%.3f", ImGuiInputTextFlags_EnterReturnsTrue))
        {
            m_CameraController.SetZoom(test[0], test[1]);
        }
        float zoomValue = m_CameraController.GetZoom();
        ImGui::InputFloat("Zoom value", &zoomValue);
        ImGui::Separator();
        
        static float sens = m_CameraController.GetSensitivity();
        if(ImGui::InputFloat("Sensitivity", &sens))
        {
            m_CameraController.SetSensitivity(sens);
        }
    
        ImGui::Separator();
        static float lightColor[3] = {1.0f, 1.0f, 1.0f};
        ImGui::InputFloat3("Light Color", lightColor);
            std::dynamic_pointer_cast<Echo::OpenGLShader>(m_LightShader)->UploadUniformVec3({lightColor[0], lightColor[1], lightColor[2]}, "u_Color");
            std::dynamic_pointer_cast<Echo::OpenGLShader>(m_Shader)->UploadUniformVec3({lightColor[0], lightColor[1], lightColor[2]}, "u_LightColor");

        static float ambientStrenght = 0.1f;
        ImGui::InputFloat("AmbientStrenght", &ambientStrenght);
            std::dynamic_pointer_cast<Echo::OpenGLShader>(m_Shader)->UploadUniformFloat(ambientStrenght, "u_AmbientStrenght");

        static glm::vec3 lightPos = {1.0f, 1.0f, 1.0f};
        ImGui::DragFloat3("LightPos", &lightPos.x);
        m_lightPos = lightPos;
        std::dynamic_pointer_cast<Echo::OpenGLShader>(m_Shader)->UploadUniformVec3(m_lightPos, "u_LightPos");

        ImGui::End();
    }

    void OnEvent(Echo::Event& event) override
    {
        m_CameraController.OnEvent(event);

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

    glm::vec3 m_lightPos;
    glm::vec3 m_Color;
    bool isPaused;

    Echo::PerspectiveCameraController m_CameraController;
    Echo::Ref<Echo::Shader> m_Shader;
    Echo::Ref<Echo::Shader> m_LightShader;
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
