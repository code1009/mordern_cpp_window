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


		::ShowWindow(_Handle, SW_SHOW);
		::UpdateWindow(_Handle);


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
		_WindowMessageHandlerMap[WM_CREATE] = [this](WindowMessage& windowMessage)
		{
			// _Wnd는 아직 CreateWindowExW()함수가 끝나지 않은 상태 이므로,
			// _Wnd는 nullptr이다.
			// 또한, 생성자에서 이 영역을 호출 중이다.
			SetWindowTextW(windowMessage.hWnd, L"OtherWindow");
			callDefWindowProc(windowMessage);
		}
		;

		_WindowMessageHandlerMap[WM_CLOSE] = [this](WindowMessage& windowMessage) { onClose(); };
		_WindowMessageHandlerMap[WM_DESTROY] = [this](WindowMessage& windowMessage) { onDestory(); };
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
