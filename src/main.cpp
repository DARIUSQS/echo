#include "Events/KeyEvent.h"
#include "Log.h"
#include <Echo.h>

class ExempleLayer : public Echo::Layer
{
public:
    ExempleLayer()
        : Layer("Exemple") {}

    void OnUpdate() override
    {
    }

    void OnEvent(Echo::Event& event) override
    {
        if(event.GetEventType() == Echo::EventType::KeyPressed)
        {
            Echo::KeyEventPressed& e = (Echo::KeyEventPressed&) event;
            if(e.GetKeyCode() == EC_KEY_W) EC_TRACE("W Pressed");
        }
    }
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
