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
		//-------------------------------------------------------------------
		WindowUI::debugPrintln(L"AboutDialog.ctor() - begin");


		//-------------------------------------------------------------------
		registerWindowMessageHandler();


		//-------------------------------------------------------------------
		WindowUI::debugPrintln(L"AboutDialog.ctor() - end");
	}

	~AboutDialog()
	{
		//-------------------------------------------------------------------
		WindowUI::debugPrintln(L"AboutDialog.dtor() - begin");


		//-------------------------------------------------------------------


		//-------------------------------------------------------------------
		WindowUI::debugPrintln(L"AboutDialog.dtor() - end");
	}

	virtual void registerWindowMessageHandler(void) override
	{
		getWindowMessageHandler(WM_INITDIALOG) = [this](WindowUI::WindowMessage& windowMessage) { onInitDialog(windowMessage); };
		getWindowMessageHandler(WM_DESTROY   ) = [this](WindowUI::WindowMessage& windowMessage) { onDestory(windowMessage); };
		getWindowMessageHandler(WM_COMMAND   ) = [this](WindowUI::WindowMessage& windowMessage) { onCommand(windowMessage); };
	}

	void onInitDialog(WindowUI::WindowMessage& windowMessage)
	{
		//-------------------------------------------------------------------
		WindowUI::debugPrintln(L"AboutDialog.onInitDialog()");


		//-------------------------------------------------------------------
		defaultWindowMessageHandler(windowMessage);
	}

	void onDestory(WindowUI::WindowMessage& windowMessage)
	{
		//-------------------------------------------------------------------
		WindowUI::debugPrintln(L"AboutDialog.onDestory()");
	}

	void onCommand(WindowUI::WindowMessage& windowMessage)
	{
		WindowUI::WM_COMMAND_WindowMessageManipulator windowMessageManipulator(&windowMessage);


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

	void onOK(WindowUI::WindowMessage& windowMessage)
	{
		endDialog(IDOK);
	}

	void onCancel(WindowUI::WindowMessage& windowMessage)
	{
		endDialog(IDCANCEL);
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




