#pragma once

#include <string>

namespace musashi
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t m_RendererID; //number assigned by opengl to identify this object, glCreateProgram returns a GLuint similar to uint32_t

	};

}