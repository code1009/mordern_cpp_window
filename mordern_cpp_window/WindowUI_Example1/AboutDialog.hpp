#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Example1
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class AboutDialog : public WindowUI::BasicModalDialog
{
public:
	AboutDialog():
		WindowUI::BasicModalDialog{ IDD_ABOUTBOX }
	{
		WindowUI::debugPrintln(L"AboutDialog.ctor() - begin");


		registerWindowMessageHandler();


		WindowUI::debugPrintln(L"AboutDialog.ctor() - end");
	}

	~AboutDialog()
	{
		WindowUI::debugPrintln(L"AboutDialog.dtor() - begin");

		WindowUI::debugPrintln(L"AboutDialog.dtor() - end");
	}

	virtual void registerWindowMessageHandler(void) override
	{
		getWindowMessageHandler(WM_INITDIALOG) = [this](WindowUI::WindowMessage& windowMessage)
		{
			onInitDialog();
			defaultWindowMessageHandler(windowMessage);
		};


		getWindowMessageHandler(WM_DESTROY) = [this](WindowUI::WindowMessage& windowMessage) { onDestory(); };


		getWindowMessageHandler(WM_COMMAND) = [this](WindowUI::WindowMessage& windowMessage)
			{
				// void OnCommand(UINT uNotifyCode, int nID, CWindow wndCtl)
				// func((UINT)HIWORD(wParam), (int)LOWORD(wParam), (HWND)lParam);
				bool rv = onCommand((UINT)HIWORD(windowMessage.wParam), (int)LOWORD(windowMessage.wParam), (HWND)windowMessage.lParam);
				if (!rv)
				{
					defaultWindowMessageHandler(windowMessage);
				}
			};
	}

	void onInitDialog(void)
	{
		WindowUI::debugPrintln(L"AboutDialog.onInitDialog()");
	}

	void onDestory(void)
	{
		WindowUI::debugPrintln(L"AboutDialog.onDestory()");
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




