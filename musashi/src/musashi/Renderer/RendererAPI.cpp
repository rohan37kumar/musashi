#include "msshi_pch.h"
#include "RendererAPI.h"

namespace musashi
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;	//will set it at runtime, for now hardcoding to OpenGL
}