#pragma  once 

#include "Application.h"
#ifdef EC_PLATFORM_WINDOWS 

#else 

extern Echo::Application* Echo::CreateApplication();

int main(int argc, char** argv)
{
    auto app = Echo::CreateApplication();
    app->Run();
    delete app;
}
#endif
