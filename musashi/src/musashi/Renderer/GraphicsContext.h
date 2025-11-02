//base class for all graphics contexts, whichever API we decide to use

#pragma once

namespace musashi
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}
