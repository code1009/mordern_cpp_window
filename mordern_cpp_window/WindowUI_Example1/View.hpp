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
	explicit View(
		HWND hParent, 
		const RECT& rect, 
		DWORD style= WS_CHILD | WS_VISIBLE | WS_BORDER, 
		DWORD styleEx = WS_EX_CLIENTEDGE
	)
	{
		//-----------------------------------------------------------------------
		WindowUI::debugPrintln(L"View.ctor() - begin");


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
			windowText.c_str(),
			style, styleEx,
			rect.left, rect.top, rect.right, rect.bottom,
			hParent
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
		WindowUI::debugPrintln(text);


		//-----------------------------------------------------------------------
		WindowUI::debugPrintln(L"View.ctor() - end");
	}

	~View()
	{
		WindowUI::debugPrintln(L"View.dtor() - begin");
		WindowUI::debugPrintln(L"View.dtor() - end");
	}

	virtual void registerWindowMessageHandler(void) override
	{
		getWindowMessageHandler(WM_CREATE ) = [this](WindowUI::WindowMessage& windowMessage) { onCreate(windowMessage); };
		getWindowMessageHandler(WM_DESTROY) = [this](WindowUI::WindowMessage& windowMessage) { onDestory(windowMessage); };
		getWindowMessageHandler(WM_CLOSE  ) = [this](WindowUI::WindowMessage& windowMessage) { onClose(windowMessage); };
		getWindowMessageHandler(WM_PAINT  ) = [this](WindowUI::WindowMessage& windowMessage) { onPaint(windowMessage); };
	}

	void onCreate(WindowUI::WindowMessage& windowMessage)
	{
		//-----------------------------------------------------------------------
		WindowUI::debugPrintln(L"View.onCreate() - begin");


		//-----------------------------------------------------------------------
		//SetWindowTextW(windowMessage.hWnd, L"View");

		defaultWindowMessageHandler(windowMessage);


		//-----------------------------------------------------------------------
		WindowUI::debugPrintln(L"View.onCreate() - end");
	}

	void onDestory(WindowUI::WindowMessage& windowMessage)
	{
		WindowUI::debugPrintln(L"View.onDestory()");
	}

	void onClose(WindowUI::WindowMessage& windowMessage)
	{
		//-----------------------------------------------------------------------
		WindowUI::debugPrintln(L"View.onClose() - begin");


		//-----------------------------------------------------------------------
		WindowUI::debugPrintln(L"View.onClose() - end");
	}

	void onPaint(WindowUI::WindowMessage& windowMessage)
	{
		//-----------------------------------------------------------------------
		WindowUI::debugPrintln(L"View.onPaint() - begin");


		//-----------------------------------------------------------------------
		RECT rect;


		GetClientRect(getHandle(), &rect);


		PAINTSTRUCT ps;


		HDC hdc = BeginPaint(getHandle(), &ps);


		draw(hdc, rect);


		EndPaint(getHandle(), &ps);


		//-----------------------------------------------------------------------
		WindowUI::debugPrintln(L"View.onPaint() - end");
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




