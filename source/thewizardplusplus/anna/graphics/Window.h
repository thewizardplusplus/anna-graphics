#ifndef WINDOW_H
#define WINDOW_H

#include "../maths/Vector2D.h"
#include "KeyCode.h"
#include "ButtonCode.h"
#include <list>

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class Window {
public:
	template<typename WindowType>
	static WindowType* create(void);

	virtual ~Window(void);
	maths::Vector2D<size_t> getSize(void) const;
	bool isPressedKey(KeyCode::Types key_code) const;
	bool isPressedButton(ButtonCode::Types button_code) const;
	maths::Vector2D<size_t> getPointerPosition(void) const;
	void setPointerPosition(const maths::Vector2D<size_t>& position);
	void setPointerPosition(size_t x, size_t y);
	virtual void update(void) = 0;

protected:
	typedef std::list<KeyCode::Types>    KeyCodeList;
	typedef std::list<ButtonCode::Types> ButtonCodeList;

	maths::Vector2D<size_t> size;
	KeyCodeList             keys;
	ButtonCodeList          buttons;
	maths::Vector2D<size_t> pointer_position;

	virtual void processSettingPointerPosition(const maths::Vector2D<size_t>&
		position) = 0;
};

template<typename WindowType>
WindowType* Window::create(void) {
	return new WindowType();
}

}
}
}
#endif
