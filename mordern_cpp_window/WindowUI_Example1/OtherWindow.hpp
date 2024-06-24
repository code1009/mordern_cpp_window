#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Example1
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class OtherWindow : public WindowUI::BasicWindow
{
public:
	OtherWindow()
	{
		WindowUI::debugPrintln(L"OtherWindow.ctor() - begin");


		registerWindowMessageHandler();


		initializeWindowClass();
		registerWindowClass();
		createWindow();


		::ShowWindow(getHandle(), SW_SHOW);
		::UpdateWindow(getHandle());


		WindowUI::debugPrintln(L"OtherWindow.ctor() - end");
	}

	~OtherWindow()
	{
		WindowUI::debugPrintln(L"OtherWindow.dtor() - begin");

		destroyWindow();

		WindowUI::debugPrintln(L"OtherWindow.dtor() - end");
	}

	virtual void registerWindowMessageHandler(void) override
	{
		getWindowMessageHandler(WM_CREATE) = [this](WindowUI::WindowMessage& windowMessage)
		{
			// 생성자에서 이 영역을 호출 중이다.
			SetWindowTextW(windowMessage.hWnd, L"OtherWindow");
			defaultWindowMessageHandler(windowMessage);
		}
		;

		getWindowMessageHandler(WM_CLOSE) = [this](WindowUI::WindowMessage& windowMessage) { onClose(); };
		getWindowMessageHandler(WM_DESTROY) = [this](WindowUI::WindowMessage& windowMessage) { onDestory(); };
	}

	void onClose(void)
	{
		WindowUI::debugPrintln(L"OtherWindow.onClose() - begin");

		destroyWindow();

		WindowUI::debugPrintln(L"OtherWindow.onClose() - end");
	}

	void onDestory(void)
	{
		WindowUI::debugPrintln(L"OtherWindow.onDestory()");
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




