#pragma once
#include "GLFW/glfw3.h"
#include "Events/Event.h"
#include "ecpch.h"

namespace Echo 
{
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        WindowProps(const std::string& title = "Echo Engine", 
                    unsigned int Width = 1280, 
                    unsigned int Height = 720)
            : Title(title), Width(Width), Height(Height) {}
    };

    class Window
    {
        public:
            
            virtual ~Window() {}
            virtual void OnUpdate() = 0;

            virtual inline unsigned int GetWidth() const = 0;
            virtual inline unsigned int GetHeight() const = 0;

            virtual inline void SetEventCallback(const std::function<void(Event&)>& callback) = 0; 
            virtual void SetVSync(bool enabled) = 0;
            virtual bool IsVSync() const = 0;

            virtual void* GetWindowData() = 0;

            virtual void LockCursor() const = 0;
            virtual void UnlockCursor() const = 0;

            static Window* Create(const WindowProps& props = WindowProps());
    };
};
