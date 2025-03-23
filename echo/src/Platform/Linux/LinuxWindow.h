#pragma once
#include "WindowTemplate.h"
#include <GLFW/glfw3.h>
#include <functional>

namespace Echo 
{
    class LinuxWindow : public Window
    {
        public:
            LinuxWindow(const WindowProps& props);
            virtual ~LinuxWindow();

            void OnUpdate() override;

            inline unsigned int GetWidth() const override { return m_Data.Width;}
            inline unsigned int GetHeight() const override { return m_Data.Height;}

            inline void SetEventCallback(const std::function<void (Event &)> &callback) override { m_Data.EventCallback = callback;}
            GLFWwindow* GetWindowData() override {return m_Window;}
            void SetVSync(bool enabled) override;
            bool inline IsVSync() const override {return m_Data.VSync;};
        private:
            virtual void Init(const WindowProps& props);
            virtual void Shutdown();
        private:
            GLFWwindow* m_Window;
            
            struct WindowData
            {
                std::string Title;
                unsigned int Width, Height;
                bool VSync;
                std::function<void(Event&)> EventCallback;
            };

            WindowData m_Data;
    };
};
