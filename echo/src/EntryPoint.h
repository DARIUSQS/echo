#pragma  once 

#ifdef EC_PLATFORM_WINDOWS 
#else 
extern Echo::Application* Echo::CreateApplication();

int main(int argc, char** argv)
{
    Echo::Log::Init();
    Echo::Log::GetCoreLogger()->warn("Initialized Log!");
    Echo::Log::GetClientLogger()->warn("Initialized Log!");
    auto app = Echo::CreateApplication();
    app->Run();
    delete app;
}
#endif
