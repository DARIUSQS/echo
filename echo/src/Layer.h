#pragma once
#include "Events/Event.h"

namespace Echo 
{
    class Layer 
    {
    public: 
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& event) {}

    protected:
        std::string m_DebugName;
    };
}
