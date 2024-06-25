#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Example1
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class View : public WindowUI::BasicWindow
{
public:
	explicit View(HWND hParent)
	{
		WindowUI::debugPrintln(L"View.ctor() - begin");


		registerWindowMessageHandler();


		initializeWindowClass();
		registerWindowClass();
		createWindow();


		::ShowWindow(getHandle(), SW_SHOW);
		::UpdateWindow(getHandle());


		WindowUI::debugPrintln(L"View.ctor() - end");
	}

	~View()
	{
		WindowUI::debugPrintln(L"View.dtor() - begin");

		destroyWindow();

		WindowUI::debugPrintln(L"View.dtor() - end");
	}

	virtual void registerWindowMessageHandler(void) override
	{
		getWindowMessageHandler(WM_CREATE) = [this](WindowUI::WindowMessage& windowMessage)
		{
			SetWindowTextW(windowMessage.hWnd, L"View");
			defaultWindowMessageHandler(windowMessage);
		}
		;

		getWindowMessageHandler(WM_CLOSE) = [this](WindowUI::WindowMessage& windowMessage) { onClose(); };
		getWindowMessageHandler(WM_DESTROY) = [this](WindowUI::WindowMessage& windowMessage) { onDestory(); };
	}

	void onClose(void)
	{
		WindowUI::debugPrintln(L"View.onClose() - begin");
		WindowUI::debugPrintln(L"View.onClose() - end");
	}

	void onDestory(void)
	{
		WindowUI::debugPrintln(L"View.onDestory()");
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




