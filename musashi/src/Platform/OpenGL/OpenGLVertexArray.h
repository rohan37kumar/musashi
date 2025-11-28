#pragma once

#include "musashi/Renderer/VertexArray.h"

namespace musashi
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

	private:
		uint32_t m_RendererID;											//OpenGL VAO handle
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;		//todo why vector?
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

	};
}

/*
	why multiple VBO and single VAO?

	- VAO can have multiple VBOs bound to it, each storing different vertex attributes (positions, colors, normals, texture coords)

	- A VAO can only have one active index buffer at a time
	- glDrawElements -> Index buffers define triangle connectivity, and you only need one connectivity pattern per draw call
*/
