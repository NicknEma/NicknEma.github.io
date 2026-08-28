#include <stdio.h>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define UNICODE
#include <windows.h>
#include <shlobj.h>

#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>
#include <stdio.h>

#pragma comment(lib, "user32")
#pragma comment(lib, "comctl32")

#define MY_CONTROL 2001

HINSTANCE g_hInst;

static void ResizeListView(HWND hwndListView, HWND hwndParent) {
	RECT  rc;
	GetClientRect(hwndParent, &rc);
	MoveWindow( hwndListView, 
	            rc.left,
	            rc.top,
	            rc.right - rc.left,
	            rc.bottom - rc.top,
	            TRUE);
	//only call this if we want the LVS_NOSCROLL style
	//PositionHeader(hwndListView);
}

static HWND CreateListView(HINSTANCE hInstance, HWND hwndParent) {
	DWORD dwStyle =   WS_TABSTOP |           WS_CHILD |             WS_BORDER |             WS_VISIBLE |            LVS_AUTOARRANGE |            LVS_REPORT |             LVS_OWNERDATA;
	HWND hwndListView = CreateWindowEx(   WS_EX_CLIENTEDGE,          // ex style
	                                 WC_LISTVIEW,               // class name - defined in commctrl.h
	                                 TEXT(""),                        // dummy text
	                                 dwStyle,                   // style
	                                 0,                         // x position
	                                 0,                         // y position
	                                 0,                         // width
	                                 0,                         // height
	                                 hwndParent,                // parent
	                                 (HMENU)MY_CONTROL,        // ID
	                                 g_hInst,                   // instance
	                                 NULL);                     // no extra data
	
	ResizeListView(hwndListView, hwndParent);
	
	//set the image lists
	HIMAGELIST himlSmall = ImageList_Create(16, 16, ILC_COLORDDB | ILC_MASK, 1, 0);
	HIMAGELIST himlLarge = ImageList_Create(32, 32, ILC_COLORDDB | ILC_MASK, 1, 0);
	if (himlSmall && himlLarge) {
	   HICON hIcon = 0;
	
	   //set up the small image list
	   // hIcon = LoadImage(g_hInst, MAKEINTRESOURCE(IDI_DISK), IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
	   ImageList_AddIcon(himlSmall, hIcon);
	
	   //set up the large image list
	   // hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_DISK));
	   ImageList_AddIcon(himlLarge, hIcon);
	
	   ListView_SetImageList(hwndListView, himlSmall, LVSIL_SMALL);
	   ListView_SetImageList(hwndListView, himlLarge, LVSIL_NORMAL);
	   }
	
	return hwndListView;
	}
	#define ITEM_COUNT   100000
static BOOL InsertListViewItems(HWND hwndListView) {
	ListView_DeleteAllItems(hwndListView); //empty the list
	ListView_SetItemCount(hwndListView, ITEM_COUNT);	//set the number of items in the list
	return TRUE;
}

static BOOL InitListView(HWND hwndListView) {
	TCHAR       szString[5][20] = {TEXT("Main Column"), TEXT("Column 1"), TEXT("Column 2"), TEXT("Column 3"), TEXT("Column 4")};
	
	//empty the list
	ListView_DeleteAllItems(hwndListView);
	
	//initialize the columns
	LV_COLUMN   lvColumn;
	lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvColumn.fmt = LVCFMT_LEFT;
	lvColumn.cx = 120;
	for (int i = 0; i < 5; i++) {
		lvColumn.pszText = szString[i];
		ListView_InsertColumn(hwndListView, i, &lvColumn);
	}
	
	InsertListViewItems(hwndListView);
	
	return TRUE;
}

LRESULT ListViewNotify(HWND hWnd, LPARAM lParam) {
	LPNMHDR  lpnmh = (LPNMHDR) lParam;
	HWND     hwndListView = GetDlgItem(hWnd, MY_CONTROL);
	
	switch(lpnmh->code) {
	   case LVN_GETDISPINFO: {
#if 0
	      LV_DISPINFO *lpdi = (LV_DISPINFO *)lParam;
	      wchar_t szString[MAX_PATH];
	
	      if(lpdi->item.iSubItem)
	         {
	         if(lpdi->item.mask & LVIF_TEXT)
	            {
	            _sntprintf_s(szString, _countof(szString), _TRUNCATE,
							 TEXT("Item %d - Column %d"),
							 lpdi->item.iItem + 1, lpdi->item.iSubItem);
	            _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
						   szString, _TRUNCATE);
	            }
	         }
	      else
	         {
	         if(lpdi->item.mask & LVIF_TEXT)
	            {
	            _sntprintf_s(szString, _countof(szString), _TRUNCATE,
							 TEXT("Item %d"), lpdi->item.iItem + 1);
	            _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
						   szString, _TRUNCATE);
	            }
	
	         if(lpdi->item.mask & LVIF_IMAGE)
	            {
	            lpdi->item.iImage = 0;
	            }
	         }
#endif
	      }
	      return 0;

	   case LVN_ODCACHEHINT: {
	      LPNMLVCACHEHINT   lpCacheHint = (LPNMLVCACHEHINT)lParam;
	      /*
	      This sample doesn't use this notification, but this is sent when the 
	      ListView is about to ask for a range of items. On this notification, 
	      you should load the specified items into your local cache. It is still 
	      possible to get an LVN_GETDISPINFO for an item that has not been cached, 
	      therefore, your application must take into account the chance of this 
	      occurring.
	      */
	      }
	      return 0;
	
	   case LVN_ODFINDITEM:
	      {
	      LPNMLVFINDITEM lpFindItem = (LPNMLVFINDITEM)lParam;
	      /*
	      This sample doesn't use this notification, but this is sent when the 
	      ListView needs a particular item. Return -1 if the item is not found.
	      */
	      }
	      return 0;
	   }
	
	return 0;
}

LRESULT CALLBACK WindowProc(HWND Window, UINT MessageKind,
							WPARAM WParam, LPARAM LParam) {
static HWND hwndListView;
	LRESULT Result = 0;
	switch (MessageKind) {
		case WM_CREATE: {
			hwndListView = CreateListView(GetModuleHandleW(NULL), Window);
      	InitListView(hwndListView);
		} break;
		
		case WM_SIZE:
      ResizeListView(hwndListView, Window);
      break;

		case WM_COMMAND:
		{
			if (LOWORD(WParam) == MY_CONTROL)
				PostQuitMessage(0);
			// Result = DefWindowProcW(Window, MessageKind, WParam, LParam);
		} break;
		
		case WM_NOTIFY:
		{
			Result = ListViewNotify(Window, LParam);
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
	g_hInst = Instance;
	InitCommonControls();
	
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
		CW_USEDEFAULT,				// Width
		CW_USEDEFAULT,				// Height
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
