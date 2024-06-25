/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"
#include "../res/resource.h"

#include "../WindowUI/WindowFunction.hpp"
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


	//-----------------------------------------------------------------------
	std::wstring windowText;
	HWND hwnd;


	windowText = WindowUI::getWindowInstance()->loadString(IDS_APP_TITLE);
	hwnd = createWindow(windowText.c_str());
	if (!hwnd)
	{
		throw std::wstring(L"MainFrame::MainFrame(): createWindow() failed");
	}


	//-----------------------------------------------------------------------
	RECT rect;

	
	rect.left = 0;
	rect.top = 0;
	rect.right = 500;
	rect.bottom = 100;
	_View = std::make_shared<View>(getHandle(), rect);


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
	getWindowMessageHandler(WM_NCCREATE ) = [this](WindowUI::WindowMessage& windowMessage) { onNcCreate(windowMessage); };
	getWindowMessageHandler(WM_NCDESTROY) = [this](WindowUI::WindowMessage& windowMessage) { onNcDestory(windowMessage); };
	getWindowMessageHandler(WM_CREATE   ) = [this](WindowUI::WindowMessage& windowMessage) { onCreate(windowMessage); };
	getWindowMessageHandler(WM_DESTROY  ) = [this](WindowUI::WindowMessage& windowMessage) { onDestory(windowMessage); };
	getWindowMessageHandler(WM_CLOSE    ) = [this](WindowUI::WindowMessage& windowMessage) { onClose(windowMessage); };
	getWindowMessageHandler(WM_SIZE     ) = [this](WindowUI::WindowMessage& windowMessage) { onSize(windowMessage); };
	getWindowMessageHandler(WM_PAINT    ) = [this](WindowUI::WindowMessage& windowMessage) { onPaint(windowMessage); };
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

void MainFrame::onNcCreate(WindowUI::WindowMessage& windowMessage)
{
	WindowUI::debugPrintln(L"MainFrame.onNcCreate() - begin");


	WindowUI::WM_NCCREATE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	// 둘 다 됨
#if 0
	defaultWindowMessageHandler(windowMessage);
#else
	windowMessageManipulator.Result(TRUE);
#endif


	WindowUI::debugPrintln(L"MainFrame.onNcCreate() - end");
}

void MainFrame::onNcDestory(WindowUI::WindowMessage& windowMessage)
{
	WindowUI::debugPrintln(L"MainFrame.onNcDestory()");
}

void MainFrame::onCreate(WindowUI::WindowMessage& windowMessage)
{
	WindowUI::debugPrintln(L"MainFrame.onCreate() - begin");


	WindowUI::WM_CREATE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	// 둘 다 됨
#if 0
	defaultWindowMessageHandler(windowMessage);
#else
	windowMessageManipulator.Result(0);
#endif


	WindowUI::debugPrintln(L"MainFrame.onCreate() - end");
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

	::MoveWindow(_View->getHandle(), 0, 0, windowMessageManipulator.size().cx, 100, FALSE);
}

void MainFrame::onPaint(WindowUI::WindowMessage& windowMessage)
{
	RECT rect;


	GetClientRect(getHandle(), &rect);


	PAINTSTRUCT ps;


	HDC hdc = BeginPaint(getHandle(), &ps);


	draw(hdc, rect);


	EndPaint(getHandle(), &ps);
}

void MainFrame::draw(HDC hdc, RECT& rect)
{
	HBRUSH hbr;


	hbr = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);


	FillRect(hdc, &rect, hbr);
	SetBkMode(hdc, TRANSPARENT);
	DrawText(hdc, L"MainFrame", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
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




