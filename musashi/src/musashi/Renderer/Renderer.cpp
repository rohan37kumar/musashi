#include "msshi_pch.h"
#include "Renderer.h"

namespace musashi
{
	void Renderer::BeginScene()		//todo imlement params	-> environ, camera, lighting stuff
	{
	}
	void Renderer::EndScene()
	{	
	}


	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)	//submits into render command queue to get evaluated
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}