/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"
#include "../res/resource.h"

#include <atlbase.h>
#include <atlhost.h>

#include <winternl.h>
#include <MsHtmdid.h>

#include "../wui/WindowFunction.hpp"
#include "../wui/Core.hpp"
#include "../wui/WindowMessageManipulator.hpp"

#include "WebBrowser.hpp"

#include "uri.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui_Example2
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


	_pWindow->_pWebBrowser->QueryInterface(IID_IUnknown, (void**)&pUnk);
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
STDMETHODIMP WebBrowserEventSink::Invoke(DISPID dispid, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult, EXCEPINFO* pexecinfo, UINT* puArgErr)
{
	if (!pdispparams)
	{
		return E_INVALIDARG;
	}


	switch (dispid)
	{
	case DISPID_BEFORENAVIGATE2   : _pWindow->onBeforeNavigate2   (pdispparams, pvarResult); break;
	case DISPID_COMMANDSTATECHANGE: _pWindow->onCommandStateChange(pdispparams, pvarResult); break;
	case DISPID_DOCUMENTCOMPLETE  : _pWindow->onDocumentComplete  (pdispparams, pvarResult); break;
	case DISPID_DOWNLOADBEGIN     : _pWindow->onDownloadBegin     (pdispparams, pvarResult); break;
	case DISPID_DOWNLOADCOMPLETE  : _pWindow->onDownloadComplete  (pdispparams, pvarResult); break;
	case DISPID_NAVIGATECOMPLETE2 : _pWindow->onNavigateComplete2 (pdispparams, pvarResult); break;
	case DISPID_PROGRESSCHANGE    : _pWindow->onProgressChange    (pdispparams, pvarResult); break;
	case DISPID_PROPERTYCHANGE    : _pWindow->onPropertyChange    (pdispparams, pvarResult); break;
	case DISPID_STATUSTEXTCHANGE  : _pWindow->onStatusTextChange  (pdispparams, pvarResult); break;
	case DISPID_NEWWINDOW2        : _pWindow->onNewWindow2        (pdispparams, pvarResult); break;
	case DISPID_TITLECHANGE       : _pWindow->onTitleChange       (pdispparams, pvarResult); break;


	case DISPID_ONMESSAGE:
		break;
	}
	
	return S_OK;
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WebBrowserWindow::WebBrowserWindow(
	HWND hParent,
	const RECT& rect
)
{
	//-----------------------------------------------------------------------
	registerWindowMessageHandler();


	//-----------------------------------------------------------------------
	initializeWindowClass();
	registerWindowClass();


	//-----------------------------------------------------------------------
	std::uint32_t style = WS_CHILD | WS_VISIBLE; // | WS_BORDER;
	std::uint32_t styleEx = WS_EX_CLIENTEDGE;
	std::wstring windowText;
	HWND hwnd;


	styleEx = 0;
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
	wui::debugPrintln(text);
}

WebBrowserWindow::~WebBrowserWindow()
{
}

void WebBrowserWindow::registerWindowMessageHandler(void)
{
	getWindowMessageHandler(WM_CREATE) = [this](wui::WindowMessage& windowMessage) { onCreate(windowMessage); };
	getWindowMessageHandler(WM_DESTROY) = [this](wui::WindowMessage& windowMessage) { onDestory(windowMessage); };
	getWindowMessageHandler(WM_CLOSE) = [this](wui::WindowMessage& windowMessage) { onClose(windowMessage); };
	getWindowMessageHandler(WM_SIZE) = [this](wui::WindowMessage& windowMessage) { onSize(windowMessage); };
	getWindowMessageHandler(WM_COMMAND) = [this](wui::WindowMessage& windowMessage) { onCommand(windowMessage); };
}

void WebBrowserWindow::onCreate(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	//SetWindowTextW(windowMessage.hWnd, L"WebBrowserWindow");
	createWebBrowser();


	defaultWindowMessageHandler(windowMessage);
}

void WebBrowserWindow::onDestory(wui::WindowMessage& windowMessage)
{
	destroyWebBrowser();
}

void WebBrowserWindow::onClose(wui::WindowMessage& windowMessage)
{
}

void WebBrowserWindow::onSize(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	wui::WM_SIZE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	//-----------------------------------------------------------------------
	if (_hWebBrowserWindowHandle)
	{
		RECT rect;


		GetClientRect(getHandle(), &rect);
		wui::moveWindow(_hWebBrowserWindowHandle, rect);
	}
}

void WebBrowserWindow::onCommand(wui::WindowMessage& windowMessage)
{
	wui::WM_COMMAND_WindowMessageManipulator windowMessageManipulator(&windowMessage);


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

void WebBrowserWindow::onTest1(wui::WindowMessage& windowMessage)
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

void WebBrowserWindow::onTest2(wui::WindowMessage& windowMessage)
{
	execJSfunction(L"test0");
}

std::wstring WebBrowserWindow::getCurrentURL(void)
{
	//------------------------------------------------------------------------
	WCHAR szModuleFilePath[MAX_PATH] = { 0 };


	GetModuleFileNameW(NULL, szModuleFilePath, MAX_PATH);


	//------------------------------------------------------------------------
	WCHAR szURL[MAX_PATH] = { 0 };


	wsprintfW(szURL, L"res://%s/%d", szModuleFilePath, IDR_HTML1);


	//------------------------------------------------------------------------

	return std::wstring (szURL);
}

//===========================================================================
void WebBrowserWindow::onHTMLDocumentEvent(std::wstring wurl)
{
	//------------------------------------------------------------------------
	std::string url;


	url = uri::wcs_to_mbcs(wurl);


	//------------------------------------------------------------------------
	std::string base;
	std::string file;


	base = uri::erase_query_string(url);
	file = uri::decode(uri::parse_file(base));


	//------------------------------------------------------------------------
	std::string query_string;
	std::map<std::string, std::string> param_map;
	std::map<std::wstring, std::wstring> wparam_map;


	query_string = uri::parse_query_string(url);
	param_map = uri::parse_query_string_parameters(query_string); // utf8
	wparam_map = uri::utf8_to_wcs(param_map);


	//------------------------------------------------------------------------
	std::wstring html;
	std::wostringstream oss;


	//------------------------------------------------------------------------
	oss << L"<div class=\"input\">";
	oss << "<pre>";
	oss << uri::mbcs_to_wcs(file); // uri::mbcs_to_wcs(file, CP_UTF8);
	oss << L": C++에서 이벤트 처리합니다.";
	oss << L"</pre>";
	oss << L"</div>";


	html = oss.str();
	insertAdjacentHTML(html);
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
		CComPtr<IAxWinAmbientDispatch> ambient;


		AtlAxGetHost(_hWebBrowserWindowHandle, &punkIE);
		ambient = punkIE;
		if (ambient)
		{
			ambient->put_AllowContextMenu(VARIANT_FALSE);
		}
	}


	//------------------------------------------------------------------------
	if (!_pHTMLDocument) 
	{
		throw std::wstring(L"WebBrowser::createWebBrowser(): _pHTMLDocument failed");
	}


	//------------------------------------------------------------------------
	CComBSTR bstr_url(getCurrentURL().c_str());


	_pWebBrowser->Navigate(bstr_url, NULL, NULL, NULL, NULL);


	//------------------------------------------------------------------------
	_EventSink._pWindow = this;
	_EventSink.connect();


	//------------------------------------------------------------------------
	RECT rect;


	GetClientRect(getHandle(), &rect);
	wui::moveWindow(_hWebBrowserWindowHandle, rect);
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
	CComPtr<IHTMLElement> pElementBody;


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
	CComPtr<IDispatch> pDispatch;


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
void WebBrowserWindow::onBeforeNavigate2(DISPPARAMS* pdispparams, VARIANT* pvarResult)
{
	/*
	[6] IDispatch * pDisp,
	[5] VARIANT * Url,
	[4] VARIANT * Flags,
	[3] VARIANT * TargetFrameName,
	[2] VARIANT * PostData,
	[1] VARIANT * Headers,
	[0] VARIANT_BOOL * Cancel
	*/

	if (pdispparams && pdispparams->cArgs == 7 && pdispparams->rgvarg) 
	{
		VARIANTARG& url = pdispparams->rgvarg[5];
		std::wstring url_string;


		/*
		if (url.vt == VT_BSTR)
		{
			url_string = url.bstrVal;
			wui::debugPrintln(url_string);
		}
		if (url.vt == (VT_BSTR | VT_BYREF))
		{
			url_string = *url.pbstrVal;
			wui::debugPrintln(url_string);
		}
		*/
		if (url.vt == (VT_VARIANT | VT_BYREF))
		{
			if (url.pvarVal->vt == VT_BSTR)
			{
				url_string = url.pvarVal->bstrVal;
				wui::debugPrintln(url_string);
				// res://D:\test\mordern_cpp_window\Debug\mordern_cpp_window.exe/101
			}
		}


		VARIANTARG& cancel = pdispparams->rgvarg[0];


		if (cancel.vt == (VT_BOOL | VT_BYREF))
		{
			//------------------------------------------------------------------------
			if (url_string == getCurrentURL())
			{
				*cancel.pboolVal = VARIANT_FALSE;
			}
			else
			{
				*cancel.pboolVal = VARIANT_TRUE;

				// url로 html ui 이벤트 처리로 활용 가능
				onHTMLDocumentEvent(url_string);
			}
		}
	}
}

// Called when the enabled state of a command changes.
void WebBrowserWindow::onCommandStateChange(DISPPARAMS* pdispparams, VARIANT* pvarResult)
{
	/*
	CToolBar& TB = GetToolBar();

	if ((pdispparams) && (pdispparams->cArgs == 2))
	{
		BOOL isEnabled = pdispparams->rgvarg[0].boolVal;
		LONG command = pdispparams->rgvarg[1].lVal;
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
void WebBrowserWindow::onDocumentComplete(DISPPARAMS* pdispparams, VARIANT* pvarResult)
{


}

// Called when a navigation operation is beginning.
void WebBrowserWindow::onDownloadBegin(DISPPARAMS* pdispparams, VARIANT* pvarResult)
{

}

// Called when a navigation operation finishes, is halted, or fails.
void WebBrowserWindow::onDownloadComplete(DISPPARAMS* pdispparams, VARIANT* pvarResult)
{

}

// Called when navigation completes on either a window or frameset element.
void WebBrowserWindow::onNavigateComplete2(DISPPARAMS* pdispparams, VARIANT* pvarResult)
{
	/*
	CString str = _T("Navigate Complete");

	if (pdispparams->rgvarg[0].vt == (VT_BYREF | VT_VARIANT))
	{
		VARIANT url = *pdispparams->rgvarg[0].pvarVal;
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
void WebBrowserWindow::onNewWindow2(DISPPARAMS* pdispparams, VARIANT* pvarResult)
{

}

// Called when the progress of a download operation is updated on the object.
void WebBrowserWindow::onProgressChange(DISPPARAMS* pdispparams, VARIANT* pvarResult)
{
	/*
	CString str;

	if (pdispparams->cArgs != 0)
	{
		if (pdispparams->cArgs > 1 && pdispparams->rgvarg[1].vt == VT_I4)
		{
			int progress = pdispparams->rgvarg[1].lVal;
			str << _T("Progress = ") << progress;
		}

		if (pdispparams->rgvarg[0].vt == VT_I4)
		{
			int progressMax = pdispparams->rgvarg[0].lVal;
			str << _T(", ProgressMax = ") << progressMax;
		}

		str << _T("\n");
		TRACE(str);
	}
	*/
}

// Called when the IWebBrowser2::PutProperty method of the object changes the
// value of a property.
void WebBrowserWindow::onPropertyChange(DISPPARAMS* pdispparams, VARIANT* pvarResult)
{
	/*
	CString str;
	if (pdispparams->cArgs > 0 && pdispparams->rgvarg[0].vt == VT_BSTR)
	{
		str += _T("Property Change:");
		str += pdispparams->rgvarg[0].bstrVal;
	}

	str += _T("\n");
	TRACE(str);
	*/
}

// Called when the status bar text of the object has changed.
void WebBrowserWindow::onStatusTextChange(DISPPARAMS* pdispparams, VARIANT* pvarResult)
{
	/*
	CString statusText = pdispparams->rgvarg->bstrVal;

	if (statusText != _T(""))
		SetStatusText(statusText);
	else
		SetStatusText(_T("Done"));
	*/
}

// Called when the title of a document in the object becomes available
// or changes.
void WebBrowserWindow::onTitleChange(DISPPARAMS* pdispparams, VARIANT* pvarResult)
{
	/*
	TRACE(_T("TitleChange: \n"));
	CString str;

	if ((pdispparams->cArgs > 0) && (pdispparams->rgvarg[0].vt == VT_BSTR))
	{
		str = pdispparams->rgvarg[0].bstrVal;
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




