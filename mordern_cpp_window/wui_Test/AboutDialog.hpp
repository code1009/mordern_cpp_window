#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui_Test
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class AboutDialog : public wui::BasicModalDialog
{
public:
	AboutDialog():
		wui::BasicModalDialog{ IDD_ABOUTBOX }
	{
		wui::debugPrintln(L"AboutDialog.ctor() - begin");


		registerWindowMessageHandler();


		wui::debugPrintln(L"AboutDialog.ctor() - end");
	}

	~AboutDialog()
	{
		wui::debugPrintln(L"AboutDialog.dtor() - begin");

		wui::debugPrintln(L"AboutDialog.dtor() - end");
	}

	virtual void registerWindowMessageHandler(void) override
	{
		getWindowMessageHandler(WM_INITDIALOG) = [this](wui::WindowMessage* windowMessage)
		{
			onInitDialog();
			defaultWindowMessageHandler(windowMessage);
		};


		getWindowMessageHandler(WM_DESTROY) = [this](wui::WindowMessage* windowMessage) { onDestory(); };


		getWindowMessageHandler(WM_COMMAND) = [this](wui::WindowMessage* windowMessage)
			{
				// void OnCommand(UINT uNotifyCode, int nID, CWindow wndCtl)
				// func((UINT)HIWORD(wParam), (int)LOWORD(wParam), (HWND)lParam);
				bool rv = onCommand((UINT)HIWORD(windowMessage->wParam), (int)LOWORD(windowMessage->wParam), (HWND)windowMessage->lParam);
				if (!rv)
				{
					defaultWindowMessageHandler(windowMessage);
				}
			};
	}

	void onInitDialog(void)
	{
		wui::debugPrintln(L"AboutDialog.onInitDialog()");
	}

	void onDestory(void)
	{
		wui::debugPrintln(L"AboutDialog.onDestory()");
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
		endDialog(IDOK);
	}

	void onCancel(void)
	{
		endDialog(IDCANCEL);
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




