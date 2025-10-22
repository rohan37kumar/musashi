#include "msshi_pch.h"
#include <Musashi.h>

//testing the engine functions here

class ExampleLayer : public musashi::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		MSSHI_INFO("ExampleLayer::Update");
	}
	void OnEvent(musashi::Event& event) override
	{
		MSSHI_INFO("{0}", event.ToString());
	}
};

class Sandbox : public musashi::Application 
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new musashi::ImGuiLayer()); //adds the imgui layer on the top
	}
	~Sandbox()
	{

	}
};

musashi::Application* musashi::CreateApplication()
{
	return new Sandbox();
}