#pragma  once 
#include "Application.h"
#include "Log.h"
#ifdef EC_PLATFORM_WINDOWS 
#else 

extern Echo::Application* Echo::CreateApplication();

int main(int argc, char** argv)
{
    Echo::Log::Init();
    EC_CORE_INFO("Initialized Log!");

    auto app = Echo::CreateApplication();
    app->Run();
    delete app;
}
#endif
