#include "msshi_pch.h"
#include "Application.h"

#include "musashi/Log.h"
#include "musashi/Events/ApplicationEvent.h"

#include <GLFW/glfw3.h>

namespace musashi
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		MSSHI_CORE_INFO("{0}", e.ToString()); //logging every event
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