/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"
#include "../res/resource.h"

#include "../WindowUI/WindowFunction.hpp"
#include "../WindowUI/Core.hpp"
#include "../WindowUI/WindowMessageManipulator.hpp"

#include "View.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Example2
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
View::View(
	HWND hParent,
	const RECT& rect,
	std::uint32_t style,
	std::uint32_t styleEx
)
{
	//-----------------------------------------------------------------------
	WindowUI::debugPrintln(L"View.ctor() - begin");


	//-----------------------------------------------------------------------
	registerWindowMessageHandler();


	//-----------------------------------------------------------------------
	initializeWindowClass();
	registerWindowClass();


	//-----------------------------------------------------------------------
	std::wstring windowText;
	HWND hwnd;


	windowText = L"View";
	hwnd = createWindow(
		hParent,
		windowText.c_str(),
		static_cast<DWORD>(style),
		static_cast<DWORD>(styleEx),
		rect.left, rect.top, rect.right, rect.bottom
	);
	if (!hwnd)
	{
		throw std::wstring(L"View::View(): createWindow() failed");
	}


	//-----------------------------------------------------------------------
	::ShowWindow(getHandle(), SW_SHOW);
	::UpdateWindow(getHandle());


	//-----------------------------------------------------------------------
	std::wstring text;


	text = getWindowText(this);
	text = L"View Window";
	setWindowText(this, text);
	text = getWindowText(this);
	WindowUI::debugPrintln(text);


	//-----------------------------------------------------------------------
	WindowUI::debugPrintln(L"View.ctor() - end");
}

View::~View()
{
	WindowUI::debugPrintln(L"View.dtor() - begin");
	WindowUI::debugPrintln(L"View.dtor() - end");
}

void View::registerWindowMessageHandler(void)
{
	getWindowMessageHandler(WM_CREATE) = [this](WindowUI::WindowMessage& windowMessage) { onCreate(windowMessage); };
	getWindowMessageHandler(WM_DESTROY) = [this](WindowUI::WindowMessage& windowMessage) { onDestory(windowMessage); };
	getWindowMessageHandler(WM_CLOSE) = [this](WindowUI::WindowMessage& windowMessage) { onClose(windowMessage); };
	getWindowMessageHandler(WM_PAINT) = [this](WindowUI::WindowMessage& windowMessage) { onPaint(windowMessage); };
}

void View::onCreate(WindowUI::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	WindowUI::debugPrintln(L"View.onCreate() - begin");


	//-----------------------------------------------------------------------
	//SetWindowTextW(windowMessage.hWnd, L"View");

	defaultWindowMessageHandler(windowMessage);


	//-----------------------------------------------------------------------
	WindowUI::debugPrintln(L"View.onCreate() - end");
}

void View::onDestory(WindowUI::WindowMessage& windowMessage)
{
	WindowUI::debugPrintln(L"View.onDestory()");
}

void View::onClose(WindowUI::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	WindowUI::debugPrintln(L"View.onClose() - begin");


	//-----------------------------------------------------------------------
	WindowUI::debugPrintln(L"View.onClose() - end");
}

void View::onPaint(WindowUI::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	WindowUI::debugPrintln(L"View.onPaint() - begin");


	//-----------------------------------------------------------------------
	RECT rect;


	GetClientRect(getHandle(), &rect);


	PAINTSTRUCT ps;


	HDC hdc = BeginPaint(getHandle(), &ps);


	draw(hdc, rect);


	EndPaint(getHandle(), &ps);


	//-----------------------------------------------------------------------
	WindowUI::debugPrintln(L"View.onPaint() - end");
}

void View::draw(HDC hdc, RECT& rect)
{
	HBRUSH hbr;


	hbr = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);


	FillRect(hdc, &rect, hbr);
	SetBkMode(hdc, TRANSPARENT);
	DrawText(hdc, L"View", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




