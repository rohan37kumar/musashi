#include "msshi_pch.h"
#include "WindowsWindow.h"

namespace musashi
{
	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props) //Create fn from Window.h 
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		MSSHI_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			//TODO: glfwTerminate on system shutdown
			int success = glfwInit(); //initializing and checking below
			MSSHI_CORE_ASSERT(success, "Could not initialize GLFW!"); //testing, if glfwInit fails it returns 0
			//success var as we should be able to remove the above log in release builds

			s_GLFWInitialized = true;
		}

		//creation of GLFW Window
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr); //c_str() converts std::string to const char*
		glfwMakeContextCurrent(m_Window); //setting OpenGL context to this window
		glfwSetWindowUserPointer(m_Window, &m_Data); //now GLFW knows about our window and its data, m_Window is GLFW Window*, and m_Data is my struct
		//will be used later for event callbacks
		SetVSync(true);	
	}

	void WindowsWindow::OnUpdate() //per frame update of our window
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window); //yet to know it's functionality
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		//controlling how buffer swaps are synchronized with the monitor’s vertical refresh rate
		if (enabled)
			glfwSwapInterval(1); //enable vsync, explanation pending
		else
			glfwSwapInterval(0); //disable vsync

		m_Data.VSync = enabled;
	}
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
//really simple stuff, boilerplate [dead skull emoji]
