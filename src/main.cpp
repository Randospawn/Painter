#include <Windows.h>
#include <iostream>




LRESULT CALLBACK mwcProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int main(int argc, char **argv) {
	HINSTANCE hInst = GetModuleHandleW(NULL); // Gets the hInst for this process
	const wchar_t mwcn[] = L"MAIN";
	WNDCLASSW mwc = {};
	mwc.lpfnWndProc = mwcProc;
	mwc.hInstance = hInst;
	mwc.lpszClassName = mwcn;
	RegisterClassW(&mwc);
	
	
	HWND hWnd = CreateWindowExW(
		0,
		mwcn,
		L"Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL, // Parent window
		NULL, // Menu 
		hInst,
		NULL
	);
	if (hWnd == NULL) {
		return 0;
	}
	ShowWindow(hWnd, SW_SHOWNORMAL);
	
	
	MSG msg = {};
	while (GetMessageW(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	
	return 0;
}



LRESULT CALLBACK mwcProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CLOSE:
			DestroyWindow(hWnd);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				// Render on the window
				FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
				EndPaint(hWnd, &ps);
				return 0;
			}
		default:
			break;
	}
	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}







