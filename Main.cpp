#include "Window.h"
#include "AppWindow.h"

int main()
{

	AppWindow wnd;
	
	wchar_t wnd_name[] = L"GameWindow";
	if (wnd.Init(wnd_name))
	{

		while (wnd.IsRunning())
		{

			wnd.Broadcast();

		}

	}

	return 0;

}
