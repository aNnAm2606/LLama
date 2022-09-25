#include "llamapch.h"
#include "Application.h"

#include "Llama/Events/ApplicationEvent.h"
#include "Llama/Log.h"


namespace Llama {
	Application::Application()
	{
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			LLAMA_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			LLAMA_TRACE(e);
		}
		
		while (true);
	}

}

