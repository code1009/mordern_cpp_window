#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Example2
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class View : public WindowUI::BasicWindow
{
public:
	explicit View(
		HWND hParent,
		const RECT& rect,
		std::uint32_t style = WS_CHILD | WS_VISIBLE | WS_BORDER,
		std::uint32_t styleEx = WS_EX_CLIENTEDGE
	);

	~View();

public:
	virtual void registerWindowMessageHandler(void) override;

public:
	void onCreate(WindowUI::WindowMessage& windowMessage);
	void onDestory(WindowUI::WindowMessage& windowMessage);
	void onClose(WindowUI::WindowMessage& windowMessage);
	void onPaint(WindowUI::WindowMessage& windowMessage);
	void draw(HDC hdc, RECT& rect);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




