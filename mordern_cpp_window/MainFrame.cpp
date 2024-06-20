/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "framework.h"
#include "resource.h"

#include "WindowAPI.hpp"
#include "MainFrame.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
MainFrame::MainFrame()
{
	print("MainFrame.ctor() - begin");

	registerWindowMessageHandler();

	initializeWindowClass();
	registerWindowClass();
	createWindow(0, L"MainFrame");
	::ShowWindow(_hWnd, SW_SHOW);
	::UpdateWindow(_hWnd);


	print("MainFrame.ctor() - end");
}

MainFrame::~MainFrame()
{
	print("MainFrame.dtor()");
}

void MainFrame::registerWindowMessageHandler(void)
{
	_WindowMessageHandlerMap[WM_CREATE] = [this](WindowMessage& windowMessage)
	{
		onCreate();
		callDefaultWindowProc(windowMessage);
	}
	;

	_WindowMessageHandlerMap[WM_DESTROY] = [this](WindowMessage& windowMessage)
	{
		onDestory();
	}
	;

	_WindowMessageHandlerMap[WM_CLOSE] = [this](WindowMessage& windowMessage)
	{
		onClose();
	}
	;

	_WindowMessageHandlerMap[WM_COMMAND] = [this](WindowMessage& windowMessage)
	{
		// void OnCommand(UINT uNotifyCode, int nID, CWindow wndCtl)
		// func((UINT)HIWORD(wParam), (int)LOWORD(wParam), (HWND)lParam);
		bool rv = onCommand((UINT)HIWORD(windowMessage.wParam), (int)LOWORD(windowMessage.wParam), (HWND)windowMessage.lParam);
		if (!rv)
		{
			callDefaultWindowProc(windowMessage);
		}
	}
	;

	_WindowMessageHandlerMap[WM_PAINT] = [this](WindowMessage& windowMessage)
	{
		// void OnPaint(CDCHandle dc)
		// func((HDC)wParam);
		onPaint((HDC)windowMessage.wParam);
	}
	;
}

void MainFrame::initializeWindowClass(void)
{
	Window::initializeWindowClass();

	_WindowClass.lpszMenuName = MAKEINTRESOURCEW(IDC_MORDERNCPPWINDOW);
	_WindowClass.hIcon = LoadIcon(_WindowClass.hInstance, MAKEINTRESOURCE(IDI_MORDERNCPPWINDOW));
	_WindowClass.hIconSm = LoadIcon(_WindowClass.hInstance, MAKEINTRESOURCE(IDI_SMALL));
}

void MainFrame::onCreate(void)
{
	print("MainFrame.onCreate()");
}

void MainFrame::onDestory(void)
{
	print("MainFrame.onDestory() - begin");

	::PostQuitMessage(0);

	print("MainFrame.onDestory() - end");
}

void MainFrame::onClose(void)
{
	print("MainFrame.onClose() - begin");

	destroyWindow();

	print("MainFrame.onClose() - end");
}

bool MainFrame::onCommand(UINT uNotifyCode, int nID, HWND wndCtl)
{
	switch (nID)
	{
	case IDM_ABOUT:
		return true;
		break;

	case IDM_EXIT:
		destroyWindow();
		return true;
		break;

	default:
		break;
	}


	return false;
}

void MainFrame::onPaint(HDC hDC)
{
	// 최초 실행시 UpdateWindow()에 의해서
	// ctor()안에서 호출 되지만 createWindow()호출 이후라서 _hWnd 유효함

	PAINTSTRUCT ps;
	
	
	HDC hdc = BeginPaint(_hWnd, &ps);
	RECT rect{ 0,0, 100, 100 };

	DrawText(hdc, L"MainFrame", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	EndPaint(_hWnd, &ps);
}
