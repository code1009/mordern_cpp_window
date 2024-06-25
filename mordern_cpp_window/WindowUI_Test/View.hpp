#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Test
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
		createWindow(L"View", WS_CHILD| WS_VISIBLE, 0, 0, 0, 0, 0, hParent);


		::ShowWindow(getHandle(), SW_SHOW);
		::UpdateWindow(getHandle());


		std::wstring text = getWindowText(this);
		WindowUI::debugPrintln(text);


		WindowUI::debugPrintln(L"View.ctor() - end");
	}

	~View()
	{
		WindowUI::debugPrintln(L"View.dtor() - begin");

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

		getWindowMessageHandler(WM_CLOSE) = [this](WindowUI::WindowMessage& windowMessage) { onClose(windowMessage); };
		getWindowMessageHandler(WM_DESTROY) = [this](WindowUI::WindowMessage& windowMessage) { onDestory(windowMessage); };

		getWindowMessageHandler(WM_PAINT) = [this](WindowUI::WindowMessage& windowMessage) { onPaint(windowMessage); };
	}

	void onClose(WindowUI::WindowMessage& windowMessage)
	{
		WindowUI::debugPrintln(L"View.onClose() - begin");
		WindowUI::debugPrintln(L"View.onClose() - end");
	}

	void onDestory(WindowUI::WindowMessage& windowMessage)
	{
		WindowUI::debugPrintln(L"View.onDestory()");
	}

	void onPaint(WindowUI::WindowMessage& windowMessage)
	{
		PAINTSTRUCT ps;


		HDC hdc = BeginPaint(getHandle(), &ps);
		RECT rect{ 0,0, 500, 100 };
		HBRUSH hbr;


		hbr = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);


		FillRect(hdc, &rect, hbr);
		DrawText(hdc, L"View", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		EndPaint(getHandle(), &ps);
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




