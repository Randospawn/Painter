#include "window.hpp"
#include <cstdlib>




Window::Window(wchar_t *windowClass) {
	this->ClassName = windowClass;
	this->wc.lpfnWndProc = nullptr;
	this->wc.hInstance = GetModuleHandleW(NULL);
	this->wc.lpszClassName = this->ClassName;
}

void Window::Open(int width, int height, wchar_t *title) {
	RegisterClassW(&this->wc);
	this->Wdw = CreateWindowExW(
		0,
		this->ClassName,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, width, height,
		NULL,
		NULL,
		this->wc.hInstance,
		NULL
	);
	if (this->Wdw == NULL) {
		exit(-1);
	}
	ShowWindow(this->Wdw, SW_SHOWNORMAL);
	return;
}

Window::~Window(void) {
	UnregisterClassW(this->ClassName, GetModuleHandleW(NULL));
	return;
}







