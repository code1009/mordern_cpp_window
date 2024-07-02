﻿/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"
#include "../res/resource.h"

#include <atlbase.h>
#include <atlhost.h>

#include <winternl.h>

#include "../wui/WindowFunction.hpp"
#include "../wui/Core.hpp"
#include "../wui/WindowMessageManipulator.hpp"

#include "AboutDialog.hpp"
#include "WebView.hpp"
#include "MainFrame.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui_Example3
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
MainFrame::MainFrame()
{
	//-----------------------------------------------------------------------
	registerWindowMessageHandler();


	//-----------------------------------------------------------------------
	initializeWindowClass();
	registerWindowClass();


	//-----------------------------------------------------------------------
	static std::wstring windowText;
	HWND hwnd;


	windowText = wui::getWindowInstance()->loadString(IDS_APP_TITLE);
	hwnd = createWindow(nullptr, windowText.c_str(), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	if (!hwnd)
	{
		throw std::wstring(L"MainFrame::MainFrame(): createWindow() failed");
	}


	//-----------------------------------------------------------------------
	RECT rect;

	
	GetClientRect(getHandle(), &rect);


	//-----------------------------------------------------------------------
	std::shared_ptr<Window> view;


	view = std::make_shared<WebView>(getHandle(), rect);
	_View = view;


	//-----------------------------------------------------------------------
	::ShowWindow(getHandle(), SW_SHOW);
	::UpdateWindow(getHandle());
}

MainFrame::~MainFrame()
{
}

void MainFrame::registerWindowMessageHandler(void)
{
	getWindowMessageHandler(WM_CREATE   ) = [this](wui::WindowMessage& windowMessage) { onCreate(windowMessage); };
	getWindowMessageHandler(WM_DESTROY  ) = [this](wui::WindowMessage& windowMessage) { onDestory(windowMessage); };
	getWindowMessageHandler(WM_CLOSE    ) = [this](wui::WindowMessage& windowMessage) { onClose(windowMessage); };
	getWindowMessageHandler(WM_SIZE     ) = [this](wui::WindowMessage& windowMessage) { onSize(windowMessage); };
	getWindowMessageHandler(WM_COMMAND  ) = [this](wui::WindowMessage& windowMessage) { onCommand(windowMessage); };
}

void MainFrame::initializeWindowClass(void)
{
	BasicWindow::initializeWindowClass();


	static std::wstring windowClassName = wui::getWindowInstance()->loadString(IDC_MORDERNCPPWINDOW);


	getWindowClass().lpszClassName = windowClassName.c_str();
	getWindowClass().lpszMenuName  = wui::getWindowInstance()->makeIntResource(IDC_MORDERNCPPWINDOW);
	getWindowClass().hIcon         = wui::getWindowInstance()->loadIcon(IDI_MORDERNCPPWINDOW);
	getWindowClass().hIconSm       = wui::getWindowInstance()->loadIcon(IDI_SMALL);
}

void MainFrame::onCreate(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	wui::WM_CREATE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	windowMessageManipulator.Result(0);
}

void MainFrame::onDestory(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	::PostQuitMessage(0);
}

void MainFrame::onClose(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	destroyWindow();
}

void MainFrame::onSize(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	wui::WM_SIZE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	//-----------------------------------------------------------------------
	RECT rect;


	GetClientRect(getHandle(), &rect);
	wui::moveWindow(_View.get(), rect);
}

void MainFrame::onCommand(wui::WindowMessage& windowMessage)
{
	wui::WM_COMMAND_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	switch (windowMessageManipulator.nID())
	{
	case IDM_ABOUT:
		onAbout(windowMessage);
		return;
		break;

	case IDM_EXIT:
		onExit(windowMessage);
		return;
		break;

	case IDM_TEST1:
		onTest1(windowMessage);
		break;

	case IDM_TEST2:
		onTest2(windowMessage);
		break;

	default:
		break;
	}


	defaultWindowMessageHandler(windowMessage);
}

void MainFrame::onAbout(wui::WindowMessage& windowMessage)
{
	AboutDialog dlg;


	dlg.doModal(getHandle());
}

void MainFrame::onExit(wui::WindowMessage& windowMessage)
{
	destroyWindow();
}

void MainFrame::onTest1(wui::WindowMessage& windowMessage)
{
	sendMessage(_View.get(), windowMessage);
}

void MainFrame::onTest2(wui::WindowMessage& windowMessage)
{
	sendMessage(_View.get(), windowMessage);
}


/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




