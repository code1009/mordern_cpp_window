#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui_Example1
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class View : public wui::BasicWindow
{
public:
	explicit View(
		HWND hParent, 
		const RECT& rect, 
		std::uint32_t style= WS_CHILD | WS_VISIBLE | WS_BORDER, 
		std::uint32_t styleEx = WS_EX_CLIENTEDGE
	)
	{
		//-----------------------------------------------------------------------
		wui::debugPrintln(L"View.ctor() - begin");


		//-----------------------------------------------------------------------
		registerWindowMessageHandler();


		//-----------------------------------------------------------------------
		initializeWindowClass();
		registerWindowClass();


		//-----------------------------------------------------------------------
		std::wstring windowText;
		HWND hwnd;


		windowText = L"View";
		hwnd = createWindow(
			hParent,
			windowText.c_str(),
			static_cast<DWORD>(style),
			static_cast<DWORD>(styleEx),
			rect.left, rect.top, rect.right, rect.bottom
		);
		if (!hwnd)
		{
			throw std::wstring(L"View::View(): createWindow() failed");
		}


		//-----------------------------------------------------------------------
		::ShowWindow(getHandle(), SW_SHOW);
		::UpdateWindow(getHandle());


		//-----------------------------------------------------------------------
		std::wstring text;
		
		
		text = getWindowText(this);
		text = L"View Window";
		setWindowText(this, text);
		text = getWindowText(this);
		wui::debugPrintln(text);


		//-----------------------------------------------------------------------
		wui::debugPrintln(L"View.ctor() - end");
	}

	~View()
	{
		wui::debugPrintln(L"View.dtor() - begin");
		wui::debugPrintln(L"View.dtor() - end");
	}

	virtual void registerWindowMessageHandler(void) override
	{
		getWindowMessageHandler(WM_CREATE ) = [this](wui::WindowMessage& windowMessage) { onCreate(windowMessage); };
		getWindowMessageHandler(WM_DESTROY) = [this](wui::WindowMessage& windowMessage) { onDestory(windowMessage); };
		getWindowMessageHandler(WM_CLOSE  ) = [this](wui::WindowMessage& windowMessage) { onClose(windowMessage); };
		getWindowMessageHandler(WM_PAINT  ) = [this](wui::WindowMessage& windowMessage) { onPaint(windowMessage); };
	}

	void onCreate(wui::WindowMessage& windowMessage)
	{
		//-----------------------------------------------------------------------
		wui::debugPrintln(L"View.onCreate() - begin");


		//-----------------------------------------------------------------------
		//SetWindowTextW(windowMessage.hWnd, L"View");

		defaultWindowMessageHandler(windowMessage);


		//-----------------------------------------------------------------------
		wui::debugPrintln(L"View.onCreate() - end");
	}

	void onDestory(wui::WindowMessage& windowMessage)
	{
		wui::debugPrintln(L"View.onDestory()");
	}

	void onClose(wui::WindowMessage& windowMessage)
	{
		//-----------------------------------------------------------------------
		wui::debugPrintln(L"View.onClose() - begin");


		//-----------------------------------------------------------------------
		wui::debugPrintln(L"View.onClose() - end");
	}

	void onPaint(wui::WindowMessage& windowMessage)
	{
		//-----------------------------------------------------------------------
		wui::debugPrintln(L"View.onPaint() - begin");


		//-----------------------------------------------------------------------
		RECT rect;


		GetClientRect(getHandle(), &rect);


		PAINTSTRUCT ps;


		HDC hdc = BeginPaint(getHandle(), &ps);


		draw(hdc, rect);


		EndPaint(getHandle(), &ps);


		//-----------------------------------------------------------------------
		wui::debugPrintln(L"View.onPaint() - end");
	}

	void draw(HDC hdc, RECT& rect)
	{
		HBRUSH hbr;


		hbr = reinterpret_cast<HBRUSH>(COLOR_BTNFACE + 1);


		FillRect(hdc, &rect, hbr);
		SetBkMode(hdc, TRANSPARENT);
		DrawText(hdc, L"View", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	}
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




