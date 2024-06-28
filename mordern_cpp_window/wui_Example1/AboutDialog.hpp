#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui_Example1
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class AboutDialog : public wui::BasicModalDialog
{
public:
	AboutDialog():
		wui::BasicModalDialog{ IDD_ABOUTBOX }
	{
		//-------------------------------------------------------------------
		wui::debugPrintln(L"AboutDialog.ctor() - begin");


		//-------------------------------------------------------------------
		registerWindowMessageHandler();


		//-------------------------------------------------------------------
		wui::debugPrintln(L"AboutDialog.ctor() - end");
	}

	~AboutDialog()
	{
		//-------------------------------------------------------------------
		wui::debugPrintln(L"AboutDialog.dtor() - begin");


		//-------------------------------------------------------------------


		//-------------------------------------------------------------------
		wui::debugPrintln(L"AboutDialog.dtor() - end");
	}

	virtual void registerWindowMessageHandler(void) override
	{
		getWindowMessageHandler(WM_INITDIALOG) = [this](wui::WindowMessage& windowMessage) { onInitDialog(windowMessage); };
		getWindowMessageHandler(WM_DESTROY   ) = [this](wui::WindowMessage& windowMessage) { onDestory(windowMessage); };
		getWindowMessageHandler(WM_COMMAND   ) = [this](wui::WindowMessage& windowMessage) { onCommand(windowMessage); };
	}

	void onInitDialog(wui::WindowMessage& windowMessage)
	{
		//-------------------------------------------------------------------
		wui::debugPrintln(L"AboutDialog.onInitDialog()");


		//-------------------------------------------------------------------
		defaultWindowMessageHandler(windowMessage);
	}

	void onDestory(wui::WindowMessage& windowMessage)
	{
		//-------------------------------------------------------------------
		wui::debugPrintln(L"AboutDialog.onDestory()");
	}

	void onCommand(wui::WindowMessage& windowMessage)
	{
		wui::WM_COMMAND_WindowMessageManipulator windowMessageManipulator(&windowMessage);


		switch (windowMessageManipulator.nID())
		{
		case IDOK:
			onOK(windowMessage);
			return;
			break;

		case IDCANCEL:
			onCancel(windowMessage);
			return;
			break;

		default:
			break;
		}


		defaultWindowMessageHandler(windowMessage);
	}

	void onOK(wui::WindowMessage& windowMessage)
	{
		endDialog(IDOK);
	}

	void onCancel(wui::WindowMessage& windowMessage)
	{
		endDialog(IDCANCEL);
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




