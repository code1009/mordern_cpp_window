/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"
#include "../res/resource.h"

#include "../wui/WindowFunction.hpp"
#include "../wui/Core.hpp"
#include "../wui/WindowMessageManipulator.hpp"

#include "WebView.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
/*
.vcxproj
<Project>

...

  <ImportGroup Label="ExtensionTargets">
    <Import Project="..\packages\Microsoft.Windows.ImplementationLibrary.1.0.191107.2\build\native\Microsoft.Windows.ImplementationLibrary.targets" Condition="Exists('..\packages\Microsoft.Windows.ImplementationLibrary.1.0.191107.2\build\native\Microsoft.Windows.ImplementationLibrary.targets')" />
    <Import Project="..\packages\Microsoft.Web.WebView2.1.0.902.49\build\native\Microsoft.Web.WebView2.targets" Condition="Exists('..\packages\Microsoft.Web.WebView2.1.0.902.49\build\native\Microsoft.Web.WebView2.targets')" />
  </ImportGroup>
  <Target Name="EnsureNuGetPackageBuildImports" BeforeTargets="PrepareForBuild">
    <PropertyGroup>
      <ErrorText>This project references NuGet package(s) that are missing on this computer. Use NuGet Package Restore to download them.  For more information, see http://go.microsoft.com/fwlink/?LinkID=322105. The missing file is {0}.</ErrorText>
    </PropertyGroup>
    <Error Condition="!Exists('..\packages\Microsoft.Windows.ImplementationLibrary.1.0.191107.2\build\native\Microsoft.Windows.ImplementationLibrary.targets')" Text="$([System.String]::Format('$(ErrorText)', '..\packages\Microsoft.Windows.ImplementationLibrary.1.0.191107.2\build\native\Microsoft.Windows.ImplementationLibrary.targets'))" />
    <Error Condition="!Exists('..\packages\Microsoft.Web.WebView2.1.0.902.49\build\native\Microsoft.Web.WebView2.targets')" Text="$([System.String]::Format('$(ErrorText)', '..\packages\Microsoft.Web.WebView2.1.0.902.49\build\native\Microsoft.Web.WebView2.targets'))" />
  </Target>
</Project>
*/





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui_Example3
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WebView::WebView(
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
	windowText = L"WebView";
	hwnd = createWindow(
		hParent,
		windowText.c_str(),
		static_cast<DWORD>(style),
		static_cast<DWORD>(styleEx),
		rect.left, rect.top, rect.right, rect.bottom
	);
	if (!hwnd)
	{
		throw std::wstring(L"WebView::WebView(): createWindow() failed");
	}


	//-----------------------------------------------------------------------
	start();


	//-----------------------------------------------------------------------
	::ShowWindow(getHandle(), SW_SHOW);
	::UpdateWindow(getHandle());


	//-----------------------------------------------------------------------
	std::wstring text;


	text = getWindowText(this);
	text = L"WebView";
	setWindowText(this, text);
	text = getWindowText(this);
	wui::debugPrintln(text);
}

WebView::~WebView()
{
}

void WebView::registerWindowMessageHandler(void)
{
	getWindowMessageHandler(WM_CREATE) = [this](wui::WindowMessage& windowMessage) { onCreate(windowMessage); };
	getWindowMessageHandler(WM_DESTROY) = [this](wui::WindowMessage& windowMessage) { onDestory(windowMessage); };
	getWindowMessageHandler(WM_CLOSE) = [this](wui::WindowMessage& windowMessage) { onClose(windowMessage); };
	getWindowMessageHandler(WM_SIZE) = [this](wui::WindowMessage& windowMessage) { onSize(windowMessage); };
	getWindowMessageHandler(WM_DPICHANGED) = [this](wui::WindowMessage& windowMessage) { onDPIChanged(windowMessage); };
	getWindowMessageHandler(WM_COMMAND) = [this](wui::WindowMessage& windowMessage) { onCommand(windowMessage); };
}

void WebView::onCreate(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	//SetWindowTextW(windowMessage.hWnd, L"WebView");


	defaultWindowMessageHandler(windowMessage);
}

