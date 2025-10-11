#include "msshi_pch.h"
#include "Application.h"

#include "musashi/Log.h"
#include "musashi/Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace musashi
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		while (m_Running) //our main loop
		{
			//test GLFW fns
			glClearColor(0.157f, 0.157f, 0.157f, 0.5f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();
			//till here we'll have a window that opens and gets deleted
			//but non-functional, yet to add Events & callbacks
		}
	}
}