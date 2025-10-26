#include "msshi_pch.h"
#include <Musashi.h>

//testing the engine functions here

class EngineLayer : public musashi::Layer
{
public:
	EngineLayer()
		: Layer("Engine")
	{
	}

	void OnUpdate() override
	{
		//MSSHI_INFO("ExampleLayer::Update");

		if (musashi::Input::IsKeyPressed(MSSHI_KEY_TAB))
			MSSHI_INFO("Tab Key Pressed");
	}
	void OnEvent(musashi::Event& event) override
	{
		//MSSHI_INFO("{0}", event.ToString());
	}
};

class Sandbox : public musashi::Application 
{
public:
	Sandbox()
	{
		PushLayer(new EngineLayer());

		//PushOverlay(new musashi::ImGuiLayer()); //adds the imgui layer on the top ]- no more, our musashi engine will automatically add
	}
	~Sandbox()
	{

	}
};

musashi::Application* musashi::CreateApplication()
{
	//creating a Sandbox app of type musashi::Application, and returning to engine
	return new Sandbox();
}