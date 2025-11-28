#pragma once

#include <memory>
#include "musashi/Renderer/Buffer.h"

namespace musashi
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;		//ref of VBO in VAO
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;						//same for IB
		//now with this -> access VB & IB from VAO...beautiful!!!

		static VertexArray* Create();
		
	};
}