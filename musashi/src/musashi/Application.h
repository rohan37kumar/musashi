//this is the main application header file
//for now just the Run fn is declared

#pragma once
#include "Core.h"

namespace musashi{

	class MSSHI_API Application
	{
		public:
			Application();
			virtual ~Application();
	
		void Run();
	};

	//will be defined in the CLIENT code
	Application* CreateApplication();
}
