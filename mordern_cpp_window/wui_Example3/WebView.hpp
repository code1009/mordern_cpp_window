#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
// \packages\Microsoft.Windows.ImplementationLibrary.1.0.191107.2\include\wil
#include <wrl.h>
#include <wil/com.h>

// \packages\Microsoft.Web.WebView2.1.0.902.49\build\native\include
#include <WebView2.h>





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui_Example3
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class WebView : public wui::BasicWindow
{
public:
	wil::com_ptr<ICoreWebView2Controller> m_controller;
	wil::com_ptr<ICoreWebView2> m_webView;

public:
	explicit WebView(
		HWND hParent,
		const RECT& rect
	);

	virtual ~WebView();

public:
	virtual void registerWindowMessageHandler(void) override;

public:
	void onCreate(wui::WindowMessage& windowMessage);
	void onDestory(wui::WindowMessage& windowMessage);
	void onClose(wui::WindowMessage& windowMessage);

	void onSize(wui::WindowMessage& windowMessage);
	void onDPIChanged(wui::WindowMessage& windowMessage);
	
	void onCommand(wui::WindowMessage& windowMessage);
	void onTest1(wui::WindowMessage& windowMessage);
	void onTest2(wui::WindowMessage& windowMessage);

public:
	std::wstring getCurrentURL(void);
	void start(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




