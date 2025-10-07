#include <Musashi.h>


//testing the engine functions here

class Sandbox : public musashi::Application 
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

musashi::Application* musashi::CreateApplication()
{
	return new Sandbox();
}