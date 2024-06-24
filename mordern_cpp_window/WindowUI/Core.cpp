﻿/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"

#include "Core.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void debugPrintln(const std::wstring& message)
{
	OutputDebugStringW(message.c_str());
	OutputDebugStringW(L"\r\n");
}

void reportError(const std::wstring& message)
{
	//-----------------------------------------------------------------------
	DWORD dwLastErrorCode;
	DWORD dwSystemLocale;
	DWORD dwFlags;
	HLOCAL hLocal;
	DWORD dwLength;


	dwLastErrorCode = GetLastError();
	dwSystemLocale = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);
	dwFlags = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
	hLocal = NULL;
	dwLength = FormatMessageW(dwFlags, NULL, dwLastErrorCode, dwSystemLocale, (LPWSTR)&hLocal, 0, NULL);


	//-----------------------------------------------------------------------
	if (!dwLength)
	{
		ExitProcess(dwLastErrorCode);
		return;
	}


	//-----------------------------------------------------------------------
	std::wstring errorString = ((const WCHAR*)hLocal);


	//-----------------------------------------------------------------------
	WCHAR* errorMessageString;
	std::size_t errorMessageStringLength;


	errorMessageStringLength = message.size() + errorString.size() + 40;
	errorMessageString = new WCHAR[errorMessageStringLength];

	StringCchPrintfW(errorMessageString,
		errorMessageStringLength,
		L"%s failed with error %d: %s",
		message.c_str(),
		dwLastErrorCode,
		errorString.c_str()
	);
	debugPrintln(errorMessageString);
	MessageBoxW(NULL, errorMessageString, L"Error", MB_ICONEXCLAMATION|MB_OK);

	delete[] errorMessageString;
	

	//-----------------------------------------------------------------------
	LocalFree(hLocal);


	//-----------------------------------------------------------------------
	ExitProcess(dwLastErrorCode);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WindowInstance::WindowInstance():
	_Handle{ nullptr }
{
}

HINSTANCE WindowInstance::getHandle(void)
{
	return _Handle;
}

HINSTANCE WindowInstance::setHandle(HINSTANCE handle)
{
	HINSTANCE old;


	old = _Handle;
	_Handle = handle;

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

WindowMessage::WindowMessage(const WindowMessage& other):
	hWnd   {other.hWnd   }, 
	uMsg   {other.uMsg   }, 
	wParam {other.wParam }, 
	lParam {other.lParam }, 
	lResult{other.lResult}
{
}

WindowMessage& WindowMessage::operator=(const WindowMessage& other)
{
	if (this != &other)
	{
		hWnd    = other.hWnd;
		uMsg    = other.uMsg;
		wParam  = other.wParam;
		lParam  = other.lParam;
		lResult = other.lResult;
	}

	return *this;
}

WindowMessage::WindowMessage(WindowMessage&& other) noexcept : 
	hWnd   {std::move(other.hWnd   )},
	uMsg   {std::move(other.uMsg   )}, 
	wParam {std::move(other.wParam )}, 
	lParam {std::move(other.lParam )}, 
	lResult{std::move(other.lResult)}
{
	other.hWnd = nullptr;
	other.uMsg = 0;
	other.wParam = 0;
	other.lParam = 0;
	other.lResult = 0;
}

WindowMessage& WindowMessage::operator=(WindowMessage&& other) noexcept
{
	if (this != &other)
	{
		hWnd    = std::move(other.hWnd   );
		uMsg    = std::move(other.uMsg   );
		wParam  = std::move(other.wParam );
		lParam  = std::move(other.lParam );
		lResult = std::move(other.lResult);

		other.hWnd    = nullptr;
		other.uMsg    = 0;
		other.wParam  = 0;
		other.lParam  = 0;
		other.lResult = 0;
	}


	return *this;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LRESULT __stdcall WindowProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam);
INT_PTR __stdcall DialogProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam);





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
Window::Window()
{
}

Window::~Window()
{
}

HWND Window::getHandle(void)
{
	return _Handle;
}

HWND Window::setHandle(HWND handle)
{
	HWND old;


	old = _Handle;
	_Handle = handle;

	return _Handle;
}

