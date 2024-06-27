#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Example2
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebBrowserWindow;





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebBrowserEventSink : public IDispatch
{
public:
	WebBrowserWindow* _pHostWindow{ nullptr };

public:
	virtual ~WebBrowserEventSink() {}

public:
	// IUnknown
	virtual STDMETHODIMP QueryInterface(REFIID riid, void** ppvObject);
	virtual STDMETHODIMP_(ULONG) AddRef();
	virtual STDMETHODIMP_(ULONG) Release();

public:
	// IDispatch
	virtual STDMETHODIMP GetIDsOfNames(REFIID riid, OLECHAR** rgszNames, unsigned int cNames, LCID lcid, DISPID* rgdispid);
	virtual STDMETHODIMP GetTypeInfo(unsigned int itinfo, LCID lcid, ITypeInfo** pptinfo);
	virtual STDMETHODIMP GetTypeInfoCount(unsigned int* pctinfo);
	virtual STDMETHODIMP Invoke(DISPID dispid, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS* pdispparams, VARIANT* pvarResult, EXCEPINFO* pexecinfo, unsigned int* puArgErr);
};






/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebBrowserWindow : public WindowUI::BasicWindow
{
public:
	CComQIPtr<IWebBrowser2> _pWebBrowser;
	CComQIPtr<IHTMLDocument2> _pHTMLDocument;
	HWND _hWebBrowserWindowHandle;

public:
	explicit WebBrowserWindow(
		HWND hParent,
		const RECT& rect,
		std::uint32_t style = WS_CHILD | WS_VISIBLE | WS_BORDER,
		std::uint32_t styleEx = WS_EX_CLIENTEDGE
	);

	virtual ~WebBrowserWindow();

public:
	virtual void registerWindowMessageHandler(void) override;

public:
	void onCreate(WindowUI::WindowMessage& windowMessage);
	void onDestory(WindowUI::WindowMessage& windowMessage);
	void onClose(WindowUI::WindowMessage& windowMessage);

	void onSize(WindowUI::WindowMessage& windowMessage);

	void onCommand(WindowUI::WindowMessage& windowMessage);
	void onTest1(WindowUI::WindowMessage& windowMessage);
	void onTest2(WindowUI::WindowMessage& windowMessage);

public:
	void WebBrowser_create(void);
	void WebBrowser_destroy(void);

public:
	void WebBrowser_scrollBottom(void);
	void WebBrowser_execCommand(std::wstring command);
	void WebBrowser_insertAdjacentHTML(std::wstring html);
	void WebBrowser_execJSfunction(std::wstring function);

public:
	void WebBrowser_onBeforeNavigate2   (DISPPARAMS* pDispParams);
	void WebBrowser_onCommandStateChange(DISPPARAMS* pDispParams);
	void WebBrowser_onDocumentComplete  (DISPPARAMS* pDispParams);
	void WebBrowser_onDownloadBegin     (DISPPARAMS* pDispParams);
	void WebBrowser_onDownloadComplete  (DISPPARAMS* pDispParams);
	void WebBrowser_onNavigateComplete2 (DISPPARAMS* pDispParams);
	void WebBrowser_onNewWindow2        (DISPPARAMS* pDispParams);
	void WebBrowser_onProgressChange    (DISPPARAMS* pDispParams);
	void WebBrowser_onPropertyChange    (DISPPARAMS* pDispParams);
	void WebBrowser_onStatusTextChange  (DISPPARAMS* pDispParams);
	void WebBrowser_onTitleChange       (DISPPARAMS* pDispParams);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




