#include "msshi_pch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace musashi
{
	//here in Create fns we'll select which Rendering API we intend to use  -> and fetch that platform-specific implementation 

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
				MSSHI_CORE_ASSERT(false, "RendererAPI->None selected!");
				return nullptr;

		case RendererAPI::API::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);

			default:
				break;
		}

		MSSHI_CORE_ASSERT(false, "Couldn't find a valid RendererAPI");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			MSSHI_CORE_ASSERT(false, "RendererAPI->None selected!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);

		default:
			break;
		}

		MSSHI_CORE_ASSERT(false, "Couldn't find a valid RendererAPI");
		return nullptr;
	}
}