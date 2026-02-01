#include "msshi_pch.h"
#include "Application.h"

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

		MSSHI_CORE_TRACE("rendering a hexagon...");

		//calling Create : ref OpenGLVertexArray.cpp
		m_VertexArray.reset(VertexArray::Create());

		// hexagon vertices (center + 6 outer vertices)
		float vertices[7 * 7] = {
			 //center
			  0.0f,  0.0f,  0.0f,	0.1f, 0.1f, 0.1f, 1.0f,	//0

			  0.5f,  0.0f,  0.0f,	0.1f, 0.1f, 0.1f, 1.0f,	//1	right
			  0.25f, 0.433f, 0.0f,	0.1f, 0.1f, 0.1f, 1.0f,	//2	tr
			 -0.25f, 0.433f, 0.0f,	0.1f, 0.1f, 0.1f, 1.0f,	//3	tl
			 -0.5f,  0.0f,  0.0f,	0.1f, 0.1f, 0.1f, 1.0f,	//4	left
			 -0.25f,-0.433f, 0.0f,	0.1f, 0.1f, 0.1f, 1.0f,	//5	bl
			  0.25f,-0.433f, 0.0f,  0.1f, 0.1f, 0.1f, 1.0f	//6	br
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));						//implementation defined [Buffer -> OpenGLBuffer]
		//sample layout to test stuff
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"  },
			{ ShaderDataType::Float4, "a_Color"     }  //if we had colors, hence added 4 more components for each vertext in vertices array
		};
		vertexBuffer->SetLayout(layout);		//overriden fn in openGLBuffer.h

		m_VertexArray->AddVertexBuffer(vertexBuffer);		//linking VB : ref OpenGLVertexArray.cpp

		uint32_t indices[18] = {
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 5,
			0, 5, 6,
			0, 6, 1
		};

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t) ));		//implementation defined [Buffer -> OpenGLBuffer]

		m_VertexArray->SetIndexBuffer(indexBuffer);			//linking IB : ref OpenGLVertexArray.cpp

		//writing our own simple shaders(GLSL)...
		//the R prefix in string allows multi line without new line in Cpp

		//responsible for positioning vertices
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_VPMatrix;

			out vec3 v_Position;
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_VPMatrix * vec4(a_Position, 1.0);
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
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);	//causes interpolation of the colors across our shape
				//color = v_Color;
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
			RenderCommand::SetClearColor({ 0.157f, 0.157f, 0.157f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			//m_VertexArray->Bind();
			//glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
			// ^^^ abstracted to Renderer::Submit() : ref OpenGLRendererAPI.cpp

			m_Shader->Bind(); //binding our shader before submitting VAO
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

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