void WebView::onDestory(wui::WindowMessage& windowMessage)
{
}

void WebView::onClose(wui::WindowMessage& windowMessage)
{
}

void WebView::onSize(wui::WindowMessage& windowMessage)
{
	//-----------------------------------------------------------------------
	wui::WM_SIZE_WindowMessageManipulator windowMessageManipulator(&windowMessage);


	//-----------------------------------------------------------------------
	RECT rect;


	if (m_controller != nullptr)
	{
		::GetClientRect(getHandle(), &rect);

		m_controller->put_Bounds(rect);
	}
}

void WebView::onDPIChanged(wui::WindowMessage& windowMessage)
{
	RECT* pWindowRect = reinterpret_cast<RECT*>(windowMessage.lParam);


	wui::setWindowPos(this, HWND_TOP, *pWindowRect, SWP_SHOWWINDOW);
}

void WebView::onCommand(wui::WindowMessage& windowMessage)
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

void WebView::onTest1(wui::WindowMessage& windowMessage)
{

}

void WebView::onTest2(wui::WindowMessage& windowMessage)
{
}

std::wstring WebView::getCurrentURL(void)
{
	//------------------------------------------------------------------------
	WCHAR szModuleFilePath[MAX_PATH] = { 0 };


	GetModuleFileNameW(NULL, szModuleFilePath, MAX_PATH);


	//------------------------------------------------------------------------
	WCHAR szURL[MAX_PATH] = { 0 };


	wsprintfW(szURL, L"res://%s/%d", szModuleFilePath, IDR_HTML1);


	//------------------------------------------------------------------------

	return std::wstring(szURL);
}

void WebView::start(void)
{
	std::wstring dataDirectory;


	dataDirectory =
		L"C:\\Users\\USER\\AppData\\Roaming\\Win32++\\EdgeBrowser";

	// Use a lambda and callback to create the core web environment.
	CreateCoreWebView2EnvironmentWithOptions(nullptr, dataDirectory.c_str(), nullptr,
		Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2EnvironmentCompletedHandler>(
			[this](HRESULT, ICoreWebView2Environment* env) -> HRESULT
			{
				// Use a lambda and callback to create the core web controller.
				env->CreateCoreWebView2Controller(getHandle(), Microsoft::WRL::Callback<ICoreWebView2CreateCoreWebView2ControllerCompletedHandler>(
					[this](HRESULT, ICoreWebView2Controller* controller) -> HRESULT
					{
						if (controller != nullptr)
						{
							// Retrieve the web view from the controller.
							m_controller = controller;
							m_controller->get_CoreWebView2(&m_webView);

							// Resize WebView to fit the bounds of the parent window
							RECT rect;


							::GetClientRect(getHandle(), &rect);
							m_controller->put_Bounds(rect);

							// Navigate to a web site.
							//m_webView->Navigate(L"https://www.google.com/");
							m_webView->Navigate(getCurrentURL().c_str());
							
						}
						return S_OK;
					}).Get());
				return S_OK;
			}).Get());

// https://stackoverflow.com/questions/72104836/can-webview2-navigate-to-an-html-resource-embedded-in-the-application
/*
WebView2 does not support the res URI scheme.
                              ~~~
For serving app content that is not on the disk, 

you can use :

NavigateToString: 
You can provide app created HTML to render, 
however there is no way to additionally reference subresources 
that are dynamically app created.

WebResourceRequested : 
You can use the CoreWebView2.WebResourceRequested event to intercept any resource requests 
that you want after setting the filter via AddWebResourceRequestedFilter.
In this event you can intercept any resource request and decide to supply your own response stream rather
than allowing the request to actually go to the network.
You could use these both together, using NavigateToString to supply the initial HTML to render,
refer to subresources on a particular domain like app.example in that HTML,
and then in WebResourceRequested intercept all requests to app.example and provide your own stream.
*/

//https://github.com/MicrosoftEdge/WebView2Samples/blob/02a1ccb54b6994a0fb7da7ce8a54a1825185b08e/SampleApps/WebView2APISample/SettingsComponent.cpp#L1556


}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




