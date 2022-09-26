#pragma once

#include "llamapch.h"
#include "Llama/Core.h"


namespace Llama
{
	//Events in Llama are currently blocking, meaning when an event occurs it
	//imediately gets dispatched and must be dealt with right then and there.
	//For the fututre, a better strategy might be buffer events in an event
	//bus and process them during the "event" part of the update stage.


	//We have all kind of event types which are implemented in their relevant files. 
	//Code assigned to each event, like a num from 1-14. Bassically specifies what type they are.(int id)
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,   //covered by ApplicationEvent.h
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,                                               //covered by KeyEvent.h
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled     //covered by MouseEvent.h
	};

	//For event filtering, recieving all events from application, but we might only care about mouse not to have to check
	//what event type. This is a BIT field with multiple BIT events set, so we mask them out and c wut category/ies it belongs to
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	//Base class for events
	class LLAMA_API Event
	{
		
	public:
		bool Handled = false;//To see if event has been handled or not

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) //Asks if this event in the given category, to filter out certain events
		{
			return GetCategoryFlags() & category; //If returns 0, not in category, other, it will be true
		}

	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())//which event type the current event which we are trying to dispatch is
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}
