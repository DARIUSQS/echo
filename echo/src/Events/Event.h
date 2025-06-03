#pragma once
#include "Core.h"
#include "ecpch.h"
#include <functional>

namespace Echo
{
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender, 
        KeyPressed, KeyReleased, KeyTyped, 
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScroll
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication    = BIT(0),
        EventCategoryInput          = BIT(1),
        EventCategoryKeyBoard       = BIT(2),
        EventCategoryMouse          = BIT(3),
        EventCategoryMouseButton    = BIT(4)
    };
    
    #define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::type; }\
                                                                    virtual EventType GetEventType() const override { return GetStaticType(); }\
                                                                    virtual const char* GetName() const override { return #type;}
    #define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; };

    class Event
    {
        public:
            virtual EventType GetEventType() const = 0;
            virtual const char* GetName() const = 0;
            virtual int GetCategoryFlags() const = 0;
            virtual std::string ToString() const {return GetName();}

            bool m_Handled = false;
    };

    class EventDispatcher
    {
        template<typename T>
        using Eventfn = std::function<bool(T&)>;

    public:
           EventDispatcher(Event& event)
               : m_Event(event) 
           {

           }

           template<typename T>
           bool Dispatch(Eventfn<T> func)
           {
                if(m_Event.GetEventType() == T::GetStaticType())
                {
                    m_Event.m_Handled = func(*(T*)&m_Event);
                    return true;
                }
                return false;
           }
    private:
           Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }

    /// Formatter for the Log library

    inline std::string format_as(const Event& e) 
    {
        return e.ToString();
    }

}
