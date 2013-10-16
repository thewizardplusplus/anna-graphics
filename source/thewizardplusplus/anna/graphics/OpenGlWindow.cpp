#include "OpenGlWindow.h"
#include "../../utils/Console.h"
#include <cstdlib>
#include <cstring>

using namespace thewizardplusplus::anna::graphics;
using namespace thewizardplusplus::anna::maths;
using namespace thewizardplusplus::utils;

#ifdef OS_WINDOWS
const std::wstring OpenGlWindow::WINDOW_CLASS_NAME = L"Anna Window Class";

LRESULT CALLBACK OpenGlWindow::globalWindowProcedure(HWND window, UINT message,
	WPARAM word_parameter, LPARAM long_parameter)
{
	OpenGlWindow* target = NULL;
	if (message == WM_NCCREATE) {
		target = static_cast<OpenGlWindow*>(reinterpret_cast<CREATESTRUCT*>(
			long_parameter)->lpCreateParams);
		SetWindowLong(window, GWL_USERDATA, reinterpret_cast<LONG>(target));
	} else {
		target = reinterpret_cast<OpenGlWindow*>(GetWindowLong(window,
			GWL_USERDATA));
	}

	LRESULT result = 0;
	if (target == NULL) {
		result = DefWindowProc(window, message, word_parameter, long_parameter);
	} else {
		result = target->windowProcedure(window, message, word_parameter,
			long_parameter);
	}

	return result;
}
#endif

