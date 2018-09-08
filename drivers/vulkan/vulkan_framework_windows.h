/*
	Vulkan Framework Copyright (c) 2017 - 2018 Cengiz Terzibas

	Permission is hereby granted, free of charge, to any person obtaining a copy of
	this software and associated documentation files (the "Software"), to deal in the
	Software without restriction, including without limitation the rights to use, copy,
	modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
	and to permit persons to whom the Software is furnished to do so, subject to the
	following conditions:

	The above copyright notice and this permission notice shall be included in all copies
	or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
	PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
	FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
	OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
	DEALINGS IN THE SOFTWARE.

*/

#ifndef VULKAN_FRAMEWORK_WINDOWS_H
#define VULKAN_FRAMEWORK_WINDOWS_H

#define VKF_CHECK(A) assert(A)

#ifdef __linux__
#ifdef VKF_SURFACE_XCB
#define VK_USE_PLATFORM_XCB_KHR
#include <xcb/xcb_keysyms.h>
#include <X11/keysym.h>
#elif defined(VKF_SURFACE_XLIB)
#define VK_USE_PLATFORM_XLIB_KHR
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>
#elif defined(VKF_SURFACE_WAYLAND)
#define VK_USE_PLATFORM_WAYLAND_KHR
#include <wayland-client.h>
#endif
#elif defined(WIN32)
#if VKF_SURFACE_WIN32
#define VK_USE_PLATFORM_WIN32_KHR
#include <Windows.h>
#endif
#endif

#include <string>

namespace vkf {

	/**
	 * @class Windows
	 * @brief Helper class to handle cross platform windowing.
	 */
	class Windows {
		public:
			Windows(const std::string& title, uint32_t width, uint32_t height);
			~Windows();

			/// Create the window.
			int init();
#ifdef VKF_SURFACE_XCB
			int init(xcb_connection_t* connection, xcb_window_t window);
#elif defined(VKF_SURFACE_XLIB)
			int init(Display* display, Window window);
#elif defined(VKF_SURFACE_WIN32)
			int init(HINSTANCE instance, HWND hwnd);
#endif

			/// Destroy the window.
			int destroy();

			/// Set keyboard focus.
			void setInputFocus();

			/// Show the window.
			void show();

			/// Poll events.
			bool pollEvents();

			/// Returns the width of the window.
			uint32_t getWidth() const;

			/// Returns the height of the window.
			uint32_t getHeight() const;

			const std::string& getTitle() const;

#ifdef VKF_SURFACE_XCB
			/// Returns the native xcb connection handle.
			xcb_connection_t* getConnection() const;

			/// Return the native xcb window handle.
			xcb_window_t getWindow() const;

#elif defined(VKF_SURFACE_XLIB)

			/// Returns the native xcb connection handle.
			Display* getDisplay() const;

			/// Return the native xcb window handle.
			Window getWindow() const;

#elif defined(VKF_SURFACE_WIN32)
			HINSTANCE getInstance() const;

			HWND getHandle() const;
#endif

		private:
#ifdef VKF_SURFACE_XCB
			xcb_connection_t* m_connection;
			xcb_screen_t* m_screen;
			xcb_window_t m_window;

			xcb_key_symbols_t* m_kss;
			xcb_intern_atom_cookie_t m_cookie;
			xcb_intern_atom_reply_t* m_reply;
			xcb_intern_atom_cookie_t m_cookie2;
			xcb_intern_atom_reply_t* m_atom_wm_delete_window;

#elif defined(VKF_SURFACE_XLIB)
			Display* m_display;
			Window m_window;
			Atom WM_PROTOCOLS;
			Atom WM_DELETE_WINDOW;
#elif defined(VKF_SURFACE_WIN32)
			HINSTANCE m_instance;
			HWND m_handle;
#endif

			std::string m_title;
			uint32_t m_width;
			uint32_t m_height;
	};
}
#endif
