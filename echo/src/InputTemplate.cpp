#include "InputTemplate.h"
#include "Platform/Linux/LinuxInput.h"
namespace Echo 
{
    Input* Input::s_Instance = new InputGlfw;
}
