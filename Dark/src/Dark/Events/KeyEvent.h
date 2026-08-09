#pragma once

#include "Event.h"

namespace Dark {

	class DARK_API KeyEvent : public Event {

	protected:
		int m_KeyCode{};

		KeyEvent(int keycode)
			: m_KeyCode(keycode) {

		}

	public:
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

		inline int GetKeyCode() const { return m_KeyCode; }

	};

	class DARK_API KeyPressedEvent : public KeyEvent {

		int m_RepeatCount{};

	public:
		KeyPressedEvent(int KeyCode, int repeatCount)
			: KeyEvent(KeyCode), m_RepeatCount(repeatCount) { }

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			 
			ss << "KeyPressedEvent: " << m_KeyCode << "(Repeats: " << m_RepeatCount << ")";

			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);

	};

	class DARK_API KeyReleasedEvent : public KeyEvent {

	public:
		KeyReleasedEvent(int KeyCode)
			: KeyEvent(KeyCode) { }

		std::string ToString() const override{
			std::stringstream ss;

			ss << "KeyReleasedEvent: " << m_KeyCode;

			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);

	};

	class DARK_API KeyTypedEvent : public KeyEvent {

	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) { }

		std::string ToString() const override {
			std::stringstream ss;

			ss << "KeyPressedEvent: " << m_KeyCode;

			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);

	};

}