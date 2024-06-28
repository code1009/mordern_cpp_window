#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui_Test
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class AboutModelessDialog : public wui::BasicModelessDialog
{
public:
	explicit AboutModelessDialog(HWND hParent):
		wui::BasicModelessDialog{ IDD_ABOUTBOX }
	{
		wui::debugPrintln(L"AboutModelessDialog.ctor() - begin");


		registerWindowMessageHandler();

		createDialog(hParent);
		::ShowWindow(getHandle(), SW_SHOW);

		wui::debugPrintln(L"AboutModelessDialog.ctor() - end");
	}

	~AboutModelessDialog()
	{
		wui::debugPrintln(L"AboutModelessDialog.dtor() - begin");

		wui::debugPrintln(L"AboutModelessDialog.dtor() - end");
	}

	virtual void registerWindowMessageHandler(void) override
	{
		getWindowMessageHandler(WM_INITDIALOG) = [this](wui::WindowMessage& windowMessage)
		{
			onInitDialog();
			defaultWindowMessageHandler(windowMessage);
		};


		getWindowMessageHandler(WM_DESTROY) = [this](wui::WindowMessage& windowMessage) { onDestory(); };
		
		getWindowMessageHandler(WM_CLOSE) = [this](wui::WindowMessage& windowMessage)
		{
			onClose();
		};

		getWindowMessageHandler(WM_COMMAND) = [this](wui::WindowMessage& windowMessage)
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
		wui::debugPrintln(L"AboutModelessDialog.onInitDialog()");
	}

	void onDestory(void)
	{
		wui::debugPrintln(L"AboutModelessDialog.onDestory()");
	}

	void onClose(void)
	{
		wui::debugPrintln(L"AboutModelessDialog.onClose() - begin");

		destroyWindow();

		wui::debugPrintln(L"AboutModelessDialog.onClose() - end");
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




