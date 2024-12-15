#include "Application.h"
#include <iostream>

namespace Echo {
    Application::Application(){}
    Application::~Application(){}
    
    void Application::Run()
    {
        while(true)
        {
            std::cout << 3;
        }
    }
}
