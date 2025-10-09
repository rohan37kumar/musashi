#include "Application.h"
#include "musashi/Log.h"
#include "musashi/Events/ApplicationEvent.h"

namespace musashi
{
	Application::Application()
	{
	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		//testing the event system
		WindowResizeEvent e(1280, 720);
		MSSHI_TRACE(e.ToString());

		while (true); //opening a window which does nothing but runs endlessly.
	}
}