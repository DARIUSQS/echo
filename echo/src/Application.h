#pragma once 
#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Layer.h"
#include "WindowTemplate.h"
#include "LayerStack.h"
#include "Renderer/Shader.h"
#include "Buffer.h"

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

            std::unique_ptr<Window> m_Window;
            bool m_Running = true;

            LayerStack m_LayerStack;

            static Application* s_Instance;

            /// Triangle
            unsigned int m_VAO;
            std::unique_ptr<Shader> m_Shader;
            std::unique_ptr<VertexBuffer> m_VertexBuffer;
            std::unique_ptr<IndexBuffer> m_IndexBuffer;
   };
   // Defined in CLIENT
   Application* CreateApplication();
}
