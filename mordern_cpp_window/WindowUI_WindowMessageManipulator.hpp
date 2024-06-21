#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#if 0
// atlcrack.h

int OnCreate(LPCREATESTRUCT lpCreateStruct)
WM_CREATE
lResult = (LRESULT)func((LPCREATESTRUCT)lParam);

BOOL OnInitDialog(CWindow wndFocus, LPARAM lInitParam)
WM_INITDIALOG
lResult = (LRESULT)func((HWND)wParam, lParam);

BOOL OnCopyData(CWindow wnd, PCOPYDATASTRUCT pCopyDataStruct)
WM_COPYDATA
lResult = (LRESULT)func((HWND)wParam, (PCOPYDATASTRUCT)lParam);

void OnDestroy()
WM_DESTROY
func();
lResult = 0;

void OnMove(CPoint ptPos)
WM_MOVE
func(_WTYPES_NS::CPoint(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
lResult = 0;

#endif

#if 0
class WindowMessageProcess_WM_CREATE
{
public:
	using Handler = std::function<int(LPCREATESTRUCT lpCreateStruct)>;

public:
	int _Return;
	Handler _Function;

public:
	void invoke(WindowMessage* _windowMessage)
	{
		_Return = _Function(
			(LPCREATESTRUCT)_windowMessage->lParam
		);
		_windowMessage->lResult = (LRESULT)_Return;
	}
};

// void OnCommand(UINT uNotifyCode, int nID, CWindow wndCtl)
// func((UINT)HIWORD(wParam), (int)LOWORD(wParam), (HWND)lParam);
class WindowMessage_WM_COMMAND : public WindowMessage
{
public:
	UINT uNotifyCode(void) const { return (UINT)HIWORD(wParam); }
	int  nID(void) const { return (int)LOWORD(wParam); }
	HWND wndCtl(void) const { return (HWND)lParam; }
	void Return(void)
	{
		lResult = 0;
	}
};

class WindowMessage_WM_CREATE : public WindowMessage
{
public:
	LPCREATESTRUCT lpCreateStruct(void) const { return (LPCREATESTRUCT)lParam; }
	void Return(int rv)
	{
		lResult = (LRESULT)rv;
	}
};
#endif

// BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct)
// WM_NCCREATE
// lResult = (LRESULT)func((LPCREATESTRUCT)lParam);

// void OnNcDestroy()
// WM_NCDESTROY
// func(); lResult = 0;

/////////////////////////////////////////////////////////////////////////////
//===========================================================================
/*
int OnCreate(LPCREATESTRUCT lpCreateStruct)
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
/*
// BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct)
// WM_NCCREATE
// lResult = (LRESULT)func((LPCREATESTRUCT)lParam);
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

//using WM_NCCREATE_WindowMessageManipulator = WM_CREATE_WindowMessageManipulator;

