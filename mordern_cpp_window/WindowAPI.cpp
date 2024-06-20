/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "framework.h"

#include "WindowAPI.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void print(const std::string& message)
{
	//OutputDebugStringA("//===========================================================================\r\n");
	OutputDebugStringA(message.c_str());
	OutputDebugStringA("\r\n");
	//OutputDebugStringA("//===========================================================================\r\n");
}

void reportError(LPCTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code

	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);

	// Display the error message and exit the process

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
		(lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf,
		LocalSize(lpDisplayBuf) / sizeof(TCHAR),
		TEXT("%s failed with error %d: %s"),
		lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
HINSTANCE WindowInstance::getHandle(void)
{
	return _hInstance;
}

HINSTANCE WindowInstance::setHandle(HINSTANCE hInstance)
{
	HINSTANCE old;


	old = _hInstance;
	_hInstance = hInstance;

	return _hInstance;
}

WindowInstance* getWindowInstance(void)
{
	static WindowInstance instance;

	return &instance;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WindowMessage::WindowMessage(
	HWND      hwnd,
	uint32_t  umsg,
	WPARAM    wparam,
	LPARAM    lparam
) :
	hWnd{ hwnd },
	uMsg{ umsg },
	wParam{ wparam },
	lParam{ lparam },
	lResult{ 0 }
{
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LRESULT __stdcall WindowProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
Window::Window()
{
	/*
	registerWindowMessageHandler();


	registerWindowClass();
	createWindow();
	*/
}

Window::~Window()
{

}

void Window::registerWindowMessageHandler(void)
{
}

void Window::registerWindowClass(void)
{
	memset(&_WindowClass, 0, sizeof(_WindowClass));

	_WindowClass.cbSize = sizeof(_WindowClass);
	_WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	_WindowClass.hInstance = getWindowInstance()->getHandle();
	_WindowClass.lpfnWndProc = WindowProc;
	_WindowClass.lpszClassName = L"TheWindowClass";
	_WindowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	_WindowClass.hCursor = ::LoadCursorW(nullptr, IDC_ARROW);


	WNDCLASSEXW wndClass;
	BOOL rv;


	rv = GetClassInfoExW(_WindowClass.hInstance, _WindowClass.lpszClassName, &wndClass);
	if (FALSE == rv)
	{
		ATOM atom = RegisterClassExW(&_WindowClass);
		if (!atom)
		{
			reportError(L"registerWindowClass");
		}
	}
}

void Window::createWindow(void)
{
	DWORD   dwExStyle = 0;
	LPCWSTR lpWindowName = L"Here is the title of the Window, will only show on the taskbar.";
	DWORD   dwStyle = WS_POPUP | WS_CAPTION | WS_BORDER | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX;
	int     X = CW_USEDEFAULT;
	int     Y = CW_USEDEFAULT;
	int     nWidth = 500;
	int     nHeight = 500;
	HWND    hWndParent = nullptr;
	HMENU   hMenu = nullptr;


	_hWnd = CreateWindowExW(
		dwExStyle,
		_WindowClass.lpszClassName,
		lpWindowName,
		dwStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nWidth,
		nHeight,
		hWndParent,
		hMenu,
		_WindowClass.hInstance,
		this
	);
}

void Window::destroyWindow(void)
{
	if (_hWnd)
	{
		DestroyWindow(_hWnd);
	}

	_hWnd = nullptr;
}

void Window::callDefaultWindowProc(WindowMessage& windowMessage)
{
	windowMessage.lResult =
		::DefWindowProcW(
			windowMessage.hWnd,
			windowMessage.uMsg,
			windowMessage.wParam,
			windowMessage.lParam);
}

void Window::onWindowProc(WindowMessage& windowMessage)
{
	auto found = _WindowMessageHandlerMap.find(windowMessage.uMsg);


	if (found != _WindowMessageHandlerMap.end())
	{
		auto handler = (*found).second;
		if (handler)
		{
			handler(windowMessage);
			return;
		}
	}


	callDefaultWindowProc(windowMessage);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LRESULT __stdcall WindowProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	if (WM_NCCREATE == message)
	{
		auto userData = reinterpret_cast<CREATESTRUCTW*>(lParam)->lpCreateParams;
		::SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(userData));
	}


	auto windowPtr = reinterpret_cast<Window*>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA));
	if (windowPtr)
	{
		WindowMessage windowMessage{ hwnd, message, wParam, lParam };


		windowPtr->onWindowProc(windowMessage);

		return windowMessage.lResult;
	}


	return ::DefWindowProcW(hwnd, message, wParam, lParam);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void WindowMessageLoop::runLoop(void)
{
	MSG msg;
	BOOL rv;


	do
	{
		rv = ::PeekMessageW(&msg, HWND{}, 0, 0, PM_REMOVE);
		if (rv != 0)
		{
			::TranslateMessage(&msg);
			::DispatchMessageW(&msg);
		}
	} while (msg.message != WM_QUIT);
}




