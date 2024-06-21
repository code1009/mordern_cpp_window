#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void print(const std::wstring& message);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WindowInstance
{
public:
	HINSTANCE _Handle{ nullptr };

public:
	HINSTANCE getHandle(void);
	HINSTANCE setHandle(HINSTANCE hInstance);

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
using WindowMessageHandler = std::function<void(WindowMessage& windowMessage)>;
using WindowMessageHandlerMap = std::map<std::uint32_t, WindowMessageHandler>;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class Window
{
public:
	HWND                    _Handle{ nullptr };
	WindowMessageHandlerMap _WindowMessageHandlerMap{ };

public:
	Window();
	virtual ~Window();

public:
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
public:
	WNDCLASSEXW _WindowClass{ };

public:
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

