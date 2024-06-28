/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"
#include "../res/resource.h"

#include "../wui/WindowFunction.hpp"
#include "../wui/Core.hpp"
#include "../wui/WindowMessageManipulator.hpp"

#include "AboutDialog.hpp"
#include "View.hpp"
#include "MainFrame.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui_Example1
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
MainFrame::MainFrame()
{
	//-----------------------------------------------------------------------
	wui::debugPrintln(L"MainFrame.ctor() - begin");


	//-----------------------------------------------------------------------
	registerWindowMessageHandler();


	//-----------------------------------------------------------------------
	initializeWindowClass();
	registerWindowClass();


	//-----------------------------------------------------------------------
	static std::wstring windowText;
	HWND hwnd;


	windowText = wui::getWindowInstance()->loadString(IDS_APP_TITLE);
	hwnd = createWindow(nullptr, windowText.c_str());
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
	wui::debugPrintln(L"MainFrame.ctor() - end");
}

MainFrame::~MainFrame()
{
	//-----------------------------------------------------------------------
	wui::debugPrintln(L"MainFrame.dtor() - begin");


	//-----------------------------------------------------------------------


	//-----------------------------------------------------------------------
	wui::debugPrintln(L"MainFrame.dtor() - end");
}

void MainFrame::registerWindowMessageHandler(void)
{
	getWindowMessageHandler(WM_NCCREATE ) = [this](wui::WindowMessage& windowMessage) { onNcCreate(windowMessage); };
	getWindowMessageHandler(WM_NCDESTROY) = [this](wui::WindowMessage& windowMessage) { onNcDestory(windowMessage); };
	getWindowMessageHandler(WM_CREATE   ) = [this](wui::WindowMessage& windowMessage) { onCreate(windowMessage); };
	getWindowMessageHandler(WM_DESTROY  ) = [this](wui::WindowMessage& windowMessage) { onDestory(windowMessage); };
	getWindowMessageHandler(WM_CLOSE    ) = [this](wui::WindowMessage& windowMessage) { onClose(windowMessage); };
	getWindowMessageHandler(WM_SIZE     ) = [this](wui::WindowMessage& windowMessage) { onSize(windowMessage); };
	getWindowMessageHandler(WM_PAINT    ) = [this](wui::WindowMessage& windowMessage) { onPaint(windowMessage); };
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

void MainFrame::onNcCreate(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	wui::debugPrintln(L"MainFrame.onNcCreate() - begin");


	//-----------------------------------------------------------------------
	wui::WM_NCCREATE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	windowMessageManipulator.Result(TRUE);


	//-----------------------------------------------------------------------
	wui::debugPrintln(L"MainFrame.onNcCreate() - end");
}

void MainFrame::onNcDestory(wui::WindowMessage& windowMessage)
{
	wui::debugPrintln(L"MainFrame.onNcDestory()");
}

void MainFrame::onCreate(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	wui::debugPrintln(L"MainFrame.onCreate() - begin");


	//-----------------------------------------------------------------------
	wui::WM_CREATE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	//defaultWindowMessageHandler(windowMessage);
	windowMessageManipulator.Result(0);


	//-----------------------------------------------------------------------
	wui::debugPrintln(L"MainFrame.onCreate() - end");
}

void MainFrame::onDestory(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	wui::debugPrintln(L"MainFrame.onDestory() - begin");


	//-----------------------------------------------------------------------
	::PostQuitMessage(0);


	//-----------------------------------------------------------------------
	wui::debugPrintln(L"MainFrame.onDestory() - end");
}

void MainFrame::onClose(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	wui::debugPrintln(L"MainFrame.onClose() - begin");


	//-----------------------------------------------------------------------
	destroyWindow();


	//-----------------------------------------------------------------------
	wui::debugPrintln(L"MainFrame.onClose() - end");
}

void MainFrame::onSize(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	wui::WM_SIZE_WindowMessageManipulator windowMessageManipulator(&windowMessage);

	::MoveWindow(_View->getHandle(), 0, 0, windowMessageManipulator.size().cx, 100, FALSE);
}

void MainFrame::onPaint(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	wui::debugPrintln(L"MainFrame.onPaint() - begin");


	//-----------------------------------------------------------------------
	RECT rect;


	GetClientRect(getHandle(), &rect);


	PAINTSTRUCT ps;


	HDC hdc = BeginPaint(getHandle(), &ps);


	draw(hdc, rect);


	EndPaint(getHandle(), &ps);


	//-----------------------------------------------------------------------
	wui::debugPrintln(L"MainFrame.onPaint() - end");
}

void MainFrame::draw(HDC hdc, RECT& rect)
{
	HBRUSH hbr;


	hbr = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);


	FillRect(hdc, &rect, hbr);
	SetBkMode(hdc, TRANSPARENT);
	DrawText(hdc, L"MainFrame", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
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
		destroyWindow();
		return;
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





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




