#include "LayerStack.h"

namespace Echo 
{
    LayerStack::LayerStack()
    {
        m_LayerStart = m_Layers.begin();
    }

    LayerStack::~LayerStack()
    {
        for(Layer* layer : m_Layers)
        {
            layer->OnDetach();
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        m_Layers.emplace(m_Layers.begin(), layer);
        layer->OnAttach();
        m_LayerStart++;
    }

    void LayerStack::PushOverlay(Layer* overlay)
    {
        m_Layers.emplace_back(overlay);
        overlay->OnAttach();
    }
    
    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
        if(it != m_Layers.end())
        {
            (*it)->OnDetach();
            delete (*it);
            m_Layers.erase(it);
            m_LayerStart--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
        if(it != m_Layers.end())
        {
            m_Layers.erase(it);
            m_LayerStart--;
        }
    }
}

