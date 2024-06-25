﻿/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"
#include "../res/resource.h"

#include "../WindowUI/Core.hpp"
#include "../WindowUI/WindowMessageManipulator.hpp"

#include "AboutDialog.hpp"
#include "View.hpp"
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
	_View = std::make_shared<View>(getHandle());


	//-----------------------------------------------------------------------
	::ShowWindow(getHandle(), SW_SHOW);
	::UpdateWindow(getHandle());


	//-----------------------------------------------------------------------
	WindowUI::debugPrintln(L"MainFrame.ctor() - end");
}

MainFrame::~MainFrame()
{
	WindowUI::debugPrintln(L"MainFrame.dtor() - begin");

	WindowUI::debugPrintln(L"MainFrame.dtor() - end");
}

void MainFrame::registerWindowMessageHandler(void)
{
	getWindowMessageHandler(WM_NCCREATE) = [this](WindowUI::WindowMessage& windowMessage) { onNcCreate(windowMessage); };
	getWindowMessageHandler(WM_NCDESTROY) = [this](WindowUI::WindowMessage& windowMessage) { onNcDestory(windowMessage); };
	getWindowMessageHandler(WM_CREATE) = [this](WindowUI::WindowMessage& windowMessage) { onCreate(windowMessage); };
	getWindowMessageHandler(WM_DESTROY) = [this](WindowUI::WindowMessage& windowMessage) { onDestory(windowMessage); };
	getWindowMessageHandler(WM_CLOSE) = [this](WindowUI::WindowMessage& windowMessage) { onClose(windowMessage); };
	getWindowMessageHandler(WM_SIZE) = [this](WindowUI::WindowMessage& windowMessage) { onSize(windowMessage); };
	getWindowMessageHandler(WM_PAINT) = [this](WindowUI::WindowMessage& windowMessage) { onPaint(windowMessage); };
	getWindowMessageHandler(WM_COMMAND) = [this](WindowUI::WindowMessage& windowMessage) { onCommand(windowMessage); };
}

void MainFrame::initializeWindowClass(void)
{
	BasicWindow::initializeWindowClass();


	static std::wstring windowClassName = WindowUI::getWindowInstance()->loadString(IDC_MORDERNCPPWINDOW);


	getWindowClass().lpszClassName = windowClassName.c_str();
	getWindowClass().lpszMenuName  = WindowUI::getWindowInstance()->makeIntResource(IDC_MORDERNCPPWINDOW);
	getWindowClass().hIcon         = WindowUI::getWindowInstance()->loadIcon(IDI_MORDERNCPPWINDOW);
	getWindowClass().hIconSm       = WindowUI::getWindowInstance()->loadIcon(IDI_SMALL);
}

void MainFrame::onNcCreate(WindowUI::WindowMessage& windowMessage)
{
	WindowUI::WM_NCCREATE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	WindowUI::debugPrintln(L"MainFrame.onNcCreate()");
}

void MainFrame::onNcDestory(WindowUI::WindowMessage& windowMessage)
{
	WindowUI::debugPrintln(L"MainFrame.onNcDestory()");
}

void MainFrame::onCreate(WindowUI::WindowMessage& windowMessage)
{
	WindowUI::WM_CREATE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	WindowUI::debugPrintln(L"MainFrame.onCreate()");
}

void MainFrame::onDestory(WindowUI::WindowMessage& windowMessage)
{
	WindowUI::debugPrintln(L"MainFrame.onDestory() - begin");

	::PostQuitMessage(0);

	WindowUI::debugPrintln(L"MainFrame.onDestory() - end");
}

void MainFrame::onClose(WindowUI::WindowMessage& windowMessage)
{
	WindowUI::debugPrintln(L"MainFrame.onClose() - begin");

	destroyWindow();

	WindowUI::debugPrintln(L"MainFrame.onClose() - end");
}

void MainFrame::onSize(WindowUI::WindowMessage& windowMessage)
{
	WindowUI::WM_SIZE_WindowMessageManipulator windowMessageManipulator(&windowMessage);

	if (_View)
	{
		::MoveWindow(_View->getHandle(), 0, 0, windowMessageManipulator.size().cx, 100, FALSE);
	}
}

void MainFrame::onPaint(WindowUI::WindowMessage& windowMessage)
{
	PAINTSTRUCT ps;
	
	
	HDC hdc = BeginPaint(getHandle(), &ps);
	RECT rect{ 0,0, 500, 500 };

	DrawText(hdc, L"MainFrame", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	EndPaint(getHandle(), &ps);
}

void MainFrame::onCommand(WindowUI::WindowMessage& windowMessage)
{
	WindowUI::WM_COMMAND_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	switch (windowMessageManipulator.nID())
	{
	case IDM_ABOUT:
		onAbout(windowMessage);
		return;
		break;

	case IDM_EXIT:
		destroyWindow();
		return;
		break;

	default:
		break;
	}


	defaultWindowMessageHandler(windowMessage);
}

void MainFrame::onAbout(WindowUI::WindowMessage& windowMessage)
{
	AboutDialog dlg;


	dlg.doModal(getHandle());
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




