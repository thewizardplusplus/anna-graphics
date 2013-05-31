#include "Window.h"
#include <algorithm>

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;

Window::~Window(void) {}

Vector2D<size_t> Window::getSize(void) const {
	return size;
}

bool Window::isPressedKey(KeyCode::Types key_code) const {
	return std::find(keys.begin(), keys.end(), key_code) != keys.end();
}

bool Window::isPressedButton(ButtonCode::Types button_code) const {
	return std::find(buttons.begin(), buttons.end(), button_code) != buttons.
		end();
}

Vector2D<size_t> Window::getPointerPosition(void) const {
	return pointer_position;
}

void Window::setPointerPosition(const maths::Vector2D<size_t>& position) {
	pointer_position = position;
	processSettingPointerPosition(pointer_position);
}

void Window::setPointerPosition(size_t x, size_t y) {
	setPointerPosition(Vector2D<size_t>(x, y));
}
