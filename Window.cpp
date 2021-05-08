#include "Window.h"
#include <iostream>

#define EDWND0 L"WNDcexwS0"

Window* window_ptr = nullptr;

int x = 0;

Window::Window()
{
}

bool Window::Broadcast()
{

	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{

		TranslateMessage(&msg);
		DispatchMessage (&msg);

	}

	OnUpdate();

	Sleep(1);

	return true;
	
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{

		case(WM_CREATE): //If you cant tell what these do, I feel bad for you.
		{

			window_ptr->OnCreate();

			break;

		}

		case(WM_DESTROY):
		{

			//Get a pointer to the window
			Window* window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
			window_ptr->OnDestroy();
			::PostQuitMessage(0);
			break;

		}

		case(WM_PAINT):
		{

			HDC hdc = ::GetDC(hWnd);

			Rectangle(hdc, 0 + x++, 0, 10 + x, 10);

			break;

		}

		default:
			return ::DefWindowProcW(hWnd, msg, wParam, lParam);

	}

	return NULL;

}

bool Window::Init(wchar_t wnd_name[])
{

	const wchar_t wndCLASS[] = EDWND0;

	//Create the wndcexw for styling the window
	WNDCLASSEXW wndcexw;
	wndcexw.cbClsExtra    = NULL;
	wndcexw.cbSize        = sizeof(wndcexw);
	wndcexw.cbWndExtra    = NULL;
	wndcexw.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wndcexw.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndcexw.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
	wndcexw.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);
	wndcexw.hInstance     = NULL;
	wndcexw.lpszClassName = wndCLASS;
	wndcexw.lpszMenuName  = L"";
	wndcexw.style         = NULL;
	wndcexw.lpfnWndProc   = WndProc;

	//if this fails return false
	if (!::RegisterClassEx(&wndcexw))
		return false;

	if (window_ptr == nullptr)
		window_ptr =  this;

	//Create the window
	w_hwnd = ::CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, wndCLASS, wnd_name, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 2024, 768, NULL, NULL, NULL, NULL);

	if (!w_hwnd)
		return false;

	//Show the window
	::ShowWindow(w_hwnd, SW_SHOW);

	//Flag the window as running
	open = TRUE;

	return true;
}

bool Window::Release()
{

	if (!::DestroyWindow(w_hwnd)) return false; return true;
	
}

void Window::OnCreate()
{
}

void Window::OnDestroy()
{

	open = FALSE;

}

void Window::OnUpdate()
{

	InvalidateRect(w_hwnd, NULL, FALSE);

}

BOOL Window::IsRunning()
{
	
	return open;

}

Window::~Window()
{
}
