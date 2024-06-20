/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "framework.h"

#include "WindowAPI.hpp"
#include "MainWindow.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
MainWindow::MainWindow()
{
	print("MainWindow.ctor() - begin");

	registerWindowMessageHandler();

	registerWindowClass();
	createWindow();
	::ShowWindow(_hWnd, SW_SHOW);

	print("MainWindow.ctor() - end");
}

MainWindow::~MainWindow()
{
	print("MainWindow.dtor()");
}

void MainWindow::registerWindowMessageHandler(void)
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
}

void MainWindow::onCreate(void)
{
	print("MainWindow.onCreate()");
}

void MainWindow::onDestory(void)
{
	print("MainWindow.onDestory() - begin");

	::PostQuitMessage(0);

	print("MainWindow.onDestory() - end");
}

void MainWindow::onClose(void)
{
	print("MainWindow.onClose() - begin");

	destroyWindow();

	print("MainWindow.onClose() - end");
}
