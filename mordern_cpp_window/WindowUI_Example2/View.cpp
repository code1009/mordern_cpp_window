/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"
#include "../res/resource.h"

#include <atlbase.h>
#include <atlhost.h>

#include <winternl.h>

#include "../WindowUI/WindowFunction.hpp"
#include "../WindowUI/Core.hpp"
#include "../WindowUI/WindowMessageManipulator.hpp"

#include "View.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Example2
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
View::View(
	HWND hParent,
	const RECT& rect,
	std::uint32_t style,
	std::uint32_t styleEx
)
{
	//-----------------------------------------------------------------------
	registerWindowMessageHandler();


	//-----------------------------------------------------------------------
	initializeWindowClass();
	registerWindowClass();


	//-----------------------------------------------------------------------
	std::wstring windowText;
	HWND hwnd;


	style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	windowText = L"View";
	hwnd = createWindow(
		hParent,
		windowText.c_str(),
		static_cast<DWORD>(style),
		static_cast<DWORD>(styleEx),
		rect.left, rect.top, rect.right, rect.bottom
	);
	if (!hwnd)
	{
		throw std::wstring(L"View::View(): createWindow() failed");
	}


	//-----------------------------------------------------------------------
	//createBrowser();


	//-----------------------------------------------------------------------
	::ShowWindow(getHandle(), SW_SHOW);
	::UpdateWindow(getHandle());


	//-----------------------------------------------------------------------
	std::wstring text;


	text = getWindowText(this);
	text = L"View Window";
	setWindowText(this, text);
	text = getWindowText(this);
	WindowUI::debugPrintln(text);
}

View::~View()
{
}

void View::registerWindowMessageHandler(void)
{
	getWindowMessageHandler(WM_CREATE) = [this](WindowUI::WindowMessage& windowMessage) { onCreate(windowMessage); };
	getWindowMessageHandler(WM_DESTROY) = [this](WindowUI::WindowMessage& windowMessage) { onDestory(windowMessage); };
	getWindowMessageHandler(WM_CLOSE) = [this](WindowUI::WindowMessage& windowMessage) { onClose(windowMessage); };
	getWindowMessageHandler(WM_SIZE) = [this](WindowUI::WindowMessage& windowMessage) { onSize(windowMessage); };
	getWindowMessageHandler(WM_COMMAND) = [this](WindowUI::WindowMessage& windowMessage) { onCommand(windowMessage); };
}

void View::onCreate(WindowUI::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	//SetWindowTextW(windowMessage.hWnd, L"View");
	createBrowser();


	defaultWindowMessageHandler(windowMessage);
}

void View::onDestory(WindowUI::WindowMessage& windowMessage)
{
	destroyBrowser();
}

void View::onClose(WindowUI::WindowMessage& windowMessage)
{
}

void View::onSize(WindowUI::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	WindowUI::WM_SIZE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	//-----------------------------------------------------------------------
	if (_hBrowser)
	{
		RECT rect;


		GetClientRect(getHandle(), &rect);
		WindowUI::moveWindow(_hBrowser, rect);
	}
}

void View::onCommand(WindowUI::WindowMessage& windowMessage)
{
	WindowUI::WM_COMMAND_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	switch (windowMessageManipulator.nID())
	{
	case IDM_TEST1:
		onTest1(windowMessage);
		return;
		break;

	default:
		break;
	}


	defaultWindowMessageHandler(windowMessage);
}

void View::onTest1(WindowUI::WindowMessage& windowMessage)
{
	//------------------------------------------------------------------------
	std::wstring html;
	std::wostringstream oss;



	oss << L"<div class=\"input\">";
	oss << "<pre>";
	oss << L"안녕하세요?";
	oss << L"</pre>";
	oss << L"</div>";


	html = oss.str();
	browserInsertAdjacentHTML(html);


	oss.str(L"");
	oss.clear();


}

void View::destroyBrowser(void)
{
	_pDocument.Release();
	_pWB2.Release();
}

