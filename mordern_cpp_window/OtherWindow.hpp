#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class OtherWindow : public BaseWindow
{
public:
	OtherWindow()
	{
		debugPrintln(L"OtherWindow.ctor() - begin");


		registerWindowMessageHandler();


		initializeWindowClass();
		registerWindowClass();
		createWindow();


		::ShowWindow(getHandle(), SW_SHOW);
		::UpdateWindow(getHandle());


		debugPrintln(L"OtherWindow.ctor() - end");
	}

	~OtherWindow()
	{
		debugPrintln(L"OtherWindow.dtor() - begin");

		destroyWindow();

		debugPrintln(L"OtherWindow.dtor() - end");
	}

	virtual void registerWindowMessageHandler(void) override
	{
		getWindowMessageHandler(WM_CREATE) = [this](WindowMessage& windowMessage)
		{
			// 생성자에서 이 영역을 호출 중이다.
			SetWindowTextW(windowMessage.hWnd, L"OtherWindow");
			defaultWindowMessageHandler(windowMessage);
		}
		;

		getWindowMessageHandler(WM_CLOSE) = [this](WindowMessage& windowMessage) { onClose(); };
		getWindowMessageHandler(WM_DESTROY) = [this](WindowMessage& windowMessage) { onDestory(); };
	}

	void onClose(void)
	{
		debugPrintln(L"OtherWindow.onClose() - begin");

		destroyWindow();

		debugPrintln(L"OtherWindow.onClose() - end");
	}

	void onDestory(void)
	{
		debugPrintln(L"OtherWindow.onDestory()");
	}
};
