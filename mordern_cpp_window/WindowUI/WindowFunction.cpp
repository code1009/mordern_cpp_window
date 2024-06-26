/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"

#include "WindowFunction.hpp"
#include "Core.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
std::wstring getWindowText(const Window* w)
{
	std::wstring s;


	int length;


	length = GetWindowTextLengthW(w->getHandle());


	if (length > 0)
	{
		s.resize(length + 1, 0);

		GetWindowTextW(w->getHandle(), s.data(), length + 1);
	}


	return s;
}

void setWindowText(const Window* w, const std::wstring& s)
{
	SetWindowText(w->getHandle(), s.c_str());
}

void moveWindow(const Window* w, const RECT& rect, bool repaint)
{
	::MoveWindow(w->getHandle(),
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



/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




