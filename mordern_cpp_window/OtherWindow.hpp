#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class OtherWindow : public Window
{
public:
	OtherWindow()
	{
		print("OtherWindow.ctor() - begin");

		registerWindowMessageHandler();

		registerWindowClass();
		createWindow();
		::ShowWindow(_hWnd, SW_SHOW);

		print("OtherWindow.ctor() - end");
	}

	~OtherWindow()
	{
		print("OtherWindow.dtor() - begin");

		destroyWindow();

		print("OtherWindow.dtor() - end");
	}

	virtual void registerWindowMessageHandler(void) override
	{
		_WindowMessageHandlerMap[WM_CREATE] = [this](WindowMessage& windowMessage)
		{
			// _Wnd�� ���� CreateWindowExW()�Լ��� ������ ���� ���� �̹Ƿ�,
			// _Wnd�� nullptr�̴�.
			// ����, �����ڿ��� �� ������ ȣ�� ���̴�.
			SetWindowTextW(windowMessage.hWnd, L"OtherWindow");
			callDefaultWindowProc(windowMessage);
		}
		;

		_WindowMessageHandlerMap[WM_CLOSE] = [this](WindowMessage& windowMessage) { onClose(); };
		_WindowMessageHandlerMap[WM_DESTROY] = [this](WindowMessage& windowMessage) { onDestory(); };
	}

	void onClose(void)
	{
		print("OtherWindow.onClose() - begin");

		destroyWindow();

		print("OtherWindow.onClose() - end");
	}

	void onDestory(void)
	{
		print("OtherWindow.onDestory()");
	}
};
