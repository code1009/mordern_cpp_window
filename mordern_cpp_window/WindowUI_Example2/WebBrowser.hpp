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
	DWORD _Cookie{ 0 };

public:
	virtual ~WebBrowserEventSink() {}

public:
	IConnectionPoint* getConnectionPoint(REFIID riid);
	void connect(void);
	void disconnect(void);

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
	WebBrowserEventSink _EventSink;

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
	void createWebBrowser(void);
	void destroyWebBrowser(void);

public:
	void scrollBottom(void);
	void execCommand(std::wstring command);
	void insertAdjacentHTML(std::wstring html);
	void execJSfunction(std::wstring function);

public:
	void onBeforeNavigate2   (DISPPARAMS* pDispParams);
	void onCommandStateChange(DISPPARAMS* pDispParams);
	void onDocumentComplete  (DISPPARAMS* pDispParams);
	void onDownloadBegin     (DISPPARAMS* pDispParams);
	void onDownloadComplete  (DISPPARAMS* pDispParams);
	void onNavigateComplete2 (DISPPARAMS* pDispParams);
	void onNewWindow2        (DISPPARAMS* pDispParams);
	void onProgressChange    (DISPPARAMS* pDispParams);
	void onPropertyChange    (DISPPARAMS* pDispParams);
	void onStatusTextChange  (DISPPARAMS* pDispParams);
	void onTitleChange       (DISPPARAMS* pDispParams);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




