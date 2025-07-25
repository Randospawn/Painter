#include <Windows.h>
#include <dwmapi.h>
#include <iostream>
#include <cmath>
#include <numbers>




unsigned char W_PS = false;
int B_W = 20;
unsigned char M_BS = false; // I think I'll call you "mouse bullshit" instead from now on!
int M_X, M_Y;
LRESULT CALLBACK mwcProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int main(int argc, char **argv) {
	HINSTANCE hInst = GetModuleHandleW(NULL);
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
	
	
	POINT mPos;
	GetCursorPos(&mPos);
	
	
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
				if (W_PS != false) {
					if (M_BS != true) {
						l = (M_X - B_W), t = (M_Y + B_W), r = (M_X + B_W), b = (M_Y - B_W);
						// Find better & more efficient way of forcing a window redraw (also make menus for creating new "projects")
						InvalidateRect(hWnd, NULL, TRUE); // Forces the whole window to repaint
						UpdateWindow(hWnd);
					}
				}
				return 0;
			}
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				HBRUSH brush = CreateSolidBrush(RGB(40, 40, 40));
				SelectObject(hdc, brush);
				FillRect(hdc, &ps.rcPaint, NULL);
				
				if (W_PS != false) {
					if (M_BS != true) {
						HBRUSH nb = CreateSolidBrush(RGB(0, 0, 0));
						SelectObject(hdc, nb);
						Ellipse(hdc, l, t, r, b);
						SelectObject(hdc, brush);
						DeleteObject(nb);
					}
				}
				
				EndPaint(hWnd, &ps);
				DeleteObject(brush);
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







