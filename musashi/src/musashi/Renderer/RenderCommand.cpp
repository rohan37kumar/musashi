#include "msshi_pch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace musashi
{
	//hardcoding OpenGL for now
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}