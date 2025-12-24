#include "msshi_pch.h"
#include "VertexArray.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace musashi
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			MSSHI_CORE_ASSERT(false, "RendererAPI->None selected!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();

		default:
			break;
		}

		MSSHI_CORE_ASSERT(false, "Couldn't find a valid RendererAPI");
		return nullptr;
	}
}