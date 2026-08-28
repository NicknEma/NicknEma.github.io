#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE
#include <windows.h>

#pragma comment(lib, "user32")

#define MY_CONTROL 2001

LRESULT CALLBACK WindowProc(HWND Window, UINT MessageKind,
							WPARAM WParam, LPARAM LParam) {
	LRESULT Result = 0;
	switch (MessageKind) {
		case WM_CREATE: {
			RECT ClientRect;
			GetClientRect(Window, &ClientRect);
			int Left = 5;
			int Top = 5;
			int Width = ClientRect.right - ClientRect.left - 2*Left;
			int Height = ClientRect.bottom - ClientRect.top - 2*Top;
#if 0
			HWND Control = CreateWindowW(
				L"Static",
				L"Hello",
				WS_CHILD|WS_VISIBLE,
				5, 5, 200, 100,
				Window,
				NULL,
				GetModuleHandleW(NULL),
				NULL
			);
#elif 1
			HWND Control = CreateWindowW(
				L"Button",
				L"Hello",
				WS_CHILD|WS_VISIBLE,
				Left, Top, Width, Height,
				Window,
				(HMENU)MY_CONTROL,
				GetModuleHandleW(NULL),
				NULL
			);
#endif
		} break;

		case WM_COMMAND:
		{
			if (LOWORD(WParam) == MY_CONTROL)
				PostQuitMessage(0);
			// Result = DefWindowProcW(Window, MessageKind, WParam, LParam);
		} break;
		
		case WM_NOTIFY:
		{
			//Result = DefWindowProcW(Window, MessageKind, WParam, LParam);
		} break;
		
		case STN_CLICKED:break;
		
		case WM_CLOSE: PostQuitMessage(0); break;

		default: {
			Result = DefWindowProcW(Window, MessageKind, WParam, LParam);
		} break;
	}
	return Result;
}

int wWinMain(HINSTANCE Instance, HINSTANCE, wchar_t *, int)
{
	WNDCLASSW WindowClass = {0}; // Set everything to zero
	WindowClass.lpfnWndProc   = WindowProc;
	WindowClass.hInstance     = GetModuleHandleW(NULL);
	WindowClass.lpszClassName = L"Main Window Class";
	WindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	
	RegisterClassW(&WindowClass);
	
	HWND Window = CreateWindowW(
		WindowClass.lpszClassName,	// The class name
		L"Hello Windows",			// Title of the window
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,		// The "style" of the window
		CW_USEDEFAULT,				// Left edge
		CW_USEDEFAULT,				// Top edge
		200,				// Width
		100,				// Height
		NULL,						// Parent window	(optional)
		NULL,						// Menu				(optional)
		WindowClass.hInstance,		// Module handle
		NULL						// Additional data	(optional)
	);
	
	MSG Message;
	while (GetMessageW(&Message, NULL, 0, 0) > 0) {
		TranslateMessage(&Message);
		DispatchMessageW(&Message);
	}
}
