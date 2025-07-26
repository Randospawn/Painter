#ifndef __STATES_H__
#define __STATES_H__


#include <Windows.h>


#define W_MS 0
#define W_PS 4


int W_S = W_MS;
int B_W = 20;
unsigned char M_BS = false; // I think I'll call you "mouse bullshit" instead from now on!
int M_X, M_Y;
LRESULT CALLBACK mwcProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);





#endif


