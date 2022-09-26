#include <Llama.h>

class ExampleLayer : public Llama::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		LLAMA_INFO("ExampleLayer::Update");
	}

	void OnEvent(Llama::Event& event) override
	{
		LLAMA_TRACE("{0}", event);
	}
};

	class Sandbox : public Llama::Application
	{
	public:
		Sandbox()
		{
			PushLayer(new ExampleLayer());
			PushOverlay(new Llama::ImGuiLayer());
		}

		~Sandbox()
		{
		}

	};

	Llama::Application* Llama::CreateApplication()
	{
		return new Sandbox();
	}