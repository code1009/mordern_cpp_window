﻿/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"
#include "../res/resource.h"

#include <atlbase.h>
#include <atlhost.h>

#include <winternl.h>

#include "../WindowUI/WindowFunction.hpp"
#include "../WindowUI/Core.hpp"
#include "../WindowUI/WindowMessageManipulator.hpp"

#include "WebBrowser.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Example2
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// The following can also be found in exdispid.h (except MinGW)
#define DISPID_STATUSTEXTCHANGE   102
#define DISPID_DOWNLOADCOMPLETE   104
#define DISPID_COMMANDSTATECHANGE 105
#define DISPID_DOWNLOADBEGIN      106
#define DISPID_PROGRESSCHANGE     108
#define DISPID_PROPERTYCHANGE     112
#define DISPID_TITLECHANGE        113
#define DISPID_BEFORENAVIGATE2    250
#define DISPID_NEWWINDOW2         251
#define DISPID_NAVIGATECOMPLETE2  252
#define DISPID_DOCUMENTCOMPLETE   259





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// Retrieve pointer to IConnectionPoint.
// Call Release on this pointer when it is no longer required.
IConnectionPoint* WebBrowserEventSink::getConnectionPoint(REFIID riid)
{
	IConnectionPoint* pcp = nullptr;
	IUnknown* pUnk = nullptr;


	_pHostWindow->_pWebBrowser->QueryInterface(IID_IUnknown, (void**)&pUnk);
	if (pUnk)
	{
		IConnectionPointContainer* pcpc = nullptr;


		if (!SUCCEEDED(pUnk->QueryInterface(IID_IConnectionPointContainer, (void**)&pcpc)))
		{
		}

		if (pcpc)
		{
			if (!SUCCEEDED(pcpc->FindConnectionPoint(riid, &pcp)))
			{
			}
			pcpc->Release();
		}

		pUnk->Release();
	}

	return pcp;
}

void WebBrowserEventSink::connect(void)
{
	IConnectionPoint* pcp = NULL;


	pcp = getConnectionPoint(DIID_DWebBrowserEvents2);
	if (pcp)
	{
		if (!SUCCEEDED(pcp->Advise(this, &_Cookie)))
		{
		}
		pcp->Release();
	}
}

void WebBrowserEventSink::disconnect(void)
{
	IConnectionPoint* pcp = NULL;


	pcp = getConnectionPoint(DIID_DWebBrowserEvents2);
	if (pcp)
	{
		if (!SUCCEEDED(pcp->Unadvise(_Cookie)))
		{
		}
		pcp->Release();
	}
}

//===========================================================================
// Assigns a pointer to ppvObject for the specified interface.
STDMETHODIMP WebBrowserEventSink::QueryInterface(REFIID riid, void** ppvObject)
{
	if (!ppvObject)
	{
		return E_POINTER;
	}


	if (IsEqualIID(riid, IID_IDispatch))
	{
		*ppvObject = static_cast<IDispatch*>(this);
	}
	else if (IsEqualIID(riid, IID_IUnknown))
	{
		*ppvObject = static_cast<IUnknown*>(this);
	}
	else
	{
		*ppvObject = NULL;
		return E_NOINTERFACE;
	}

	return S_OK;
}

// Not implemented. Increments a reference count.
STDMETHODIMP_(ULONG) WebBrowserEventSink::AddRef()
{
	// Always 1. Automatic deletion isn't required.
	return 1;
}

// Not implemented. Decrements a reference count.
STDMETHODIMP_(ULONG) WebBrowserEventSink::Release()
{
	// Always 1. Automatic deletion isn't required.
	return 1;
}

//===========================================================================
// Not implemented. Retrieves an array of DISPID.
STDMETHODIMP WebBrowserEventSink::GetIDsOfNames(REFIID, OLECHAR**, unsigned int, LCID, DISPID* rgdispid)
{
	if (rgdispid != NULL)
	{
		*rgdispid = DISPID_UNKNOWN;
	}

	return DISP_E_UNKNOWNNAME;
}

// Not implemented. Retrieves the type information for an object.
STDMETHODIMP WebBrowserEventSink::GetTypeInfo(unsigned int, LCID, ITypeInfo**)
{
	return E_NOTIMPL;
}

// Not implemented. Retrieves the number of type information interfaces that an object provides.
STDMETHODIMP WebBrowserEventSink::GetTypeInfoCount(unsigned int*)
{
	return E_NOTIMPL;
}

