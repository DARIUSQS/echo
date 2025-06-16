#pragma once

namespace Echo 
{
    class DeltaTime 
    {
        public:
            operator float() const { return m_time; }

            static float Seconds() {return m_time;}
            static float Miliseconds() {return m_time * 1000;}
            static void SetTime(float time) {m_time = time - m_lastFrameTime; m_lastFrameTime = time;}
        private:
            static float m_time;
            static float m_lastFrameTime;
    };
}
