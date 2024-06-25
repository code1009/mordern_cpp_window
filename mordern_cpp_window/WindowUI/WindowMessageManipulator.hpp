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
		return (LPCREATESTRUCT)(getWindowMessage()->lParam);
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
	HWND wndFocus(void)
	{ 
		return (HWND)getWindowMessage()->wParam; 
	}

	LPARAM lInitParam(void) 
	{ 
		return getWindowMessage()->lParam; 
	}

public:
	void Result(BOOL rv)
	{
		getWindowMessage()->lResult = (LRESULT) rv;
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
	HWND wnd(void) 
	{ 
		return (HWND)getWindowMessage()->wParam; 
	}

	PCOPYDATASTRUCT pCopyDataStruct(void) 
	{ 
		return (PCOPYDATASTRUCT)getWindowMessage()->lParam; 
	}

public:
	void Result(BOOL rv)
	{
		getWindowMessage()->lResult = (LRESULT)rv;
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

public:
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
// void OnSize(UINT nType, CSize size)
/*
WM_SIZE
		func((UINT)wParam, _WTYPES_NS::CSize(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam))); \
		lResult = 0; \
*/
class WM_SIZE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_SIZE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	UINT nTYPE(void)
	{
		return (UINT)getWindowMessage()->wParam;
	}

	SIZE size(void)
	{
		SIZE size{ GET_X_LPARAM(getWindowMessage()->lParam), GET_Y_LPARAM(getWindowMessage()->lParam) };

		return size;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnActivate(UINT nState, BOOL bMinimized, CWindow wndOther)
/*
WM_ACTIVATE
		func((UINT)LOWORD(wParam), (BOOL)HIWORD(wParam), (HWND)lParam); \
		lResult = 0; \
*/
class WM_ACTIVATE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_ACTIVATE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	UINT nState(void)
	{
		return (UINT)LOWORD(getWindowMessage()->wParam);
	}

	BOOL bMinimized(void)
	{
		return (BOOL)HIWORD(getWindowMessage()->wParam);
	}

	HWND wndOther(void)
	{
		return (HWND)getWindowMessage()->lParam;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnSetFocus(CWindow wndOld)
/*
WM_SETFOCUS
		func((HWND)wParam); \
		lResult = 0; \
*/
class WM_SETFOCUS_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_SETFOCUS_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	HWND wndOld(void)
	{
		return (HWND)getWindowMessage()->wParam;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnKillFocus(CWindow wndFocus)
/*
WM_KILLFOCUS
		func((HWND)wParam); \
		lResult = 0; \
*/
class WM_KILLFOCUS_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_KILLFOCUS_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	HWND wndFocus(void)
	{
		return (HWND)getWindowMessage()->wParam;
	}

public:
	void Result(void)
	{
		getWindowMessage()->lResult = (LRESULT)0;
	}
};

//===========================================================================
// void OnEnable(BOOL bEnable)
/*
WM_ENABLE
		func((BOOL)wParam); \
		lResult = 0; \
*/
class WM_ENABLE_WindowMessageManipulator : public WindowMessageManipulator
{
public:
	explicit WM_ENABLE_WindowMessageManipulator(WindowMessage* windowMessage) :
		WindowMessageManipulator(windowMessage)
	{
	}

public:
	BOOL bEnable(void)
	{
		return (BOOL)getWindowMessage()->wParam;
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
		return (LPCREATESTRUCT)(getWindowMessage()->lParam);
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