OpenGlWindow::OpenGlWindow(void) :
	#ifdef OS_LINUX
	display(NULL),
	window(0),
	context(NULL)
	#elif defined(OS_WINDOWS)
	instance(NULL),
	window(NULL),
	window_context(NULL),
	opengl_context(NULL)
	#endif
{
	#ifdef OS_LINUX
	display = XOpenDisplay(NULL);
	if (display == NULL) {
		Console::error() << "Error: can't connect with X Server.";
		std::exit(EXIT_FAILURE);
	}
	int screen = DefaultScreen(display);
	int info_attributes[] = { GLX_RGBA, GLX_DOUBLEBUFFER, GLX_DEPTH_SIZE, 24,
		None };
	XVisualInfo* info = glXChooseVisual(display, screen, info_attributes);
	if (info == NULL) {
		Console::error() << "Error: failed to choose a pixel format.";
		std::exit(EXIT_FAILURE);
	}
	size.x = XDisplayWidth(display, info->screen);
	size.y = XDisplayHeight(display, info->screen);
	XID root = RootWindow(display, info->screen);
	Colormap color_map = XCreateColormap(display, root, info->visual,
		AllocNone);
	XSetWindowAttributes window_attributes;
	window_attributes.colormap =          color_map;
	window_attributes.border_pixel =      0;
	window_attributes.override_redirect = true;
	window_attributes.event_mask =        ExposureMask | KeyPressMask |
		KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask
		| StructureNotifyMask;
	window = XCreateWindow(display, root, 0, 0, size.x, size.y, 0, info->depth,
		InputOutput, info->visual, CWBorderPixel | CWColormap | CWEventMask |
		CWOverrideRedirect, &window_attributes);
	XMapRaised(display, window);

	static char no_data[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	Pixmap bitmap_no_data = XCreateBitmapFromData(display, window, no_data, 8,
		8);
	XColor black;
	black.red =   0;
	black.green = 0;
	black.blue =  0;
	Cursor invisible_cursor = XCreatePixmapCursor(display, bitmap_no_data,
		bitmap_no_data, &black, &black, 0, 0);
	XDefineCursor(display, window, invisible_cursor);
	XFreeCursor(display, invisible_cursor);

	XGrabKeyboard(display, window, True, GrabModeAsync, GrabModeAsync,
		CurrentTime);
	XGrabPointer(display, window, True, ButtonPressMask | ButtonReleaseMask |
		PointerMotionMask, GrabModeAsync, GrabModeAsync, window, None,
		CurrentTime);
	context = glXCreateContext(display, info, 0, GL_TRUE);
	glXMakeCurrent(display, window, context);
	#elif defined(OS_WINDOWS)
	int result = 0;

	instance = GetModuleHandle(NULL);

	size.x = GetSystemMetrics(SM_CXSCREEN);
	size.y = GetSystemMetrics(SM_CYSCREEN);

	WNDCLASSEX window_class;
	window_class.cbSize =        sizeof(WNDCLASSEX);
	window_class.style =         CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	window_class.lpfnWndProc =   static_cast<WNDPROC>(OpenGlWindow::
		globalWindowProcedure);
	window_class.cbClsExtra =    0;
	window_class.cbWndExtra =    0;
	window_class.hInstance =     instance;
	window_class.hIcon =         LoadIcon(NULL, IDI_APPLICATION);
	window_class.hIconSm =       LoadIcon(NULL, IDI_APPLICATION);
	window_class.hCursor =       LoadCursor(NULL, IDC_ARROW);
	window_class.hbrBackground = NULL;
	window_class.lpszMenuName =  NULL;
	window_class.lpszClassName = WINDOW_CLASS_NAME.c_str();

	result = RegisterClassEx(&window_class);
	if (!result) {
		Console::error() << "Error: unable to register the window class.";
		std::exit(EXIT_FAILURE);
	}

	DEVMODE screen_settings;
	std::memset(&screen_settings, 0, sizeof(screen_settings));
	screen_settings.dmSize =       sizeof(screen_settings);
	screen_settings.dmPelsWidth =  size.x;
	screen_settings.dmPelsHeight = size.y;
	screen_settings.dmBitsPerPel = 32;
	screen_settings.dmFields =     DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	result = ChangeDisplaySettings(&screen_settings, CDS_FULLSCREEN);
	if (result != DISP_CHANGE_SUCCESSFUL) {
		Console::error() << "Error: cannot run in the fullscreen mode at the "
			"screen resolution on your video card.";
		std::exit(EXIT_FAILURE);
	}

	ShowCursor(FALSE);

	RECT window_rectangle;
	window_rectangle.left =   0;
	window_rectangle.right =  size.x;
	window_rectangle.top =    0;
	window_rectangle.bottom = size.y;
	AdjustWindowRectEx(&window_rectangle, WS_POPUP, FALSE, WS_EX_APPWINDOW);

	window = CreateWindowEx(WS_EX_APPWINDOW, WINDOW_CLASS_NAME.c_str(), L"",
		WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, size.x, size.y,
		NULL, NULL, instance, this);
	if (window == NULL) {
		Console::error() << "Error: unable to create window.";
		std::exit(EXIT_FAILURE);
	}

	window_context = GetDC(window);
	if (window_context == NULL) {
		Console::error() << "Error: unable to create device context.";
		std::exit(EXIT_FAILURE);
	}

	PIXELFORMATDESCRIPTOR pixel_format_descriptor = { sizeof(
		PIXELFORMATDESCRIPTOR), 1, PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER, PFD_TYPE_RGBA, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 24, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };
	unsigned int pixel_format = ChoosePixelFormat(window_context,
		&pixel_format_descriptor);
	if (pixel_format == 0) {
		Console::error() << "Error: can't find an appropriate pixel format.";
		std::exit(EXIT_FAILURE);
	}

	result = SetPixelFormat(window_context, pixel_format,
		&pixel_format_descriptor);
	if (result == 0) {
		Console::error() << "Error: unable to set pixel format.";
		std::exit(EXIT_FAILURE);
	}

	opengl_context = wglCreateContext(window_context);
	if (opengl_context == NULL) {
		Console::error() << "Error: unable to create OpenGL rendering context.";
		std::exit(EXIT_FAILURE);
	}

	result = wglMakeCurrent(window_context, opengl_context);
	if (result == 0) {
		Console::error() << "Error: unable to activate OpenGL rendering "
			"context.";
		std::exit(EXIT_FAILURE);
	}

	ShowWindow(window, SW_SHOW);
	SetForegroundWindow(window);
	SetFocus(window);

	#ifdef RAW_INPUT
	const size_t NUMBER_OF_RAW_INPUT_DEVICES = 2;
	RAWINPUTDEVICE raw_input_device_ids[NUMBER_OF_RAW_INPUT_DEVICES];

	raw_input_device_ids[0].usUsagePage = 0x01 /* HID_USAGE_PAGE_GENERIC */;
	raw_input_device_ids[0].usUsage =     0x06 /* HID_USAGE_GENERIC_KEYBOARD */;
	raw_input_device_ids[0].dwFlags =     RIDEV_NOLEGACY;
	raw_input_device_ids[0].hwndTarget =  window;

	raw_input_device_ids[1].usUsagePage = 0x01 /* HID_USAGE_PAGE_GENERIC */;
	raw_input_device_ids[1].usUsage =     0x02 /* HID_USAGE_GENERIC_MOUSE */;
	raw_input_device_ids[1].dwFlags =     RIDEV_NOLEGACY;
	raw_input_device_ids[1].hwndTarget =  window;

	result = RegisterRawInputDevices(raw_input_device_ids, \
		NUMBER_OF_RAW_INPUT_DEVICES, sizeof(RAWINPUTDEVICE));
	if (!result) {
		Console::error() << "Error: unable to register raw input device.";
		std::exit(EXIT_FAILURE);
	}
	#endif
	#endif

	initialize();
}

OpenGlWindow::~OpenGlWindow(void) {
	#ifdef OS_LINUX
	if (context) {
		if (!glXMakeCurrent(display, None, NULL)) {
			Console::error() << "AnnaGraphics warning: could not release "
				"drawing context.";
		}
		glXDestroyContext(display, context);
		context = NULL;
	}
	XCloseDisplay(display);
	#elif defined(OS_WINDOWS)
	int result = 0;

	ChangeDisplaySettings(NULL, 0);
	ShowCursor(TRUE);

	if (opengl_context != NULL) {
		result = wglMakeCurrent(NULL, NULL);
		if (result == 0) {
			Console::error() << "AnnaGraphics warning: unable to release "
				"rendering context.";
		}

		result = wglDeleteContext(opengl_context);
		if (result == 0) {
			Console::error() << "AnnaGraphics warning: unable to delete "
				"rendering context.";
		}

		opengl_context = NULL;
	}

	if (window_context != NULL) {
		result = ReleaseDC(window, window_context);
		if (result == 0) {
			Console::error() << "AnnaGraphics warning: unable to release device"
				" context.";
		}
		window_context = NULL;
	}

	if (window != NULL) {
		result = DestroyWindow(window);
		if (result == 0) {
			Console::error() << "AnnaGraphics warning: unable to destroy "
				"window.";
		}
		window = NULL;
	}

	result = UnregisterClass(WINDOW_CLASS_NAME.c_str(), instance);
	if (result == 0) {
		Console::error() << "AnnaGraphics warning: unable to unregister window "
			"class.";
	}
	instance = NULL;
	#endif
}

void OpenGlWindow::update(void) {
	#ifdef OS_LINUX
	XEvent event;

	while (XPending(display) > 0) {
		XNextEvent(display, &event);
		switch (event.type) {
			case ConfigureNotify:
				if (event.xconfigure.width != static_cast<int>(size.x) || event.
					xconfigure.height != static_cast<int>(size.y))
				{
					resize(event.xconfigure.width, event.xconfigure.height);
				}

				break;
			case KeyPress: {
				KeyCode::Types key = convertKeyCode(XLookupKeysym(&event.xkey,
					0));
				keys.push_back(key);

				break;
			}
			case KeyRelease: {
				KeyCode::Types key = convertKeyCode(XLookupKeysym(&event.xkey,
					0));
				keys.remove(key);

				break;
			}
			case ButtonPress: {
				ButtonCode::Types button = convertButtonCode(event.xbutton.
					button);
				buttons.push_back(button);

				break;
			}
			case ButtonRelease: {
				ButtonCode::Types button = convertButtonCode(event.xbutton.
					button);
				buttons.remove(button);

				break;
			}
			case MotionNotify:
				pointer_position.x = event.xmotion.x;
				pointer_position.y = event.xmotion.y;

				break;
			default:
				break;
		}
	}

	glXSwapBuffers(display, window);
	#elif defined(OS_WINDOWS)
	MSG message;

	while (true) {
		int result = PeekMessage(&message, NULL, 0, 0, PM_REMOVE);
		if (result == 0) {
			break;
		}

		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	SwapBuffers(window_context);
	#endif
}

void OpenGlWindow::processSettingPointerPosition(const Vector2D<size_t>&
	position)
{
	#ifdef OS_LINUX
	XWarpPointer(display, window, window, 0, 0, 0, 0, position.x, position.y);
	#elif defined(OS_WINDOWS)
	SetCursorPos(position.x, position.y);
	#endif
}

#ifdef OS_WINDOWS
LRESULT CALLBACK OpenGlWindow::windowProcedure(HWND window, UINT message, WPARAM
	word_parameter, LPARAM long_parameter)
{
	switch (message) {
		case WM_SIZE: {
			size_t width =  LOWORD(long_parameter);
			size_t height = HIWORD(long_parameter);
			if (width != size.x || height != size.y) {
				resize(width, height);
			}

			return 0;
		}
		#ifndef RAW_INPUT
		case WM_KEYDOWN: {
			KeyCode::Types key = convertKeyCode(word_parameter);
			keys.push_back(key);

			return 0;
		}
		case WM_KEYUP: {
			KeyCode::Types key = convertKeyCode(word_parameter);
			keys.remove(key);

			return 0;
		}
		case WM_LBUTTONDOWN:
			buttons.push_back(ButtonCode::BUTTON_LEFT);
			return 0;
		case WM_LBUTTONUP:
			buttons.remove(ButtonCode::BUTTON_LEFT);
			return 0;
		case WM_MBUTTONDOWN:
			buttons.push_back(ButtonCode::BUTTON_MIDDLE);
			return 0;
		case WM_MBUTTONUP:
			buttons.remove(ButtonCode::BUTTON_MIDDLE);
			return 0;
		case WM_RBUTTONDOWN:
			buttons.push_back(ButtonCode::BUTTON_RIGHT);
			return 0;
		case WM_RBUTTONUP:
			buttons.remove(ButtonCode::BUTTON_RIGHT);
			return 0;
		case WM_MOUSEMOVE: {
			POINTS pointer_position = MAKEPOINTS(long_parameter);
			this->pointer_position.x = pointer_position.x;
			this->pointer_position.y = pointer_position.y;

			return 0;
		}
		#else
		case WM_INPUT: {
			unsigned int required_size = 0;
			GetRawInputData(reinterpret_cast<HRAWINPUT>(long_parameter),
				RID_INPUT, NULL, &required_size, sizeof(RAWINPUTHEADER));

			unsigned char* data = new unsigned char[required_size];
			unsigned int gotten_size = GetRawInputData(reinterpret_cast<
				HRAWINPUT>(long_parameter), RID_INPUT, data, &required_size,
				sizeof(RAWINPUTHEADER));
			if (gotten_size != required_size) {
				Console::error() << "AnnaGraphics warning: function "
					"GetRawInputData() does not return correct size.";
			}

			RAWINPUT* raw_data = reinterpret_cast<RAWINPUT*>(data);
			if (raw_data->header.dwType == RIM_TYPEKEYBOARD) {
				KeyCode::Types key = convertKeyCode(raw_data->data.keyboard.
					VKey);
				if (raw_data->data.keyboard.Flags & RI_KEY_BREAK) {
					keys.remove(key);
				} else {
					keys.push_back(key);
				}
			} else if (raw_data->header.dwType == RIM_TYPEMOUSE) {
				if (raw_data->data.mouse.usButtonFlags & \
					RI_MOUSE_LEFT_BUTTON_DOWN)
				{
					buttons.push_back(ButtonCode::BUTTON_LEFT);
				} else if (raw_data->data.mouse.usButtonFlags & \
					RI_MOUSE_LEFT_BUTTON_UP)
				{
					buttons.remove(ButtonCode::BUTTON_LEFT);
				} else if (raw_data->data.mouse.usButtonFlags & \
					RI_MOUSE_MIDDLE_BUTTON_DOWN)
				{
					buttons.push_back(ButtonCode::BUTTON_MIDDLE);
				} else if (raw_data->data.mouse.usButtonFlags & \
					RI_MOUSE_MIDDLE_BUTTON_UP)
				{
					buttons.remove(ButtonCode::BUTTON_MIDDLE);
				} else if (raw_data->data.mouse.usButtonFlags & \
					RI_MOUSE_RIGHT_BUTTON_DOWN)
				{
					buttons.push_back(ButtonCode::BUTTON_RIGHT);
				} else if (raw_data->data.mouse.usButtonFlags & \
					RI_MOUSE_RIGHT_BUTTON_UP)
				{
					buttons.remove(ButtonCode::BUTTON_RIGHT);
				}

				if (raw_data->data.mouse.usFlags & MOUSE_MOVE_ABSOLUTE) {
					this->pointer_position.x = raw_data->data.mouse.lLastX;
					this->pointer_position.y = raw_data->data.mouse.lLastY;
				} else {
					this->pointer_position.x += raw_data->data.mouse.lLastX;
					this->pointer_position.y += raw_data->data.mouse.lLastY;
				}
			}

			delete[] data;
			data = NULL;

			return 0;
		}
		#endif
		default:
			return DefWindowProc(window, message, word_parameter,
				long_parameter);
	}
}
#endif

void OpenGlWindow::initialize(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glAlphaFunc(GL_NOTEQUAL, 0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(33170 /* GL_GENERATE_MIPMAP_HINT */, GL_NICEST);
	glHint(GL_FOG_HINT, GL_NICEST);
	resize(size.x, size.y);
	glFlush();
}

void OpenGlWindow::resize(size_t width, size_t height) {
	size.x = width;
	size.y = height;

	if (height == 0) {
		height = 1;
	}
	glViewport(0, 0, width, height);
}

thewizardplusplus::anna::graphics::KeyCode::Types OpenGlWindow::convertKeyCode(
	unsigned long key_code)
{
	#ifdef OS_LINUX
	switch (key_code) {
		case XK_Escape:
			return KeyCode::KEY_ESCAPE;
		case XK_F1:
			return KeyCode::KEY_F1;
		case XK_F2:
			return KeyCode::KEY_F2;
		case XK_F3:
			return KeyCode::KEY_F3;
		case XK_F4:
			return KeyCode::KEY_F4;
		case XK_F5:
			return KeyCode::KEY_F5;
		case XK_F6:
			return KeyCode::KEY_F6;
		case XK_F7:
			return KeyCode::KEY_F7;
		case XK_F8:
			return KeyCode::KEY_F8;
		case XK_F9:
			return KeyCode::KEY_F9;
		case XK_F10:
			return KeyCode::KEY_F10;
		case XK_F11:
			return KeyCode::KEY_F11;
		case XK_F12:
			return KeyCode::KEY_F12;
		case XK_Print:
			return KeyCode::KEY_PRINT_SCREEN;
		case XK_Scroll_Lock:
			return KeyCode::KEY_SCROLL_LOCK;
		case XK_Pause:
			return KeyCode::KEY_PAUSE;

		case XK_grave:
		case XK_asciitilde:
			return KeyCode::KEY_TILDE;
		case XK_1:
		case XK_exclam:
			return KeyCode::KEY_1;
		case XK_2:
		case XK_at:
			return KeyCode::KEY_2;
		case XK_3:
		case XK_numbersign:
			return KeyCode::KEY_3;
		case XK_4:
		case XK_dollar:
			return KeyCode::KEY_4;
		case XK_5:
		case XK_percent:
			return KeyCode::KEY_5;
		case XK_6:
		case XK_asciicircum:
			return KeyCode::KEY_6;
		case XK_7:
		case XK_ampersand:
			return KeyCode::KEY_7;
		case XK_8:
		case XK_asterisk:
			return KeyCode::KEY_8;
		case XK_9:
		case XK_parenleft:
			return KeyCode::KEY_9;
		case XK_0:
		case XK_parenright:
			return KeyCode::KEY_0;
		case XK_minus:
		case XK_underscore:
			return KeyCode::KEY_MINUS;
		case XK_equal:
		case XK_plus:
			return KeyCode::KEY_EQUAL;
		case XK_BackSpace:
			return KeyCode::KEY_BACKSPACE;

		case XK_Tab:
			return KeyCode::KEY_TAB;
		case XK_Caps_Lock:
			return KeyCode::KEY_CAPS_LOCK;
		case XK_Shift_L:
		case XK_Shift_R:
			return KeyCode::KEY_SHIFT;
		case XK_Control_L:
		case XK_Control_R:
			return KeyCode::KEY_CONTROL;
		case XK_Super_L:
			return KeyCode::KEY_META_LEFT;
		case XK_Super_R:
			return KeyCode::KEY_META_RIGHT;
		case XK_Alt_L:
		case XK_Alt_R:
			return KeyCode::KEY_ALT;
		case XK_space:
			return KeyCode::KEY_SPACE;
		case XK_Menu:
			return KeyCode::KEY_MENU;
		case XK_Return:
		case XK_KP_Enter:
			return KeyCode::KEY_ENTER;

		case XK_A:
		case XK_a:
			return KeyCode::KEY_A;
		case XK_B:
		case XK_b:
			return KeyCode::KEY_B;
		case XK_C:
		case XK_c:
			return KeyCode::KEY_C;
		case XK_D:
		case XK_d:
			return KeyCode::KEY_D;
		case XK_E:
		case XK_e:
			return KeyCode::KEY_E;
		case XK_F:
		case XK_f:
			return KeyCode::KEY_F;
		case XK_G:
		case XK_g:
			return KeyCode::KEY_G;
		case XK_H:
		case XK_h:
			return KeyCode::KEY_H;
		case XK_I:
		case XK_i:
			return KeyCode::KEY_I;
		case XK_J:
		case XK_j:
			return KeyCode::KEY_J;
		case XK_K:
		case XK_k:
			return KeyCode::KEY_K;
		case XK_L:
		case XK_l:
			return KeyCode::KEY_L;
		case XK_M:
		case XK_m:
			return KeyCode::KEY_M;
		case XK_N:
		case XK_n:
			return KeyCode::KEY_N;
		case XK_O:
		case XK_o:
			return KeyCode::KEY_O;
		case XK_P:
		case XK_p:
			return KeyCode::KEY_P;
		case XK_Q:
		case XK_q:
			return KeyCode::KEY_Q;
		case XK_R:
		case XK_r:
			return KeyCode::KEY_R;
		case XK_S:
		case XK_s:
			return KeyCode::KEY_S;
		case XK_T:
		case XK_t:
			return KeyCode::KEY_T;
		case XK_U:
		case XK_u:
			return KeyCode::KEY_U;
		case XK_V:
		case XK_v:
			return KeyCode::KEY_V;
		case XK_W:
		case XK_w:
			return KeyCode::KEY_W;
		case XK_X:
		case XK_x:
			return KeyCode::KEY_X;
		case XK_Y:
		case XK_y:
			return KeyCode::KEY_Y;
		case XK_Z:
		case XK_z:
			return KeyCode::KEY_Z;
		case XK_bracketleft:
		case XK_braceleft:
			return KeyCode::KEY_BRACKET_LEFT;
		case XK_bracketright:
		case XK_braceright:
			return KeyCode::KEY_BRACKET_RIGHT;
		case XK_backslash:
		case XK_bar:
			return KeyCode::KEY_BACKSLASH;
		case XK_semicolon:
		case XK_colon:
			return KeyCode::KEY_SEMICOLON;
		case XK_apostrophe:
		case XK_quotedbl:
			return KeyCode::KEY_APOSTROPHE;
		case XK_comma:
		case XK_less:
			return KeyCode::KEY_COMMA;
		case XK_period:
		case XK_greater:
			return KeyCode::KEY_DOT;
		case XK_slash:
		case XK_question:
			return KeyCode::KEY_SLASH;

		case XK_Insert:
			return KeyCode::KEY_INSERT;
		case XK_Delete:
			return KeyCode::KEY_DELETE;
		case XK_Home:
			return KeyCode::KEY_HOME;
		case XK_End:
			return KeyCode::KEY_END;
		case XK_Page_Up:
			return KeyCode::KEY_PAGE_UP;
		case XK_Page_Down:
			return KeyCode::KEY_PAGE_DOWN;

		case XK_Up:
			return KeyCode::KEY_UP;
		case XK_Left:
			return KeyCode::KEY_LEFT;
		case XK_Down:
			return KeyCode::KEY_DOWN;
		case XK_Right:
			return KeyCode::KEY_RIGHT;

		case XK_Num_Lock:
			return KeyCode::KEY_NUM_LOCK;
		case XK_KP_Add:
			return KeyCode::KEY_NUM_ADD;
		case XK_KP_Subtract:
			return KeyCode::KEY_NUM_SUBTRACT;
		case XK_KP_Multiply:
			return KeyCode::KEY_NUM_MULTIPLY;
		case XK_KP_Divide:
			return KeyCode::KEY_NUM_DIVIDE;
		case XK_KP_0:
		case XK_KP_Insert:
			return KeyCode::KEY_NUM_0;
		case XK_KP_1:
		case XK_KP_End:
			return KeyCode::KEY_NUM_1;
		case XK_KP_2:
		case XK_KP_Down:
			return KeyCode::KEY_NUM_2;
		case XK_KP_3:
		case XK_KP_Next:
			return KeyCode::KEY_NUM_3;
		case XK_KP_4:
		case XK_KP_Left:
			return KeyCode::KEY_NUM_4;
		case XK_KP_5:
			return KeyCode::KEY_NUM_5;
		case XK_KP_Begin:
			return KeyCode::KEY_NUM_SPECIAL;
		case XK_KP_6:
		case XK_KP_Right:
			return KeyCode::KEY_NUM_6;
		case XK_KP_7:
		case XK_KP_Home:
			return KeyCode::KEY_NUM_7;
		case XK_KP_8:
		case XK_KP_Up:
			return KeyCode::KEY_NUM_8;
		case XK_KP_9:
		case XK_KP_Prior:
			return KeyCode::KEY_NUM_9;
		case XK_KP_Decimal:
		case XK_KP_Delete:
			return KeyCode::KEY_NUM_DECIMAL;
		default:
			return KeyCode::UNKNOWN_KEY;
	}
	#elif defined(OS_WINDOWS)
	switch (key_code) {
		case VK_ESCAPE:
			return KeyCode::KEY_ESCAPE;
		case VK_F1:
			return KeyCode::KEY_F1;
		case VK_F2:
			return KeyCode::KEY_F2;
		case VK_F3:
			return KeyCode::KEY_F3;
		case VK_F4:
			return KeyCode::KEY_F4;
		case VK_F5:
			return KeyCode::KEY_F5;
		case VK_F6:
			return KeyCode::KEY_F6;
		case VK_F7:
			return KeyCode::KEY_F7;
		case VK_F8:
			return KeyCode::KEY_F8;
		case VK_F9:
			return KeyCode::KEY_F9;
		case VK_F10:
			return KeyCode::KEY_F10;
		case VK_F11:
			return KeyCode::KEY_F11;
		case VK_F12:
			return KeyCode::KEY_F12;
		case VK_SNAPSHOT:
			return KeyCode::KEY_PRINT_SCREEN;
		case VK_SCROLL:
			return KeyCode::KEY_SCROLL_LOCK;
		case VK_PAUSE:
			return KeyCode::KEY_PAUSE;

		case VK_OEM_3:
			return KeyCode::KEY_TILDE;
		case 0x30:
			return KeyCode::KEY_1;
		case 0x31:
			return KeyCode::KEY_2;
		case 0x32:
			return KeyCode::KEY_3;
		case 0x33:
			return KeyCode::KEY_4;
		case 0x34:
			return KeyCode::KEY_5;
		case 0x35:
			return KeyCode::KEY_6;
		case 0x36:
			return KeyCode::KEY_7;
		case 0x37:
			return KeyCode::KEY_8;
		case 0x38:
			return KeyCode::KEY_9;
		case 0x39:
			return KeyCode::KEY_0;
		case 0xBD:
			return KeyCode::KEY_MINUS;
		case 0xBB:
			return KeyCode::KEY_EQUAL;
		case VK_BACK:
			return KeyCode::KEY_BACKSPACE;

		case VK_TAB:
			return KeyCode::KEY_TAB;
		case VK_CAPITAL:
			return KeyCode::KEY_CAPS_LOCK;
		case VK_SHIFT:
			return KeyCode::KEY_SHIFT;
		case VK_CONTROL:
			return KeyCode::KEY_CONTROL;
		case VK_LWIN:
			return KeyCode::KEY_META_LEFT;
		case VK_RWIN:
			return KeyCode::KEY_META_RIGHT;
		case VK_MENU:
			return KeyCode::KEY_ALT;
		case VK_SPACE:
			return KeyCode::KEY_SPACE;
		case VK_APPS:
			return KeyCode::KEY_MENU;
		case VK_RETURN:
			return KeyCode::KEY_ENTER;

		case 0x41:
			return KeyCode::KEY_A;
		case 0x42:
			return KeyCode::KEY_B;
		case 0x43:
			return KeyCode::KEY_C;
		case 0x44:
			return KeyCode::KEY_D;
		case 0x45:
			return KeyCode::KEY_E;
		case 0x46:
			return KeyCode::KEY_F;
		case 0x47:
			return KeyCode::KEY_G;
		case 0x48:
			return KeyCode::KEY_H;
		case 0x49:
			return KeyCode::KEY_I;
		case 0x4A:
			return KeyCode::KEY_J;
		case 0x4B:
			return KeyCode::KEY_K;
		case 0x4C:
			return KeyCode::KEY_L;
		case 0x4D:
			return KeyCode::KEY_M;
		case 0x4E:
			return KeyCode::KEY_N;
		case 0x4F:
			return KeyCode::KEY_O;
		case 0x50:
			return KeyCode::KEY_P;
		case 0x51:
			return KeyCode::KEY_Q;
		case 0x52:
			return KeyCode::KEY_R;
		case 0x53:
			return KeyCode::KEY_S;
		case 0x54:
			return KeyCode::KEY_T;
		case 0x55:
			return KeyCode::KEY_U;
		case 0x56:
			return KeyCode::KEY_V;
		case 0x57:
			return KeyCode::KEY_W;
		case 0x58:
			return KeyCode::KEY_X;
		case 0x59:
			return KeyCode::KEY_Y;
		case 0x5A:
			return KeyCode::KEY_Z;
		case VK_OEM_4:
			return KeyCode::KEY_BRACKET_LEFT;
		case VK_OEM_6:
			return KeyCode::KEY_BRACKET_RIGHT;
		case VK_OEM_5:
			return KeyCode::KEY_BACKSLASH;
		case VK_OEM_1:
			return KeyCode::KEY_SEMICOLON;
		case VK_OEM_7:
			return KeyCode::KEY_APOSTROPHE;
		case 0xBC:
			return KeyCode::KEY_COMMA;
		case 0xBE:
			return KeyCode::KEY_DOT;
		case VK_OEM_2:
			return KeyCode::KEY_SLASH;

		case VK_INSERT:
			return KeyCode::KEY_INSERT;
		case VK_DELETE:
			return KeyCode::KEY_DELETE;
		case VK_HOME:
			return KeyCode::KEY_HOME;
		case VK_END:
			return KeyCode::KEY_END;
		case VK_PRIOR:
			return KeyCode::KEY_PAGE_UP;
		case VK_NEXT:
			return KeyCode::KEY_PAGE_DOWN;

		case VK_UP:
			return KeyCode::KEY_UP;
		case VK_LEFT:
			return KeyCode::KEY_LEFT;
		case VK_DOWN:
			return KeyCode::KEY_DOWN;
		case VK_RIGHT:
			return KeyCode::KEY_RIGHT;

		case VK_NUMLOCK:
			return KeyCode::KEY_NUM_LOCK;
		case VK_ADD:
			return KeyCode::KEY_NUM_ADD;
		case VK_SUBTRACT:
			return KeyCode::KEY_NUM_SUBTRACT;
		case VK_MULTIPLY:
			return KeyCode::KEY_NUM_MULTIPLY;
		case VK_DIVIDE:
			return KeyCode::KEY_NUM_DIVIDE;
		case VK_NUMPAD0:
			return KeyCode::KEY_NUM_0;
		case VK_NUMPAD1:
			return KeyCode::KEY_NUM_1;
		case VK_NUMPAD2:
			return KeyCode::KEY_NUM_2;
		case VK_NUMPAD3:
			return KeyCode::KEY_NUM_3;
		case VK_NUMPAD4:
			return KeyCode::KEY_NUM_4;
		case VK_NUMPAD5:
			return KeyCode::KEY_NUM_5;
		case VK_CLEAR:
			return KeyCode::KEY_NUM_SPECIAL;
		case VK_NUMPAD6:
			return KeyCode::KEY_NUM_6;
		case VK_NUMPAD7:
			return KeyCode::KEY_NUM_7;
		case VK_NUMPAD8:
			return KeyCode::KEY_NUM_8;
		case VK_NUMPAD9:
			return KeyCode::KEY_NUM_9;
		case VK_DECIMAL:
			return KeyCode::KEY_NUM_DECIMAL;
		default:
			return KeyCode::UNKNOWN_KEY;
	}
	#endif
}

#ifdef OS_LINUX
ButtonCode::Types OpenGlWindow::convertButtonCode(unsigned int button_code) {
	switch (button_code) {
		case Button1:
			return ButtonCode::BUTTON_LEFT;
			break;
		case Button2:
			return ButtonCode::BUTTON_MIDDLE;
			break;
		case Button3:
			return ButtonCode::BUTTON_RIGHT;
			break;
		default:
			return ButtonCode::UNKNOWN_BUTTON;
	}
}
#endif
