#pragma once 
#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Layer.h"
#include "WindowTemplate.h"
#include "LayerStack.h"
#include "Renderer/Shader.h"
#include "Buffer.h"
#include "VertexArray.h"
#include "Camera.h"
#include "ImGui/ImGuiLayer.h"

namespace Echo {
   ECHO_API class Application
   {
        public:
            Application();
            virtual ~Application();

            void Run();

            void OnEvent(Event& e);

            void PushLayer(Layer* layer);
            void PushOverlay(Layer* overlay);

            inline Window& GetWindow() { return *m_Window;}
            inline static Application& Get() { return *s_Instance;}
        private: 
            bool OnWindowClose(WindowCloseEvent& e);
            bool OnWindowResize(WindowResizeEvent& e);

            Scope<Window> m_Window;
            bool m_Running = true;

            LayerStack m_LayerStack;
            ImGuiLayer* m_ImGuiLayer;

            static Application* s_Instance;
   };
   // Defined in CLIENT
   Application* CreateApplication();
}
