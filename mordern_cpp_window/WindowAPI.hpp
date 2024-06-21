#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void debugPrintln(const std::wstring& message);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WindowInstance
{
private:
	HINSTANCE _Handle{ nullptr };

public:
	HINSTANCE getHandle(void);
	HINSTANCE setHandle(HINSTANCE handle);

public:
	std::wstring loadString(int id);
	HCURSOR loadCursor(int id);
	HICON loadIcon(int id);
	HBITMAP loadBitmap(int id);
	HCURSOR loadCursor(LPCWSTR id);	
	HICON loadIcon(LPCWSTR id);
	HBITMAP loadBitmap(LPCWSTR id);
	LPCWSTR makeIntResource(int id);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WindowInstance* getWindowInstance(void);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WindowMessage
{
public:
	HWND     hWnd;
	uint32_t uMsg;
	WPARAM   wParam;
	LPARAM   lParam;
	LRESULT  lResult;

public:
	explicit WindowMessage(
		HWND          hwnd,
		std::uint32_t umsg,
		WPARAM        wparam,
		LPARAM        lparam
	);
};





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

class WindowMessageParam_WM_COMMAND
{
private:
	WindowMessage* _WindowMessage{ nullptr };

public:
	WindowMessageParam_WM_COMMAND(WindowMessage* windowMessage) :
		_WindowMessage(windowMessage)
	{
	}

public:
	UINT uNotifyCode(void) { return (UINT)HIWORD(_WindowMessage->wParam); }
	int  nID(void) { return (int)LOWORD(_WindowMessage->wParam); }
	HWND wndCtl(void) { return (HWND)_WindowMessage->lParam; }
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
using WindowMessageHandler = std::function<void(WindowMessage& windowMessage)>;
using WindowMessageHandlerMap = std::map<std::uint32_t, WindowMessageHandler>;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class Window
{
private:
	HWND _Handle{ nullptr };
	WindowMessageHandlerMap _WindowMessageHandlerMap{ };

public:
	Window();
	virtual ~Window();

public:
	virtual HWND getHandle(void);
	virtual HWND setHandle(HWND handle);

public:
	virtual WindowMessageHandler& getWindowMessageHandler(std::uint32_t umsg);
	virtual void registerWindowMessageHandler(void) = 0;

	// 윈도우 프로시저 안에서 호출
public:
	virtual void callDefWindowProc(WindowMessage& windowMessage);
	virtual void defaultWindowMessageHandler(WindowMessage& windowMessage);
	virtual void onWindowMessage(WindowMessage& windowMessage);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class BaseWindow : public Window
{
private:
	WNDCLASSEXW _WindowClass{ };

public:
	virtual WNDCLASSEXW& getWindowClass(void);
	virtual void initializeWindowClass(void);
	virtual void registerWindowClass(void);
	virtual HWND createWindow(
		LPCWSTR lpWindowName = L"Window",
		DWORD dwStyle = WS_OVERLAPPEDWINDOW,
		DWORD dwExStyle = 0,
		int X = CW_USEDEFAULT,
		int Y = CW_USEDEFAULT,
		int nWidth = 500,
		int nHeight = 500,
		HWND hWndParent = nullptr,
		HMENU hMenu = nullptr);
	virtual void destroyWindow(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class SubclassWindow : public Window
{
public:
	WNDPROC _ChainWindowProc{ nullptr };

public:
	virtual WNDPROC subclassWindow(HWND hwnd);
	virtual WNDPROC unsubclassWindow(WNDPROC windowProc = nullptr);

	// 윈도우 프로시저 안에서 호출
public:
	virtual void defaultWindowMessageHandler(WindowMessage& windowMessage) override;

public:
	virtual void callWindowProc(WindowMessage& windowMessage, WNDPROC windowProc = nullptr);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WindowMessageLoop
{
public:
	void runLoop(void);
};