// Sends a window message to the frame when a browser event occurs.
STDMETHODIMP WebBrowserEventSink::Invoke(DISPID dispid, REFIID, LCID, WORD, DISPPARAMS* pDispParams, VARIANT*, EXCEPINFO*, unsigned int*)
{
	if (!pDispParams)
	{
		return E_INVALIDARG;
	}


	switch (dispid)
	{
	case DISPID_BEFORENAVIGATE2   : _pHostWindow->onBeforeNavigate2   (pDispParams); break;
	case DISPID_COMMANDSTATECHANGE: _pHostWindow->onCommandStateChange(pDispParams); break;
	case DISPID_DOCUMENTCOMPLETE  : _pHostWindow->onDocumentComplete  (pDispParams); break;
	case DISPID_DOWNLOADBEGIN     : _pHostWindow->onDownloadBegin     (pDispParams); break;
	case DISPID_DOWNLOADCOMPLETE  : _pHostWindow->onDownloadComplete  (pDispParams); break;
	case DISPID_NAVIGATECOMPLETE2 : _pHostWindow->onNavigateComplete2 (pDispParams); break;
	case DISPID_PROGRESSCHANGE    : _pHostWindow->onProgressChange    (pDispParams); break;
	case DISPID_PROPERTYCHANGE    : _pHostWindow->onPropertyChange    (pDispParams); break;
	case DISPID_STATUSTEXTCHANGE  : _pHostWindow->onStatusTextChange  (pDispParams); break;
	case DISPID_NEWWINDOW2        : _pHostWindow->onNewWindow2        (pDispParams); break;
	case DISPID_TITLECHANGE       : _pHostWindow->onTitleChange       (pDispParams); break;
	}
	
	return S_OK;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WebBrowserWindow::WebBrowserWindow(
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
	windowText = L"WebBrowserWindow";
	hwnd = createWindow(
		hParent,
		windowText.c_str(),
		static_cast<DWORD>(style),
		static_cast<DWORD>(styleEx),
		rect.left, rect.top, rect.right, rect.bottom
	);
	if (!hwnd)
	{
		throw std::wstring(L"WebBrowserWindow::WebBrowserWindow(): createWindow() failed");
	}


	//-----------------------------------------------------------------------
	::ShowWindow(getHandle(), SW_SHOW);
	::UpdateWindow(getHandle());


	//-----------------------------------------------------------------------
	std::wstring text;


	text = getWindowText(this);
	text = L"WebBrowserWindow";
	setWindowText(this, text);
	text = getWindowText(this);
	WindowUI::debugPrintln(text);
}

WebBrowserWindow::~WebBrowserWindow()
{
}

void WebBrowserWindow::registerWindowMessageHandler(void)
{
	getWindowMessageHandler(WM_CREATE) = [this](WindowUI::WindowMessage& windowMessage) { onCreate(windowMessage); };
	getWindowMessageHandler(WM_DESTROY) = [this](WindowUI::WindowMessage& windowMessage) { onDestory(windowMessage); };
	getWindowMessageHandler(WM_CLOSE) = [this](WindowUI::WindowMessage& windowMessage) { onClose(windowMessage); };
	getWindowMessageHandler(WM_SIZE) = [this](WindowUI::WindowMessage& windowMessage) { onSize(windowMessage); };
	getWindowMessageHandler(WM_COMMAND) = [this](WindowUI::WindowMessage& windowMessage) { onCommand(windowMessage); };
}

void WebBrowserWindow::onCreate(WindowUI::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	//SetWindowTextW(windowMessage.hWnd, L"WebBrowserWindow");
	createWebBrowser();


	defaultWindowMessageHandler(windowMessage);
}

void WebBrowserWindow::onDestory(WindowUI::WindowMessage& windowMessage)
{
	destroyWebBrowser();
}

void WebBrowserWindow::onClose(WindowUI::WindowMessage& windowMessage)
{
}

void WebBrowserWindow::onSize(WindowUI::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	WindowUI::WM_SIZE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	//-----------------------------------------------------------------------
	if (_hWebBrowserWindowHandle)
	{
		RECT rect;


		GetClientRect(getHandle(), &rect);
		WindowUI::moveWindow(_hWebBrowserWindowHandle, rect);
	}
}

void WebBrowserWindow::onCommand(WindowUI::WindowMessage& windowMessage)
{
	WindowUI::WM_COMMAND_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	switch (windowMessageManipulator.nID())
	{
	case IDM_TEST1:
		onTest1(windowMessage);
		return;
		break;

	case IDM_TEST2:
		onTest2(windowMessage);
		return;
		break;

	default:
		break;
	}


	defaultWindowMessageHandler(windowMessage);
}

void WebBrowserWindow::onTest1(WindowUI::WindowMessage& windowMessage)
{
	//------------------------------------------------------------------------
	std::wstring html;
	std::wostringstream oss;


	//------------------------------------------------------------------------
	oss << L"<div class=\"input\">";
	oss << "<pre>";
	oss << L"안녕하세요?";
	oss << L"</pre>";
	oss << L"</div>";


	html = oss.str();
	insertAdjacentHTML(html);


	//------------------------------------------------------------------------
	oss.str(L"");
	oss.clear();


	//------------------------------------------------------------------------
	oss << L"<div class=\"result\">";
	oss << L"<div class=\"icon\">";
	oss << L"<img>";
	oss << L"</div>";
	oss << L"<div class=\"chatting\">";
	oss << L"<div class=\"output\">";
	oss << L"<pre>";

	oss << L"안녕?";

	oss << L"</pre>";
	oss << L"</div>";
	oss << L"</div>";
	oss << L"</div>";



	html = oss.str();
	insertAdjacentHTML(html);
}

void WebBrowserWindow::onTest2(WindowUI::WindowMessage& windowMessage)
{
	execJSfunction(L"test0");
}

//===========================================================================
// https://github.com/kenjinote/cmdchat/blob/main/Source.cpp
//===========================================================================
void WebBrowserWindow::destroyWebBrowser(void)
{
	//------------------------------------------------------------------------
	_pWebBrowser->Stop();


	//------------------------------------------------------------------------
	_EventSink.disconnect();


	//------------------------------------------------------------------------
	_pHTMLDocument.Release();
	_pWebBrowser.Release();
}

void WebBrowserWindow::createWebBrowser(void)
{
	//------------------------------------------------------------------------
	DWORD style;
	DWORD styleEx;


	style = WS_CHILD | WS_VISIBLE | WS_VSCROLL;
	styleEx = 0;
	_hWebBrowserWindowHandle=
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
	if (!_hWebBrowserWindowHandle)
	{
		throw std::wstring(L"WebBrowser::createWebBrowser(): CreateWindowExW() failed");
	}


	//------------------------------------------------------------------------
	{
		CComPtr<IUnknown> punkIE;


		if (AtlAxGetControl(_hWebBrowserWindowHandle, &punkIE) != S_OK)
		{
			throw std::wstring(L"WebBrowser::createWebBrowser(): AtlAxGetControl() failed");
		}

		_pWebBrowser = punkIE;


		punkIE.Release();
	}


	//------------------------------------------------------------------------
	if (!_pWebBrowser)
	{
		throw std::wstring(L"WebBrowser::createWebBrowser(): _pWebBrowser failed");
	}
	_pWebBrowser->put_Silent(VARIANT_TRUE);
	_pWebBrowser->put_RegisterAsDropTarget(VARIANT_FALSE);
	_pWebBrowser->get_Document((IDispatch**)&_pHTMLDocument);



	//------------------------------------------------------------------------
	{
		CComPtr<IUnknown> punkIE;
		ATL::CComPtr<IAxWinAmbientDispatch> ambient;


		AtlAxGetHost(_hWebBrowserWindowHandle, &punkIE);
		ambient = punkIE;
		if (ambient)
		{
//			ambient->put_AllowContextMenu(VARIANT_FALSE);
		}
	}


	//------------------------------------------------------------------------
	if (!_pHTMLDocument) 
	{
		throw std::wstring(L"WebBrowser::createWebBrowser(): _pHTMLDocument failed");
	}


	//------------------------------------------------------------------------
	WCHAR szModuleFilePath[MAX_PATH] = { 0 };


	GetModuleFileNameW(NULL, szModuleFilePath, MAX_PATH);


	//------------------------------------------------------------------------
	WCHAR szURL[MAX_PATH] = { 0 };


	wsprintfW(szURL, L"res://%s/%d", szModuleFilePath, IDR_HTML1);



	//------------------------------------------------------------------------
	CComBSTR bstr_url(szURL);


	_pWebBrowser->Navigate(bstr_url, NULL, NULL, NULL, NULL);


	//------------------------------------------------------------------------
	_EventSink._pHostWindow = this;
	_EventSink.connect();


	//------------------------------------------------------------------------
	RECT rect;


	GetClientRect(getHandle(), &rect);
	WindowUI::moveWindow(_hWebBrowserWindowHandle, rect);
}

void WebBrowserWindow::scrollBottom(void)
{
	IHTMLWindow2* pHtmlWindow2;


	_pHTMLDocument->get_parentWindow(&pHtmlWindow2);
	if (pHtmlWindow2) 
	{
		pHtmlWindow2->scrollTo(0, SHRT_MAX);
		pHtmlWindow2->Release();
	}
}

void WebBrowserWindow::execCommand(std::wstring command)
{
	// command = L"Copy"
	// command = L"Unselect"

	VARIANT var = { 0 };
	VARIANT_BOOL varBool = { 0 };


	var.vt = VT_EMPTY;
	
	
	CComBSTR bstr_command(command.c_str());


	_pHTMLDocument->execCommand(bstr_command, VARIANT_FALSE, var, &varBool);
}

void WebBrowserWindow::insertAdjacentHTML(std::wstring html)
{
	CComQIPtr<IHTMLElement>pElementBody;


	_pHTMLDocument->get_body((IHTMLElement**)&pElementBody);
	if (pElementBody)
	{
		CComBSTR bstr_where(L"beforeEnd");
		CComBSTR bstr_html(html.c_str());


		pElementBody->insertAdjacentHTML(bstr_where, bstr_html);
		pElementBody.Release();
	}


	scrollBottom();
}

//===========================================================================
// https://www.codeproject.com/Articles/2352/JavaScript-call-from-C
//===========================================================================
void WebBrowserWindow::execJSfunction(std::wstring functionName)
{
	//-----------------------------------------------------------------------
	CComQIPtr<IDispatch> pDispatch;


	_pHTMLDocument->get_Script((IDispatch**)&pDispatch);
	if (!pDispatch)
	{
		return;
	}



	//-----------------------------------------------------------------------
	CComBSTR bstr_functionName(functionName.c_str());
	DISPID dispid = NULL;
	HRESULT hr;


	hr = pDispatch->GetIDsOfNames(IID_NULL, &bstr_functionName, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
	if (FAILED(hr))
	{
		pDispatch.Release();
		return;
	}


	//-----------------------------------------------------------------------
	std::vector<std::wstring> functionParamArray;
	std::wstring functionResult;


	functionParamArray.push_back(std::wstring(L"C++에서 부름"));


	//-----------------------------------------------------------------------
	UINT count;
	UINT i;


	count = static_cast<UINT>(functionParamArray.size());


	//-----------------------------------------------------------------------
	DISPPARAMS dispparams;


	memset(&dispparams, 0, sizeof dispparams);
	dispparams.cArgs = count;
	dispparams.rgvarg = new VARIANT[dispparams.cArgs];


	for (i = 0; i < count; i++)
	{
		CComBSTR bstr(functionParamArray.at(count - 1 - i).c_str() ); // back reading
		
		
		hr = bstr.CopyTo(&dispparams.rgvarg[i].bstrVal);

		dispparams.rgvarg[i].vt = VT_BSTR;
	}
	dispparams.cNamedArgs = 0;


	//-----------------------------------------------------------------------
	EXCEPINFO excepInfo;


	memset(&excepInfo, 0, sizeof excepInfo);


	//-----------------------------------------------------------------------
	CComVariant vaResult;


	//-----------------------------------------------------------------------
	UINT nArgErr = (UINT)-1;  // initialize to invalid arg


	//-----------------------------------------------------------------------
	hr = pDispatch->Invoke(dispid, IID_NULL, 0,
		DISPATCH_METHOD, &dispparams, &vaResult, &excepInfo, &nArgErr);


	//-----------------------------------------------------------------------
	delete[] dispparams.rgvarg;


	//-----------------------------------------------------------------------
	if (vaResult.vt == VT_BSTR)
	{
		functionResult = vaResult.bstrVal;
	}


	//-----------------------------------------------------------------------
	pDispatch.Release();


	//-----------------------------------------------------------------------
	::MessageBoxW(nullptr, functionResult.c_str(), L"C++에서 받음", MB_OK);
}

//===========================================================================
// https://github.com/DavidNash2024/Win32xx/blob/master/samples/Browser/src/Mainfrm.cpp
//===========================================================================
// Called before navigation occurs on either a window or frameset element.
void WebBrowserWindow::onBeforeNavigate2(DISPPARAMS* pDispParams)
{

}

// Called when the enabled state of a command changes.
void WebBrowserWindow::onCommandStateChange(DISPPARAMS* pDispParams)
{
	/*
	CToolBar& TB = GetToolBar();

	if ((pDispParams) && (pDispParams->cArgs == 2))
	{
		BOOL isEnabled = pDispParams->rgvarg[0].boolVal;
		LONG command = pDispParams->rgvarg[1].lVal;
		{
			// Update the Forward and Back buttons.
			switch (command)
			{
			case CSC_NAVIGATEFORWARD:
				isEnabled ? TB.EnableButton(IDM_FORWARD) : TB.DisableButton(IDM_FORWARD);
				break;
			case CSC_NAVIGATEBACK:
				isEnabled ? TB.EnableButton(IDM_BACK) : TB.DisableButton(IDM_BACK);
				break;
			}
		}
	}
	*/
}

// Called when a document has been completely loaded and initialized.
void WebBrowserWindow::onDocumentComplete(DISPPARAMS* pDispParams)
{
}

// Called when a navigation operation is beginning.
void WebBrowserWindow::onDownloadBegin(DISPPARAMS* pDispParams)
{

}

// Called when a navigation operation finishes, is halted, or fails.
void WebBrowserWindow::onDownloadComplete(DISPPARAMS* pDispParams)
{

}

// Called when navigation completes on either a window or frameset element.
void WebBrowserWindow::onNavigateComplete2(DISPPARAMS* pDispParams)
{
	/*
	CString str = _T("Navigate Complete");

	if (pDispParams->rgvarg[0].vt == (VT_BYREF | VT_VARIANT))
	{
		VARIANT url = *pDispParams->rgvarg[0].pvarVal;
		url.vt = VT_BSTR;

		str += url.bstrVal;
		str += _T("\n");
		TRACE(str);
		VariantClear(&url);
	}

	str = m_browser.GetLocationURL();

	// Update the URL in the ComboboxEx edit box.
	m_combo.SetWindowText(CString(str));
	*/
}

// Called when a new window is to be created.
void WebBrowserWindow::onNewWindow2(DISPPARAMS* pDispParams)
{

}

// Called when the progress of a download operation is updated on the object.
void WebBrowserWindow::onProgressChange(DISPPARAMS* pDispParams)
{
	/*
	CString str;

	if (pDispParams->cArgs != 0)
	{
		if (pDispParams->cArgs > 1 && pDispParams->rgvarg[1].vt == VT_I4)
		{
			int progress = pDispParams->rgvarg[1].lVal;
			str << _T("Progress = ") << progress;
		}

		if (pDispParams->rgvarg[0].vt == VT_I4)
		{
			int progressMax = pDispParams->rgvarg[0].lVal;
			str << _T(", ProgressMax = ") << progressMax;
		}

		str << _T("\n");
		TRACE(str);
	}
	*/
}

// Called when the IWebBrowser2::PutProperty method of the object changes the
// value of a property.
void WebBrowserWindow::onPropertyChange(DISPPARAMS* pDispParams)
{
	/*
	CString str;
	if (pDispParams->cArgs > 0 && pDispParams->rgvarg[0].vt == VT_BSTR)
	{
		str += _T("Property Change:");
		str += pDispParams->rgvarg[0].bstrVal;
	}

	str += _T("\n");
	TRACE(str);
	*/
}

// Called when the status bar text of the object has changed.
void WebBrowserWindow::onStatusTextChange(DISPPARAMS* pDispParams)
{
	/*
	CString statusText = pDispParams->rgvarg->bstrVal;

	if (statusText != _T(""))
		SetStatusText(statusText);
	else
		SetStatusText(_T("Done"));
	*/
}

// Called when the title of a document in the object becomes available
// or changes.
void WebBrowserWindow::onTitleChange(DISPPARAMS* pDispParams)
{
	/*
	TRACE(_T("TitleChange: \n"));
	CString str;

	if ((pDispParams->cArgs > 0) && (pDispParams->rgvarg[0].vt == VT_BSTR))
	{
		str = pDispParams->rgvarg[0].bstrVal;
		str += _T(" - Win32++ Browser");
		TRACE(str + _T("\n"));
	}
	else
		str = LoadString(IDW_MAIN);

	SetWindowText(str);
	*/
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




