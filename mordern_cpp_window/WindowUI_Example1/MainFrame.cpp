﻿/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"
#include "../resource.h"

#include "../WindowUI/Core.hpp"
#include "../WindowUI/WindowMessageManipulator.hpp"

#include "MainFrame.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Example1
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
MainFrame::MainFrame()
{
	//-----------------------------------------------------------------------
	WindowUI::debugPrintln(L"MainFrame.ctor() - begin");


	//-----------------------------------------------------------------------
	registerWindowMessageHandler();


	//-----------------------------------------------------------------------
	initializeWindowClass();
	registerWindowClass();
	createWindow(WindowUI::getWindowInstance()->loadString(IDS_APP_TITLE).c_str());


	//-----------------------------------------------------------------------


	//-----------------------------------------------------------------------
	::ShowWindow(getHandle(), SW_SHOW);
	::UpdateWindow(getHandle());


	//-----------------------------------------------------------------------
	WindowUI::debugPrintln(L"MainFrame.ctor() - end");
}

MainFrame::~MainFrame()
{
	WindowUI::debugPrintln(L"MainFrame.dtor()");
}

void MainFrame::registerWindowMessageHandler(void)
{
	getWindowMessageHandler(WM_NCCREATE) = [this](WindowUI::WindowMessage& windowMessage)
	{ 
		WindowUI::WM_NCCREATE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


		onNcCreate();
		//defaultWindowMessageHandler(windowMessage);
		
		windowMessageManipulator.Result(true);
	};

	getWindowMessageHandler(WM_NCDESTROY) = [this](WindowUI::WindowMessage& windowMessage)
	{ 
		onNcDestory(); 
		//defaultWindowMessageHandler(windowMessage);
	};

	getWindowMessageHandler(WM_CREATE) = [this](WindowUI::WindowMessage& windowMessage)
	{
		WindowUI::WM_CREATE_WindowMessageManipulator windowMessageManipulator(&windowMessage);

		windowMessageManipulator.lpCreateStruct();
		onCreate();
		//windowMessageManipulator.Result(0);

		//defaultWindowMessageHandler(windowMessage);
	};

	getWindowMessageHandler(WM_DESTROY) = [this](WindowUI::WindowMessage& windowMessage)
	{
		onDestory();
	};

	getWindowMessageHandler(WM_CLOSE) = [this](WindowUI::WindowMessage& windowMessage)
	{
		onClose();
	};

	getWindowMessageHandler(WM_COMMAND) = [this](WindowUI::WindowMessage& windowMessage)
	{
		// void OnCommand(UINT uNotifyCode, int nID, CWindow wndCtl)
		// func((UINT)HIWORD(wParam), (int)LOWORD(wParam), (HWND)lParam);
		bool rv = onCommand((UINT)HIWORD(windowMessage.wParam), (int)LOWORD(windowMessage.wParam), (HWND)windowMessage.lParam);
		if (!rv)
		{
			defaultWindowMessageHandler(windowMessage);
		}
	};

	getWindowMessageHandler(WM_PAINT) = [this](WindowUI::WindowMessage& windowMessage)
	{
		// void OnPaint(CDCHandle dc)
		// func((HDC)wParam);
		onPaint((HDC)windowMessage.wParam);
	};
}

void MainFrame::initializeWindowClass(void)
{
	BaseWindow::initializeWindowClass();


	static std::wstring windowClassName = WindowUI::getWindowInstance()->loadString(IDC_MORDERNCPPWINDOW);


	getWindowClass().lpszClassName = windowClassName.c_str();
	getWindowClass().lpszMenuName  = WindowUI::getWindowInstance()->makeIntResource(IDC_MORDERNCPPWINDOW);
	getWindowClass().hIcon         = WindowUI::getWindowInstance()->loadIcon(IDI_MORDERNCPPWINDOW);
	getWindowClass().hIconSm       = WindowUI::getWindowInstance()->loadIcon(IDI_SMALL);
}

void MainFrame::onNcCreate(void)
{
	WindowUI::debugPrintln(L"MainFrame.onNcCreate()");
}

void MainFrame::onNcDestory(void)
{
	WindowUI::debugPrintln(L"MainFrame.onNcDestory()");
}

void MainFrame::onCreate(void)
{
	WindowUI::debugPrintln(L"MainFrame.onCreate()");
}

void MainFrame::onDestory(void)
{
	WindowUI::debugPrintln(L"MainFrame.onDestory() - begin");

	::PostQuitMessage(0);

	WindowUI::debugPrintln(L"MainFrame.onDestory() - end");
}

void MainFrame::onClose(void)
{
	WindowUI::debugPrintln(L"MainFrame.onClose() - begin");

	destroyWindow();

	WindowUI::debugPrintln(L"MainFrame.onClose() - end");
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
	// ctor()안에서 호출 되지만 createWindow()호출 이후라서 getHandle() 유효함

	PAINTSTRUCT ps;
	
	
	HDC hdc = BeginPaint(getHandle(), &ps);
	RECT rect{ 0,0, 500, 500 };

	DrawText(hdc, L"MainFrame", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	EndPaint(getHandle(), &ps);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}