WindowMessageHandler& Window::getWindowMessageHandler(std::uint32_t umsg)
{
	return _WindowMessageHandlerMap[umsg];
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

void Window::defaultWindowMessageHandler(WindowMessage& windowMessage)
{
	callDefWindowProc(windowMessage);
}

void Window::onWindowMessage(WindowMessage& windowMessage)
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


	defaultWindowMessageHandler(windowMessage);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
BasicWindow::BasicWindow()
{
}

BasicWindow::~BasicWindow()
{
}

WNDCLASSEXW& BasicWindow::getWindowClass(void)
{
	return _WindowClass;
}

void BasicWindow::initializeWindowClass(void)
{
	memset(&_WindowClass, 0, sizeof(_WindowClass));

	_WindowClass.cbSize = sizeof(_WindowClass);
	_WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	_WindowClass.cbClsExtra = 0;
	_WindowClass.cbWndExtra = 0;
	_WindowClass.hInstance = getWindowInstance()->getHandle();
	_WindowClass.lpfnWndProc = WindowProc;
	_WindowClass.lpszClassName = L"TheBaseWindowClass";
	_WindowClass.lpszMenuName = nullptr;
	_WindowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	_WindowClass.hCursor = getWindowInstance()->loadCursor(IDC_ARROW);
	_WindowClass.hIcon = nullptr;
	_WindowClass.hIconSm = nullptr;
}

void BasicWindow::registerWindowClass(void)
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

HWND BasicWindow::createWindow(
	LPCWSTR lpWindowName,
	DWORD dwStyle,
	DWORD dwExStyle,
	int X,
	int Y,
	int nWidth,
	int nHeight,
	HWND hWndParent,
	HMENU hMenu
)
{
	HWND handle;


	handle = CreateWindowExW(
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

	return handle;
}

void BasicWindow::destroyWindow(void)
{
	HWND handle;


	handle = getHandle();
	if (handle)
	{
		DestroyWindow(handle);
	}

	setHandle(nullptr);
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
SubclassWindow::SubclassWindow()
{
}

SubclassWindow::~SubclassWindow()
{
}

WNDPROC SubclassWindow::subclassWindow(HWND hwnd)
{
	//-----------------------------------------------------------------------
	setHandle(hwnd);


	//-----------------------------------------------------------------------
	LONG_PTR rv;
	WNDPROC oldWindowProc;


	rv = ::SetWindowLongPtrW(getHandle(), GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	rv = ::SetWindowLongPtrW(getHandle(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProc));
	oldWindowProc = reinterpret_cast<WNDPROC>(rv);


	//-----------------------------------------------------------------------
	_ChainWindowProc = oldWindowProc;


	//-----------------------------------------------------------------------

	return oldWindowProc;
}

WNDPROC SubclassWindow::unsubclassWindow(WNDPROC windowProc)
{
	//-----------------------------------------------------------------------
	if (nullptr== windowProc)
	{
		windowProc = _ChainWindowProc;
	}


	//-----------------------------------------------------------------------
	LONG_PTR rv;
	WNDPROC oldWindowProc;


	rv = ::SetWindowLongPtrW(getHandle(), GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
	rv = ::SetWindowLongPtrW(getHandle(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(windowProc));
	oldWindowProc = reinterpret_cast<WNDPROC>(rv);


	//-----------------------------------------------------------------------
	setHandle(nullptr);
	_ChainWindowProc = nullptr;


	return oldWindowProc;
}

void SubclassWindow::callWindowProc(WindowMessage& windowMessage, WNDPROC windowProc)
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

WNDPROC SubclassWindow::getChainWindowProc(void)
{
	return _ChainWindowProc;
}

void SubclassWindow::defaultWindowMessageHandler(WindowMessage& windowMessage)
{
	if (_ChainWindowProc)
	{
		callWindowProc(windowMessage, _ChainWindowProc);
	}
	else
	{
		callDefWindowProc(windowMessage);
	}
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
BaseDialog::BaseDialog(std::int32_t templateNameId):
	_TemplateNameId{ templateNameId }
{
}

BaseDialog::~BaseDialog()
{
}

std::int32_t BaseDialog::getTemplateNameId(void)
{
	return _TemplateNameId;
}

int BaseDialog::doModal(HWND hwndParent)
{
	DialogBoxParamW(
		getWindowInstance()->getHandle(),
		getWindowInstance()->makeIntResource(getTemplateNameId()),
		hwndParent,
		DialogProc, 
		reinterpret_cast<LPARAM>(this)
	);

	return 0;
}

int BaseDialog::createDialog(HWND hwndParent)
{
	CreateDialogParamW(
		getWindowInstance()->getHandle(), 
		getWindowInstance()->makeIntResource(getTemplateNameId()),
		hwndParent,
		DialogProc, 
		reinterpret_cast<LPARAM>(this)
	);


	return 0;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WindowMessageLoop::WindowMessageLoop()
{
}

WindowMessageLoop::~WindowMessageLoop()
{
}

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




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
LRESULT __stdcall WindowProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	if (WM_NCCREATE == message)
	{
		auto userData = reinterpret_cast<CREATESTRUCTW*>(lParam)->lpCreateParams;
		::SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(userData));

		(reinterpret_cast<Window*>(userData))->setHandle(hwnd);
	}


	auto windowPtr = reinterpret_cast<Window*>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA));
	if (windowPtr)
	{
		WindowMessage windowMessage{ hwnd, message, wParam, lParam };


		windowPtr->onWindowMessage(windowMessage);


		if (WM_NCDESTROY == message)
		{
			::SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
			windowPtr->setHandle(nullptr);
		}


		return windowMessage.lResult;
	}


	return ::DefWindowProcW(hwnd, message, wParam, lParam);
}

//===========================================================================
INT_PTR __stdcall DialogProc(HWND hwnd, uint32_t message, WPARAM wParam, LPARAM lParam)
{
	if (WM_INITDIALOG == message)
	{
		auto userData = reinterpret_cast<BaseDialog*>(lParam);
		::SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(userData));

		(reinterpret_cast<BaseDialog*>(userData))->setHandle(hwnd);
	}


	auto dialogPtr = reinterpret_cast<BaseDialog*>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA));
	if (dialogPtr)
	{
		WindowMessage windowMessage{ hwnd, message, wParam, lParam };


		dialogPtr->onWindowMessage(windowMessage);


		if (WM_NCDESTROY == message)
		{
			::SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(nullptr));
			dialogPtr->setHandle(nullptr);
		}


		return windowMessage.lResult;
	}


	return ::DefWindowProcW(hwnd, message, wParam, lParam);
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




