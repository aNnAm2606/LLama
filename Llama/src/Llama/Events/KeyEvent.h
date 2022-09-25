#pragma once

#include "Event.h"

namespace Llama
{

	class LLAMA_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; } //Getter for keycode

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)//macro implementing class category
	protected:
		KeyEvent(int keycode) //protected so no one else can construct it
			: m_KeyCode(keycode) {}

		int m_KeyCode;
	};

	class LLAMA_API KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(int keycode, int repeatCount)//repeat count acts like a bool, 0 means non repeat event, else its a repeat event
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)"; //Will print which key has been pressed and amount of times
			return ss.str();
		}


		EVENT_CLASS_TYPE(KeyPressed) //macro which implement all of our functions
	private:
		int m_RepeatCount;
	};

	class LLAMA_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}
