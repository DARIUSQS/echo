#pragma once

namespace Echo 
{
    class Input 
    {
        public:
            /// Implementation in the platform folder
            static bool IsKeyPressed(int keycode);
            static bool IsMouseButtonPressed(int button);
            static std::pair<float,float> GetMousePos();
            static float GetMouseX();
            static float GetMouseY();

            /// Another alternative is creating protected Implementation methods 
            /// and inheriting another class in the platform folder
    };
};
