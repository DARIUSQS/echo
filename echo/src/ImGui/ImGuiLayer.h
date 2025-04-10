#pragma once 
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "ecpch.h"
#include "Layer.h"

namespace Echo
{
    class ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();
        
        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& event);

    private:
        bool OnMouseButtonPressedEvent(MouseButtonEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrollEvent(MouseScrollEvent& e);
        bool OnKeyPressedEvent(KeyEventPressed& e);
        bool OnKeyReleasedEvent(KeyEventReleased& e);
        bool OnKeyTypedEvent(KeyEventTyped& e);
        bool OnWindowResizeEvent(WindowResizeEvent& e);

        float m_Time = 0.0f;
    };
}
