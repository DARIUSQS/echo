#include "RenderCommand.h"
#include "Platform/Opengl/OpenGLRendererAPI.h"

namespace Echo 
{
    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}

