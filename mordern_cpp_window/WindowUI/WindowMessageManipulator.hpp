#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include <windowsx.h>





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WindowMessageManipulator
{
private:
	WindowMessage* _windowMessage{ nullptr };

public:
	explicit WindowMessageManipulator(WindowMessage* windowMessage);
	virtual ~WindowMessageManipulator();

public:
	WindowMessageManipulator(const WindowMessageManipulator&) = delete;
	WindowMessageLoop& operator=(const WindowMessageManipulator&) = delete;

	WindowMessageManipulator(WindowMessageManipulator&&) = delete;
	WindowMessageManipulator& operator=(WindowMessageManipulator&&) = delete;

public:
	WindowMessage* getWindowMessage(void);
};





/////////////////////////////////////////////////////////////////////////////
//
// https://github.com/Win32-WTL/WTL/blob/main/Include/atlcrack.h
// 
/////////////////////////////////////////////////////////////////////////////
//===========================================================================





/////////////////////////////////////////////////////////////////////////////
/// 
// Standard Windows message macros
// 
/////////////////////////////////////////////////////////////////////////////
//===========================================================================
//int OnCreate(LPCREATESTRUCT lpCreateStruct)
/*
WM_CREATE
		lResult = (LRESULT)func((LPCREATESTRUCT)lParam);
*/
class WM_CREATE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_CREATE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	LPCREATESTRUCT lpCreateStruct(void) 
	{ 
		LPARAM lParam;


		lParam = getWindowMessage()->lParam;
		return (LPCREATESTRUCT)(lParam); 
	}

public:
	void Result(int rv)
	{
		getWindowMessage()->lResult = (LRESULT)rv;
	}	
};

//===========================================================================
// BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
/*
WM_INITDIALOG
		lResult = (LRESULT)func((HWND)wParam, lParam);
*/
class WM_INITDIALOG_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_INITDIALOG_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	HWND wndFocus(void) { return (HWND)getWindowMessage()->wParam; }
	LPARAM lInitParam(void) { return getWindowMessage()->lParam; }

public:
	void Result(bool rv)
	{
		getWindowMessage()->lResult = (LRESULT) rv ? 1 : 0;
	}
};

//===========================================================================
// BOOL OnCopyData(CWindow wnd, PCOPYDATASTRUCT pCopyDataStruct)
/*
WM_COPYDATA
		lResult = (LRESULT)func((HWND)wParam, (PCOPYDATASTRUCT)lParam);
*/
class WM_COPYDATA_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_COPYDATA_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	HWND wnd(void) { return (HWND)getWindowMessage()->wParam; }
	PCOPYDATASTRUCT pCopyDataStruct(void) { return (PCOPYDATASTRUCT)getWindowMessage()->lParam; }

public:
	void Result(bool rv)
	{
		getWindowMessage()->lResult = (LRESULT)rv ? 1 : 0;
	}
};

//===========================================================================
//void OnDestroy()
/*
WM_DESTROY
	func(); \
	lResult = 0; \
*/
class WM_DESTROY_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_DESTROY_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnMove(CPoint ptPos)
/*
WM_MOVE
		func(_WTYPES_NS::CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))); \
		lResult = 0; \
*/
class WM_MOVE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_MOVE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

	POINT point(void)
	{
		POINT pt{ GET_X_LPARAM(getWindowMessage()->lParam), GET_Y_LPARAM(getWindowMessage()->lParam) };

		return pt;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct)
/*
WM_NCCREATE
		lResult = (LRESULT)func((LPCREATESTRUCT)lParam);
*/
class WM_NCCREATE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_NCCREATE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	LPCREATESTRUCT lpCreateStruct(void)
	{
		LPARAM lParam;


		lParam = getWindowMessage()->lParam;
		return (LPCREATESTRUCT)(lParam);
	}

public:
	void Result(bool rv)
	{
		getWindowMessage()->lResult = (LRESULT) rv ? 1 : 0;
	}
};

//===========================================================================
// void OnNcDestroy()
/*
WM_NCDESTROY
		func(); \
		lResult = 0; \
*/
using WM_NCDESTROY_WindowMessageManipulator = WM_DESTROY_WindowMessageManipulator;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}






