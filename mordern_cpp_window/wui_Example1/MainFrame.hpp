#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui_Example1
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MainFrame : public wui::BasicWindow
{
public:
	std::shared_ptr<View> _View;

public:
	MainFrame();
	virtual ~MainFrame();

public:
	virtual void registerWindowMessageHandler(void) override;
	virtual void initializeWindowClass(void) override;

public:
	void onNcCreate(wui::WindowMessage* windowMessage);
	void onNcDestory(wui::WindowMessage* windowMessage);

	void onCreate(wui::WindowMessage* windowMessage);
	void onDestory(wui::WindowMessage* windowMessage);
	void onClose(wui::WindowMessage* windowMessage);

	void onSize(wui::WindowMessage* windowMessage);

	void onPaint(wui::WindowMessage* windowMessage);

	void onCommand(wui::WindowMessage* windowMessage);
	void onAbout(wui::WindowMessage* windowMessage);

public:
	void draw(HDC hdc, RECT& rect);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





