#pragma once
#include "Renderer/RenderContext.h"
#include "WindowTemplate.h"
#include "imgui/imgui_internal.h"
#include <GLFW/glfw3.h>
#include <functional>

namespace Echo 
{
    class LinuxWindow : public Window
    {
        public:
            LinuxWindow(const WindowProps& props);
            virtual ~LinuxWindow();

            virtual void OnUpdate() override;

            virtual inline unsigned int GetWidth() const override { return m_Data.Width;}
            virtual inline unsigned int GetHeight() const override { return m_Data.Height;}

            virtual inline void SetEventCallback(const std::function<void (Event &)> &callback) override { m_Data.EventCallback = callback;}
            virtual void* GetWindowData() override {return m_Window;}
            virtual void SetVSync(bool enabled) override;
            virtual bool inline IsVSync() const override {return m_Data.VSync;};
            
            virtual void LockCursor() const override;
            virtual void UnlockCursor() const override;

        private:
            virtual void Init(const WindowProps& props);
            virtual void Shutdown();
        private:
            GLFWwindow* m_Window;
            RenderContext* m_Context;
            
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