void View::createBrowser(void)
{
	//------------------------------------------------------------------------
	DWORD style;
	DWORD styleEx;


	style = WS_CHILD | WS_VISIBLE | WS_VSCROLL;
	styleEx = 0;
	_hBrowser=
		CreateWindowExW(
			styleEx,
			L"AtlAxWin140", 
			L"about:blank", 
			style, 
			0, 0, 0, 0, 
			getHandle(),
			0, 
			getWindowClass().hInstance, 
			0);
	if (!_hBrowser)
	{
		throw std::wstring(L"View::createBrowser(): CreateWindowExW() failed");
	}


	//------------------------------------------------------------------------
	{
		CComPtr<IUnknown> punkIE;


		if (AtlAxGetControl(_hBrowser, &punkIE) != S_OK)
		{
			throw std::wstring(L"View::createBrowser(): AtlAxGetControl() failed");
		}

		_pWB2 = punkIE;


		punkIE.Release();
	}


	//------------------------------------------------------------------------
	if (!_pWB2)
	{
		throw std::wstring(L"View::createBrowser(): _pWB2 failed");
	}
	_pWB2->put_Silent(VARIANT_TRUE);
	_pWB2->put_RegisterAsDropTarget(VARIANT_FALSE);
	_pWB2->get_Document((IDispatch**)&_pDocument);



	//------------------------------------------------------------------------
	{
		CComPtr<IUnknown> punkIE;
		ATL::CComPtr<IAxWinAmbientDispatch> ambient;


		AtlAxGetHost(_hBrowser, &punkIE);
		ambient = punkIE;
		if (ambient)
		{
//			ambient->put_AllowContextMenu(VARIANT_FALSE);
		}
	}


	//------------------------------------------------------------------------
	if (!_pDocument) 
	{
		throw std::wstring(L"View::createBrowser(): _pDocument failed");
	}


	//------------------------------------------------------------------------
	WCHAR szModuleFilePath[MAX_PATH] = { 0 };


	GetModuleFileNameW(NULL, szModuleFilePath, MAX_PATH);


	//------------------------------------------------------------------------
	WCHAR szURL[MAX_PATH] = { 0 };


	wsprintfW(szURL, L"res://%s/%d", szModuleFilePath, IDR_HTML1);



	//------------------------------------------------------------------------
	CComBSTR bstr_url(szURL);


	_pWB2->Navigate(bstr_url, NULL, NULL, NULL, NULL);


	//------------------------------------------------------------------------
	RECT rect;


	GetClientRect(getHandle(), &rect);
	WindowUI::moveWindow(_hBrowser, rect);
}

void View::browserScrollBottom(void)
{
	IHTMLWindow2* pHtmlWindow2;


	_pDocument->get_parentWindow(&pHtmlWindow2);
	if (pHtmlWindow2) 
	{
		pHtmlWindow2->scrollTo(0, SHRT_MAX);
		pHtmlWindow2->Release();
	}
}

void View::browserExecCommand(std::wstring command)
{
	// command = L"Copy"
	// command = L"Unselect"
	// command = L"Copy"
	// command = L"Copy"

	VARIANT var = { 0 };
	VARIANT_BOOL varBool = { 0 };


	var.vt = VT_EMPTY;
	
	
	CComBSTR bstr_command(command.c_str());


	_pDocument->execCommand(bstr_command, VARIANT_FALSE, var, &varBool);
}

void View::browserInsertAdjacentHTML(std::wstring html)
{
	CComQIPtr<IHTMLElement>pElementBody;


	_pDocument->get_body((IHTMLElement**)&pElementBody);
	if (pElementBody)
	{
		CComBSTR bstr_where("beforeEnd");
		CComBSTR bstr_html(html.c_str());


		pElementBody->insertAdjacentHTML(bstr_where, bstr_html);
		pElementBody.Release();
	}


	browserScrollBottom();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




