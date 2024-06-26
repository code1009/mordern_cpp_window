#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Example2
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class View : public WindowUI::BasicWindow
{
public:
	CComQIPtr<IWebBrowser2> _pWB2;
	CComQIPtr<IHTMLDocument2> _pDocument;
	HWND _hBrowser;

public:
	explicit View(
		HWND hParent,
		const RECT& rect,
		std::uint32_t style = WS_CHILD | WS_VISIBLE | WS_BORDER,
		std::uint32_t styleEx = WS_EX_CLIENTEDGE
	);

	~View();

public:
	virtual void registerWindowMessageHandler(void) override;

public:
	void onCreate(WindowUI::WindowMessage& windowMessage);
	void onDestory(WindowUI::WindowMessage& windowMessage);
	void onClose(WindowUI::WindowMessage& windowMessage);

	void onSize(WindowUI::WindowMessage& windowMessage);

	void onCommand(WindowUI::WindowMessage& windowMessage);
	void onTest1(WindowUI::WindowMessage& windowMessage);

public:
	void createBrowser(void);
	void destroyBrowser(void);

public:
	void browserScrollBottom(void);
	void browserExecCommand(std::wstring command);
	void browserInsertAdjacentHTML(std::wstring html);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




