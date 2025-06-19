#pragma once
#include "Core.h"

#include "Application.h"
#include "Log.h"

#include "EntryPoint.h"

#include "Layer.h"
#include "Events/Event.h"

#include "ImGui/ImGuiLayer.h"
#include <imgui/imgui.h>

#include "Codes/KeyCodes.h"
#include "Codes/MouseCodes.h"

#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"

#include "Buffer.h"
#include "Camera.h"
#include "RenderAPI.h"
#include "RenderCommand.h" 
#include "Shader.h"
#include "Renderer.h"
#include "VertexArray.h"

#include "InputTemplate.h"
#include "DeltaTime.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/Opengl/OpenGLBuffer.h"
#include "Platform/Opengl/OpenGLVertexArray.h"
#include "Platform/Opengl/OpenGLShader.h"
#include "Platform/Opengl/OpenGLRendererAPI.h"
#include "Platform/Opengl/OpenGLContext.h"

#include "ecpch.h"
