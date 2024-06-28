#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui_Test
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class View : public wui::BasicWindow
{
public:
	explicit View(HWND hParent)
	{
		wui::debugPrintln(L"View.ctor() - begin");


		registerWindowMessageHandler();


		initializeWindowClass();
		registerWindowClass();
		createWindow(hParent, L"View", WS_CHILD| WS_VISIBLE, 0, 0, 0, 0, 0);


		::ShowWindow(getHandle(), SW_SHOW);
		::UpdateWindow(getHandle());


		std::wstring text = getWindowText(this);
		wui::debugPrintln(text);


		wui::debugPrintln(L"View.ctor() - end");
	}

	~View()
	{
		wui::debugPrintln(L"View.dtor() - begin");

		wui::debugPrintln(L"View.dtor() - end");
	}

	virtual void registerWindowMessageHandler(void) override
	{
		getWindowMessageHandler(WM_CREATE) = [this](wui::WindowMessage* windowMessage)
		{
			SetWindowTextW(windowMessage->hWnd, L"View");
			defaultWindowMessageHandler(windowMessage);
		}
		;

		getWindowMessageHandler(WM_CLOSE) = [this](wui::WindowMessage* windowMessage) { onClose(windowMessage); };
		getWindowMessageHandler(WM_DESTROY) = [this](wui::WindowMessage* windowMessage) { onDestory(windowMessage); };

		getWindowMessageHandler(WM_PAINT) = [this](wui::WindowMessage* windowMessage) { onPaint(windowMessage); };
	}

	void onClose(wui::WindowMessage* windowMessage)
	{
		wui::debugPrintln(L"View.onClose() - begin");
		wui::debugPrintln(L"View.onClose() - end");
	}

	void onDestory(wui::WindowMessage* windowMessage)
	{
		wui::debugPrintln(L"View.onDestory()");
	}

	void onPaint(wui::WindowMessage* windowMessage)
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




