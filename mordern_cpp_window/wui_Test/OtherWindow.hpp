#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui_Test
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class OtherWindow : public wui::BasicWindow
{
public:
	OtherWindow()
	{
		wui::debugPrintln(L"OtherWindow.ctor() - begin");


		registerWindowMessageHandler();


		initializeWindowClass();
		registerWindowClass();
		createWindow();


		::ShowWindow(getHandle(), SW_SHOW);
		::UpdateWindow(getHandle());


		wui::debugPrintln(L"OtherWindow.ctor() - end");
	}

	~OtherWindow()
	{
		wui::debugPrintln(L"OtherWindow.dtor() - begin");

		destroyWindow();

		wui::debugPrintln(L"OtherWindow.dtor() - end");
	}

	virtual void registerWindowMessageHandler(void) override
	{
		getWindowMessageHandler(WM_CREATE) = [this](wui::WindowMessage& windowMessage)
		{
			// 생성자에서 이 영역을 호출 중이다.
			SetWindowTextW(windowMessage.hWnd, L"OtherWindow");
			defaultWindowMessageHandler(windowMessage);
		}
		;

		getWindowMessageHandler(WM_CLOSE) = [this](wui::WindowMessage& windowMessage) { onClose(); };
		getWindowMessageHandler(WM_DESTROY) = [this](wui::WindowMessage& windowMessage) { onDestory(); };
	}

	void onClose(void)
	{
		wui::debugPrintln(L"OtherWindow.onClose() - begin");

		destroyWindow();

		wui::debugPrintln(L"OtherWindow.onClose() - end");
	}

	void onDestory(void)
	{
		wui::debugPrintln(L"OtherWindow.onDestory()");
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




