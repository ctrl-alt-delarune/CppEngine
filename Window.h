#pragma once
#include <Windows.h>





class Window
{

private:
	HWND w_hwnd;
	BOOL open = NULL;

public:
	Window();

	bool Broadcast();

	bool Init(wchar_t wnd_name[]);
	bool Release();

	virtual void OnCreate ();
	virtual void OnDestroy();
	virtual void OnUpdate ();

	BOOL IsRunning();

	~Window();

};
