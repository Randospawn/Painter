#include <Windows.h>
#include <states/states.h>
#include <dwmapi.h>
#include <iostream>
#include <cmath>
#include <numbers>






// UUUuuUUuUuuUuUhhhh this is sooo much better than opengl
int main(int argc, char **argv) {
	HINSTANCE hInst = GetModuleHandleW(NULL);
	const wchar_t mwcn[] = L"MAIN";
	WNDCLASSW mwc = {};
	mwc.lpfnWndProc = mwcProc;
	mwc.hInstance = hInst;
	mwc.lpszClassName = mwcn;
	RegisterClassW(&mwc);
	
	
	// Lokat how fucking easy making this shit will be
	HWND hWnd = CreateWindowExW(
		0,
		mwcn,
		L"Window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInst,
		NULL
	);
	if (hWnd == NULL) {
		return 0;
	}
	ShowWindow(hWnd, SW_SHOWNORMAL);
	
	
	BOOL dmt = TRUE;
	HRESULT hr = DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &dmt, sizeof(dmt));
	if (SUCCEEDED(hr) != true) {
		DestroyWindow(hWnd);
	}
	
	
	MSG msg = {};
	while (GetMessageW(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	
	
	return 0;
}



LRESULT CALLBACK mwcProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static int l, t, r, b;
	switch (uMsg) {
		case WM_CLOSE:
			DestroyWindow(hWnd);
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_MOUSEMOVE:
			{
				M_X = LOWORD(lParam);
				M_Y = HIWORD(lParam);
				return 0;
			}
		case WM_PAINT: // OH FUCK NO GPO BACK
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				HBRUSH b = CreateSolidBrush(RGB(40, 40, 40));
				SelectObject(hdc, b);
				
				FillRect(hdc, &ps.rcPaint, NULL);
				
				EndPaint(hWnd, &ps);
				DeleteObject(b);
				return 0;
			}
		case WM_LBUTTONDOWN:
			M_BS = true;
			return 0;
		case WM_LBUTTONUP:
			M_BS = false;
			return 0;
		default:
			break;
	}
	return DefWindowProcW(hWnd, uMsg, wParam, lParam);
}







