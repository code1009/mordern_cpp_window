#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void print(const std::string& message);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WindowInstance
{
public:
	HINSTANCE _hInstance{ nullptr };

public:
	HINSTANCE getHandle(void);
	HINSTANCE setHandle(HINSTANCE hInstance);
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
	WNDCLASSEXW _WindowClass{ };

public:
	HWND                    _hWnd{ nullptr };
	WindowMessageHandlerMap _WindowMessageHandlerMap{ };

public:
	Window();
	virtual ~Window();

public:
	virtual void registerWindowMessageHandler(void);
	virtual void initializeWindowClass(void);
	virtual void registerWindowClass(void);
	virtual void createWindow(
		DWORD dwExStyle = 0,
		LPCWSTR lpWindowName = L"Window",
		DWORD dwStyle = WS_OVERLAPPEDWINDOW,
		int X = CW_USEDEFAULT,
		int Y = CW_USEDEFAULT,
		int nWidth = 500,
		int nHeight = 500,
		HWND hWndParent = nullptr,
		HMENU hMenu = nullptr);
	virtual void destroyWindow(void);
	virtual void callDefaultWindowProc(WindowMessage& windowMessage);
	virtual void onWindowProc(WindowMessage& windowMessage);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WindowMessageLoop
{
public:
	void runLoop(void);
};

