#pragma once 
#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Layer.h"
#include "WindowTemplate.h"
#include "LayerStack.h"
#include "Renderer/Shader.h"
#include "Buffer.h"
#include "VertexArray.h"

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
            std::shared_ptr<Shader> m_Shader;
            std::shared_ptr<VertexBuffer> m_VertexBuffer;
            std::shared_ptr<IndexBuffer> m_IndexBuffer;
            std::shared_ptr<VertexArray> m_VertexArray;
   };
   // Defined in CLIENT
   Application* CreateApplication();
}
