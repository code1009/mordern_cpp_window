#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Example1
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class AboutModelessDialog : public WindowUI::BasicModelessDialog
{
public:
	explicit AboutModelessDialog(HWND hParent):
		WindowUI::BasicModelessDialog{ IDD_ABOUTBOX }
	{
		WindowUI::debugPrintln(L"AboutModelessDialog.ctor() - begin");


		registerWindowMessageHandler();

		createDialog(hParent);
		::ShowWindow(getHandle(), SW_SHOW);

		WindowUI::debugPrintln(L"AboutModelessDialog.ctor() - end");
	}

	~AboutModelessDialog()
	{
		WindowUI::debugPrintln(L"AboutModelessDialog.dtor() - begin");

		WindowUI::debugPrintln(L"AboutModelessDialog.dtor() - end");
	}

	virtual void registerWindowMessageHandler(void) override
	{
		getWindowMessageHandler(WM_INITDIALOG) = [this](WindowUI::WindowMessage& windowMessage)
		{
			onInitDialog();
			defaultWindowMessageHandler(windowMessage);
		};


		getWindowMessageHandler(WM_DESTROY) = [this](WindowUI::WindowMessage& windowMessage) { onDestory(); };
		
		getWindowMessageHandler(WM_CLOSE) = [this](WindowUI::WindowMessage& windowMessage)
		{
			onClose();
		};

		getWindowMessageHandler(WM_COMMAND) = [this](WindowUI::WindowMessage& windowMessage)
		{
			bool rv = onCommand((UINT)HIWORD(windowMessage.wParam), (int)LOWORD(windowMessage.wParam), (HWND)windowMessage.lParam);
			if (!rv)
			{
				defaultWindowMessageHandler(windowMessage);
			}
		};
	}

	void onInitDialog(void)
	{
		WindowUI::debugPrintln(L"AboutModelessDialog.onInitDialog()");
	}

	void onDestory(void)
	{
		WindowUI::debugPrintln(L"AboutModelessDialog.onDestory()");
	}

	void onClose(void)
	{
		WindowUI::debugPrintln(L"AboutModelessDialog.onClose() - begin");

		destroyWindow();

		WindowUI::debugPrintln(L"AboutModelessDialog.onClose() - end");
	}

	bool onCommand(UINT uNotifyCode, int nID, HWND wndCtl)
	{
		switch (nID)
		{
		case IDOK:
			onOK();
			return true;
			break;

		case IDCANCEL:
			onCancel();
			return true;
			break;

		default:
			break;
		}

		return false;
	}

	void onOK(void)
	{
		destroyWindow();
	}

	void onCancel(void)
	{
		destroyWindow();
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




