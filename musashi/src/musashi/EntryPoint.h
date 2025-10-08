//as the name suggests
//initially getting an Application pointer from an extern function then Run() to run it endlessly here. 
//kinda like having the project exist as in Unity Hub, as far as I understand

#pragma once

#ifdef MSSHI_PLATFORM_WINDOWS
extern musashi::Application* musashi::CreateApplication();

int main(int argc, char** argv)
{
	//printf("musashi Engine is running...\n");
	musashi::Log::Init();
	MSSHI_CORE_WARN("engine intiated!");
	MSSHI_INFO("Hello!");

	auto app = musashi::CreateApplication();
	app->Run();
	delete app;
}
#endif
