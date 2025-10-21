#include "msshi_pch.h"
#include "WindowsWindow.h"

#include "musashi/Events/ApplicationEvent.h"
#include "musashi/Events/KeyEvent.h"
#include "musashi/Events/MouseEvent.h"

#include <glad/glad.h>

namespace musashi
{
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		MSSHI_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

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
			
			glfwSetErrorCallback(GLFWErrorCallback); //error callback fn

			s_GLFWInitialized = true;
		}

		//creation of GLFW Window
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr); //c_str() converts std::string to const char*
		glfwMakeContextCurrent(m_Window); //setting OpenGL context to this window
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		//fills in function pointers (in Glad Header) with actual addresses from the driver, pointers of the modern OpenGL functions which are only exposed at runtime
		MSSHI_CORE_ASSERT(status, "Failed to initialize Glad..."); //catching it's status
		glfwSetWindowUserPointer(m_Window, &m_Data); //now GLFW knows about our window and its data, m_Window is GLFW Window*, and m_Data is my struct
		//will be used later for event callbacks
		SetVSync(true);

		//setting up event callbacks via GLFW Window
		// get window -> create event -> any attribute changes -> dispatch event via callback function  ]- for every event

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) //set Window resize event
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); //returns a void* from GLFW -> cast it to WindowData* -> dereference to get WindowData
			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height); //creating a window resize event
			data.EventCallback(event); //calling the event callback fn
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) //set Window close event
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) //set Key events
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0); //0 for repeat count, as we designed in KeyPressedEvent class
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1); //1 for repeat count, GLFW can't give exact count
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) //set Mouse button events
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) //set Mouse scroll events
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) //set Mouse move events
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

	}

	void WindowsWindow::OnUpdate() //per frame update of our window
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window); //todo: yet to understand it's functionality
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		//controlling how buffer swaps are synchronized with the monitor's vertical refresh rate
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
//really simple stuff, boilerplate [dead skull]
