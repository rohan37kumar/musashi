#include "msshi_pch.h"
#include "Application.h"

#include <glad/glad.h>

namespace musashi
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1) //std::bind(...) binds function + arguments into callable

	Application* Application::s_Instance = nullptr; //for passing application instance reference

	Application::Application()
	{
		MSSHI_CORE_ASSERT(!s_Instance, "Application already exists!"); //check if instance already exists
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent)); //todo understand the event callback stack, how events are passed from window to application

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);


		MSSHI_CORE_TRACE("rendering hexagon...");

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);   // <-- this VAO becomes the active listeners for further bind calls

		//glGenBuffers(1, &m_VertexBuffer);
		//glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);  // VBO becomes bound to the currently active VAO, in ARRAY BUFFER target
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// ^^^	abstracted [Buffer -> OpenGLBuffer] implementation

		// hexagon vertices (center + 6 outer vertices)
		float vertices[7 * 3] = {
			//center
			  0.0f,  0.0f,  0.0f,	//0

			  0.5f,  0.0f,  0.0f,	//1	right
			  0.25f, 0.433f, 0.0f,	//2	tr
			 -0.25f, 0.433f, 0.0f,	//3	tl
			 -0.5f,  0.0f,  0.0f,	//4	left
			 -0.25f,-0.433f, 0.0f,	//5	bl
			  0.25f,-0.433f, 0.0f	//6	br
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));


		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		/*
		VAO (m_VertexBuffer) attribute 0 -> VBO (GL_ARRAY_BUFFER)
		*/

		//glGenBuffers(1, &m_IndexBuffer);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);  // EBO becomes bound to the currently active VAO, in ELEMENT ARRAY BUFFER target
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		// ^^^	abstracted [Buffer -> OpenGLBuffer] implementation

		uint32_t indices[18] = {
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 5,
			0, 5, 6,
			0, 6, 1
		};
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t) ));

		//writing our own simple shaders(GLSL)...
		//the R prefix in string allows multi line without new line in Cpp

		//responsible for positioning vertices
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		/*
		* simple GLSL
		* - input vertexAttribute from VBO at location 0
		* - output variable to fragment shader
		* - glPosition --> built-in output variable -- holds the final position of the vertex in clip space
		*/

		//responsible for coloring the fragments/pixels
		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";
		/*
		* - output color var again at location 0
		* - getting interpolated input from vertex shader
		* - final color assignment to output variable
		*/

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

	}
	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		//core dispatcher functionality
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose)); //so if the event e is WindowCloseEvent -> call OnWindowClose fn

		//MSSHI_CORE_TRACE("{0}", e.ToString()); //logging every event

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) //reverse iteration
		{
			(*--it)->OnEvent(e); //decrementing iterator first, then dereferencing to get Layer*, then calling OnEvent fn of that layer
			if (e.Handled)
				break; 
		}
	}

	void Application::Run()
	{
		while (m_Running) //our main loop
		{
			//clear the screen -> set GLFW window color
			glClearColor(0.157f, 0.157f, 0.157f, 0.5f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind(); //binding our simple shader (to/before)? our draw elements call
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
			//drawing the hexagon after reading data from VBO (vertices) and EBO (indices) via the VAO

			//update all layers
			for(Layer* layer : m_LayerStack)
				layer->OnUpdate();

			//imgui rendering implementation
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate(); //swap buffers and poll events
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false; //stopping the main Run() loop
		return true;
	}
}
