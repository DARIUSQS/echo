#pragma once 
#include "Core.h"

namespace Echo {
   ECHO_API class Application
   {
        public:
            Application();
            virtual ~Application();

            void Run();
   };
   // Defined in CLIENT
   Application* CreateApplication();
}
