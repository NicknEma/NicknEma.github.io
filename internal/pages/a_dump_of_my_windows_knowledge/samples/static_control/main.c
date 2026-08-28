#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE
#include <windows.h>

#pragma comment(lib, "user32")

typedef struct {
	DWORD Style;
	wchar_t *Text;
} static_template;

static static_template StaticTemplates[] = {
	{ 0, L"This is a static control" },
	{ WS_BORDER, L"This one has a border" },
	{ SS_SIMPLE, L"Simple" },
	{ WS_BORDER|SS_LEFT, L"Left-aligned. The text is very long and cannot be displayed on a single line." },
	{ WS_BORDER|SS_CENTER, L"Center-aligned. The text is very long and cannot be displayed on a single line." },
	{ WS_BORDER|SS_RIGHT, L"Right-aligned. The text is very long and cannot be displayed on a single line." },
	{ SS_BLACKFRAME, L"Black frame" },
	{ SS_BLACKRECT, L"Black rect" },
	{ SS_GRAYFRAME, L"Gray frame" },
	{ SS_GRAYRECT, L"Gray rect" },
	{ SS_WHITEFRAME, L"White frame" },
	{ SS_WHITERECT, L"White rect" },
	{ WS_BORDER|SS_ENDELLIPSIS, L"C:\\dev\\websites\\NicknEma.github.io\\internal\\pages\\a_dump_of_my_windows_knowledge\\samples\\static_control\\" },
	{ WS_BORDER|SS_WORDELLIPSIS, L"C:\\dev\\websites\\NicknEma.github.io\\internal\\pages\\a_dump_of_my_windows_knowledge\\samples\\static_control\\" },
	{ WS_BORDER|SS_PATHELLIPSIS, L"C:\\dev\\websites\\NicknEma.github.io\\internal\\pages\\a_dump_of_my_windows_knowledge\\samples\\static_control\\" },
	{ SS_SUNKEN, L"Sunken" },
	{ SS_LEFTNOWORDWRAP, L"Tabs\tare\texpanded" },
	{ SS_ETCHEDFRAME, L"Frame" },
	{ SS_EDITCONTROL, L"Edit" },
};

static LRESULT CALLBACK WindowProc(HWND Window, UINT MessageKind, WPARAM WParam, LPARAM LParam) {
	LRESULT Result = 0;
	
	switch (MessageKind) {
		case WM_CREATE: {
			RECT ClientRect;
			GetClientRect(Window, &ClientRect);
			
			// int NumCols = 4;
			int NumRows = (ARRAYSIZE(StaticTemplates) + 1); // / NumCols;
			int Left = 5;
			int Top = 5;
			int Width = (ClientRect.right - ClientRect.left - 2*Left); // / NumCols;
			int Height = (ClientRect.bottom - ClientRect.top - 2*Top) / NumRows;
			
			int Y = 0;
			for (int I = 0; I < ARRAYSIZE(StaticTemplates); ++I) {
				int X = 0;
				HWND Control;
				Control = CreateWindowW(
					L"Static",
					StaticTemplates[I].Text,
					WS_CHILD|WS_VISIBLE|StaticTemplates[I].Style,
					Left + X, Top + Y, Width, Height,
					Window,
					NULL,
					GetModuleHandleW(NULL),
					NULL
				);
				// X += Width;
				Y += Height;
			}
		} break;

		case WM_COMMAND:
		{
			Result = DefWindowProcW(Window, MessageKind, WParam, LParam);
		} break;
		
		case WM_NOTIFY:
		{
			Result = DefWindowProcW(Window, MessageKind, WParam, LParam);
		} break;
		
		case WM_CLOSE: PostQuitMessage(0); break;

		default: {
			Result = DefWindowProcW(Window, MessageKind, WParam, LParam);
		} break;
	}
	
	return Result;
}

int wWinMain(HINSTANCE Instance, HINSTANCE PrevInstance, wchar_t *CommandLine, int CommandShow)
{
	WNDCLASSW WindowClass = {0}; // Set everything to zero
	WindowClass.lpfnWndProc   = WindowProc;
	WindowClass.hInstance     = Instance;
	WindowClass.hCursor       = LoadCursorW(NULL, IDC_ARROW);
	WindowClass.lpszClassName = L"Main Window Class";
	WindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	
	RegisterClassW(&WindowClass);
	
	HWND Window = CreateWindowW(
		WindowClass.lpszClassName,	// The class name
		L"Hello Windows",			// Title of the window
		WS_OVERLAPPEDWINDOW|WS_VISIBLE,		// The "style" of the window
		10,				// Left edge
		10,				// Top edge
		1000,				// Width
		800,				// Height
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
	
	return 0;
}
