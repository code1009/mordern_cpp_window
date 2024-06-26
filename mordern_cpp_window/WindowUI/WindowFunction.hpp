#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class Window;
class WindowMessage;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
std::wstring getWindowText(const Window* window);
void         setWindowText(const Window* window, const std::wstring& s);

void moveWindow(const Window* window, const RECT& rect, bool repaint = false);
void moveWindow(const HWND hwnd, const RECT& rect, bool repaint = false);

void sendMessage(const Window* window, WindowMessage& windowMessage);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




