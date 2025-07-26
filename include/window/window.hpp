#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__


#include <Windows.h>




class Window {
	public:
		wchar_t *ClassName;
		WNDCLASSW wc = {};
		HWND Wdw;
		
		Window(wchar_t *windowClass);
		void Open(int width, int height, wchar_t *title);
		~Window(void);
};


#endif


