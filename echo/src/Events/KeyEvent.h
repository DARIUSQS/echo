#pragma once

#include "Events/Event.h"

namespace Echo  
{
    class KeyEvent : public Event
    {
        public:
            inline int GetKeyCode() const { return m_KeyCode;}
            
            EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyBoard);
        protected:
            KeyEvent(int KeyCode)
                : m_KeyCode(KeyCode) {}
        int m_KeyCode;
    };

    class KeyEventPressed : public KeyEvent
    {
        public:
            KeyEventPressed(int KeyCode, int repeat = 0)
                : KeyEvent(KeyCode), m_Repeat(repeat) {}
            
            inline int GetRepeatCount() const { return m_Repeat; }

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "KeyPressedEvent: " << m_KeyCode << "( " << m_Repeat << " repeats)";
                return ss.str();
            }

            EVENT_CLASS_TYPE(KeyPressed);

        private:
            int m_Repeat;
    };

    class KeyEventReleased : public KeyEvent
    {
        public: 
            KeyEventReleased(int KeyCode)
                : KeyEvent(KeyCode) {}
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased);
    };
}
