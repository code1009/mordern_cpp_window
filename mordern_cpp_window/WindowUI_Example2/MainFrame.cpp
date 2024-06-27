/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"
#include "../res/resource.h"

#include <atlbase.h>
#include <atlhost.h>

#include <winternl.h>

#include "../WindowUI/WindowFunction.hpp"
#include "../WindowUI/Core.hpp"
#include "../WindowUI/WindowMessageManipulator.hpp"

#include "AboutDialog.hpp"
#include "WebBrowserView.hpp"
#include "MainFrame.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Example2
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


	windowText = WindowUI::getWindowInstance()->loadString(IDS_APP_TITLE);
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


	view = std::make_shared<WebBrowserView>(getHandle(), rect);
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
	getWindowMessageHandler(WM_CREATE   ) = [this](WindowUI::WindowMessage& windowMessage) { onCreate(windowMessage); };
	getWindowMessageHandler(WM_DESTROY  ) = [this](WindowUI::WindowMessage& windowMessage) { onDestory(windowMessage); };
	getWindowMessageHandler(WM_CLOSE    ) = [this](WindowUI::WindowMessage& windowMessage) { onClose(windowMessage); };
	getWindowMessageHandler(WM_SIZE     ) = [this](WindowUI::WindowMessage& windowMessage) { onSize(windowMessage); };
	getWindowMessageHandler(WM_COMMAND  ) = [this](WindowUI::WindowMessage& windowMessage) { onCommand(windowMessage); };
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

void MainFrame::onCreate(WindowUI::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	WindowUI::WM_CREATE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	windowMessageManipulator.Result(0);
}

void MainFrame::onDestory(WindowUI::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	::PostQuitMessage(0);
}

void MainFrame::onClose(WindowUI::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	destroyWindow();
}

void MainFrame::onSize(WindowUI::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	WindowUI::WM_SIZE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	//-----------------------------------------------------------------------
	RECT rect;


	GetClientRect(getHandle(), &rect);
	WindowUI::moveWindow(_View.get(), rect);
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

void MainFrame::onAbout(WindowUI::WindowMessage& windowMessage)
{
	AboutDialog dlg;


	dlg.doModal(getHandle());
}

void MainFrame::onExit(WindowUI::WindowMessage& windowMessage)
{
	destroyWindow();
}

void MainFrame::onTest1(WindowUI::WindowMessage& windowMessage)
{
	sendMessage(_View.get(), windowMessage);
}

void MainFrame::onTest2(WindowUI::WindowMessage& windowMessage)
{
	sendMessage(_View.get(), windowMessage);
}


/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




