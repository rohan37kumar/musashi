//moved the Rendering Context from WindowsWindow to OpenGLContext.cpp

#include "msshi_pch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace musashi
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		MSSHI_CORE_ASSERT(windowHandle, "Window handle is null...");
	}


	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		MSSHI_CORE_ASSERT(status, "Failed to initialize Glad...");

		MSSHI_CORE_INFO("Renderer in use: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		MSSHI_CORE_INFO("version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
		//for double buffering in OpenGL rendering, swaps front and back buffers, provides smooth rendering
	}

}