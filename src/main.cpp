#include <Echo.h>

class ExempleLayer : public Echo::Layer
{
public:
    ExempleLayer()
        : Layer("Exemple") {}

    void OnUpdate() override
    {
        EC_INFO("{0} Layer::Update", m_DebugName);
    }

    void OnEvent(Echo::Event& event) override
    {
        EC_INFO("Layer[Exemple]: {0}", event);
    }
};

class Sandbox : public Echo::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExempleLayer());
        PushLayer(new Echo::ImGuiLayer());
    }
    
    ~Sandbox()
    {

    }
};

Echo::Application* Echo::CreateApplication()
{
    return new Sandbox();
}
