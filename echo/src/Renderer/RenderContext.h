#pragma once

namespace Echo
{
    class RenderContext 
    {
        public: 
            ~RenderContext() = default;

            virtual void Init() = 0;
            virtual void SwapBuffers() = 0;
    };
}
