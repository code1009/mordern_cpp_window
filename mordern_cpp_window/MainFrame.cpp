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
	//-----------------------------------------------------------------------
	print(L"MainFrame.ctor() - begin");


	//-----------------------------------------------------------------------
	registerWindowMessageHandler();


	//-----------------------------------------------------------------------
	initializeWindowClass();
	registerWindowClass();
	createWindow(getWindowInstance()->loadString(IDS_APP_TITLE).c_str());


	//-----------------------------------------------------------------------


	//-----------------------------------------------------------------------
	::ShowWindow(_Handle, SW_SHOW);
	::UpdateWindow(_Handle);


	//-----------------------------------------------------------------------
	print(L"MainFrame.ctor() - end");
}

MainFrame::~MainFrame()
{
	print(L"MainFrame.dtor()");
}

void MainFrame::registerWindowMessageHandler(void)
{
	_WindowMessageHandlerMap[WM_CREATE] = [this](WindowMessage& windowMessage)
	{
		onCreate();

		defaultWindowMessageHandler(windowMessage);
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
			defaultWindowMessageHandler(windowMessage);
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
	BaseWindow::initializeWindowClass();


	static std::wstring windowClassName = getWindowInstance()->loadString(IDC_MORDERNCPPWINDOW);


	_WindowClass.lpszClassName = windowClassName.c_str();
	_WindowClass.lpszMenuName  = getWindowInstance()->makeIntResource(IDC_MORDERNCPPWINDOW);
	_WindowClass.hIcon         = getWindowInstance()->loadIcon(IDI_MORDERNCPPWINDOW);
	_WindowClass.hIconSm       = getWindowInstance()->loadIcon(IDI_SMALL);
}

void MainFrame::onCreate(void)
{
	print(L"MainFrame.onCreate()");
}

void MainFrame::onDestory(void)
{
	print(L"MainFrame.onDestory() - begin");

	::PostQuitMessage(0);

	print(L"MainFrame.onDestory() - end");
}

void MainFrame::onClose(void)
{
	print(L"MainFrame.onClose() - begin");

	destroyWindow();

	print(L"MainFrame.onClose() - end");
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
	// ctor()안에서 호출 되지만 createWindow()호출 이후라서 _Handle 유효함

	PAINTSTRUCT ps;
	
	
	HDC hdc = BeginPaint(_Handle, &ps);
	RECT rect{ 0,0, 500, 500 };

	DrawText(hdc, L"MainFrame", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	EndPaint(_Handle, &ps);
}
