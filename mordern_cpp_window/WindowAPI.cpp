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
	return _Handle;
}

HINSTANCE WindowInstance::setHandle(HINSTANCE hInstance)
{
	HINSTANCE old;


	old = _Handle;
	_Handle = hInstance;

	return _Handle;
}

std::wstring WindowInstance::loadString(int id)
{
	LPWSTR ptr;
	LPWSTR* pptr;
	int rv;


	ptr = nullptr;
	pptr = &ptr;
	rv = ::LoadStringW(getHandle(),
		id,
		(LPWSTR)pptr,
		0
	);


	std::wstring s;


	if (rv)
	{
		if (ptr)
		{
			s = ptr;
		}
	}

	return s;
}

HCURSOR WindowInstance::loadCursor(int id)
{
	return loadCursor(makeIntResource(id));
}

HICON WindowInstance::loadIcon(int id)
{
	return loadIcon(makeIntResource(id));
}

HBITMAP WindowInstance::loadBitmap(int id)
{
	return loadBitmap(makeIntResource(id));
}

HCURSOR WindowInstance::loadCursor(LPCWSTR id)
{
	return ::LoadCursorW(getHandle(), id);
}

HICON WindowInstance::loadIcon(LPCWSTR id)
{
	return ::LoadIcon(getHandle(), id);
}

HBITMAP WindowInstance::loadBitmap(LPCWSTR id)
{
	return ::LoadBitmapW(getHandle(), id);
}

LPCWSTR WindowInstance::makeIntResource(int id)
{
	return MAKEINTRESOURCE(id);
}

//===========================================================================
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
	//-----------------------------------------------------------------------
	registerWindowMessageHandler();


	//-----------------------------------------------------------------------
	initializeWindowClass();
	registerWindowClass();
	createWindow();


	//-----------------------------------------------------------------------
	// child window


	//-----------------------------------------------------------------------
	::ShowWindow(_Handle, SW_SHOW);
	::UpdateWindow(_Handle);
	*/
}

Window::~Window()
{

}

void Window::registerWindowMessageHandler(void)
{
}

void Window::initializeWindowClass(void)
{
	memset(&_WindowClass, 0, sizeof(_WindowClass));

	_WindowClass.cbSize = sizeof(_WindowClass);
	_WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	_WindowClass.cbClsExtra = 0;
	_WindowClass.cbWndExtra = 0;
	_WindowClass.hInstance = getWindowInstance()->getHandle();
	_WindowClass.lpfnWndProc = WindowProc;
	_WindowClass.lpszClassName = L"TheWindowClass";
	_WindowClass.lpszMenuName = nullptr;
	_WindowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	_WindowClass.hCursor = getWindowInstance()->loadCursor(IDC_ARROW);
	_WindowClass.hIcon = nullptr;
	_WindowClass.hIconSm = nullptr;
}

void Window::registerWindowClass(void)
{
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

HWND Window::createWindow(
	DWORD dwExStyle,
	LPCWSTR lpWindowName,
	DWORD dwStyle,
	int X,
	int Y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu
)
{
	_Handle = CreateWindowExW(
		dwExStyle,
		_WindowClass.lpszClassName,
		lpWindowName,
		dwStyle,
		X,
		Y,
		nWidth,
		nHeight,
		hWndParent,
		hMenu,
		_WindowClass.hInstance,
		this
	);

	return _Handle;
}

void Window::destroyWindow(void)
{
	if (_Handle)
	{
		DestroyWindow(_Handle);
	}

	_Handle = nullptr;
}

WNDPROC Window::attachWindow(HWND hwnd)
{
	//-----------------------------------------------------------------------
	HWND old;


	old = _Handle;


	//-----------------------------------------------------------------------
	_Handle = hwnd;



	//-----------------------------------------------------------------------
	LONG_PTR rv;
	WNDPROC oldWindowProc;


	rv = ::SetWindowLongPtrW(_Handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	rv = ::SetWindowLongPtrW(_Handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProc));
	oldWindowProc = reinterpret_cast<WNDPROC>(rv);


	//-----------------------------------------------------------------------
	_ChainWindowProc = oldWindowProc;


	//-----------------------------------------------------------------------

	return oldWindowProc;
}

WNDPROC Window::detachWindow(WNDPROC windowProc)
{
	//-----------------------------------------------------------------------
	HWND old;


	old = _Handle;


	//-----------------------------------------------------------------------
	if (nullptr== windowProc)
	{
		windowProc = _ChainWindowProc;
	}


	//-----------------------------------------------------------------------
	LONG_PTR rv;
	WNDPROC oldWindowProc;


	rv = ::SetWindowLongPtrW(_Handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
	rv = ::SetWindowLongPtrW(_Handle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(windowProc));
	oldWindowProc = reinterpret_cast<WNDPROC>(rv);


	//-----------------------------------------------------------------------
	_Handle = nullptr;
	_ChainWindowProc = nullptr;


	return oldWindowProc;
}

void Window::callDefWindowProc(WindowMessage& windowMessage)
{
	windowMessage.lResult =
		::DefWindowProcW(
			windowMessage.hWnd,
			windowMessage.uMsg,
			windowMessage.wParam,
			windowMessage.lParam);
}

void Window::callChainWindowProc(WindowMessage& windowMessage, WNDPROC windowProc)
{
	//-----------------------------------------------------------------------
	if (nullptr == windowProc)
	{
		windowProc = _ChainWindowProc;
	}


	//-----------------------------------------------------------------------
	windowMessage.lResult =
		::CallWindowProcW(
			windowProc,
			windowMessage.hWnd,
			windowMessage.uMsg,
			windowMessage.wParam,
			windowMessage.lParam);
}

void Window::callWindowProc(WindowMessage& windowMessage)
{
	if (_ChainWindowProc)
	{
		callChainWindowProc(windowMessage, _ChainWindowProc);
	}
	else
	{
		callDefWindowProc(windowMessage);
	}
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


	callWindowProc(windowMessage);
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




