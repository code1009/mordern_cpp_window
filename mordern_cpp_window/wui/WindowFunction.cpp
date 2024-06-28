/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"

#include "WindowFunction.hpp"
#include "Core.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
std::wstring getWindowText(const Window* window)
{
	std::wstring s;


	int length;


	length = GetWindowTextLengthW(window->getHandle());


	if (length > 0)
	{
		s.resize(length + 1, 0);

		GetWindowTextW(window->getHandle(), s.data(), length + 1);
	}


	return s;
}

void setWindowText(const Window* window, const std::wstring& s)
{
	SetWindowText(window->getHandle(), s.c_str());
}

void moveWindow(const Window* window, const RECT& rect, bool repaint)
{
	::MoveWindow(window->getHandle(),
		rect.left, rect.top, 
		rect.right - rect.left,
		rect.bottom - rect.top,
		repaint ? TRUE : FALSE);
}

void moveWindow(const HWND hwnd, const RECT& rect, bool repaint)
{
	::MoveWindow(hwnd,
		rect.left, rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		repaint ? TRUE : FALSE);
}

void sendMessage(const Window* window, WindowMessage& windowMessage)
{
	windowMessage.lResult = 
		::SendMessageW(
			window->getHandle(), 
			windowMessage.uMsg, 
			windowMessage.wParam, 
			windowMessage.lParam
		);
}



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




