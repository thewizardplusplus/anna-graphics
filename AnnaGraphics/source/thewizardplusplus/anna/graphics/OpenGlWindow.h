#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include "../../utils/os.h"
#include "Window.h"
#ifdef OS_WINDOWS
#include <windows.h>
#endif
#include <GL/gl.h>
#ifdef OS_LINUX
#include <GL/glx.h>
#endif

namespace thewizardplusplus {
namespace anna {
namespace graphics {

class OpenGlWindow : public Window {
public:
	#ifdef OS_WINDOWS
	static const std::wstring WINDOW_CLASS_NAME;

	static LRESULT CALLBACK globalWindowProcedure(HWND window, UINT message,
		WPARAM word_parameter, LPARAM long_parameter);
	#endif

	OpenGlWindow(void);
	virtual ~OpenGlWindow(void);
	virtual void update(void);

protected:
	virtual void processSettingPointerPosition(const maths::Vector2D<size_t>&
		position);

private:
	#ifdef OS_LINUX
	Display*   display;
	XID        window;
	GLXContext context;
	#elif defined(OS_WINDOWS)
	HINSTANCE instance;
	HWND      window;
	HDC       window_context;
	HGLRC     opengl_context;
	#endif

	#ifdef OS_WINDOWS
	LRESULT CALLBACK windowProcedure(HWND window, UINT message, WPARAM
		word_parameter, LPARAM long_parameter);
	#endif
	void initialize(void);
	void resize(size_t width, size_t height);
	KeyCode::Types convertKeyCode(unsigned long key_code);
	#ifdef OS_LINUX
	ButtonCode::Types convertButtonCode(unsigned int button_code);
	#endif
};

}
}
}
#endif
