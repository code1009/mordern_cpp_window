#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Example2
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MainFrame : public WindowUI::BasicWindow
{
public:
	std::shared_ptr<Window> _View;

public:
	MainFrame();
	virtual ~MainFrame();

public:
	virtual void registerWindowMessageHandler(void) override;
	virtual void initializeWindowClass(void) override;

public:
	void onNcCreate(WindowUI::WindowMessage& windowMessage);
	void onNcDestory(WindowUI::WindowMessage& windowMessage);

	void onCreate(WindowUI::WindowMessage& windowMessage);
	void onDestory(WindowUI::WindowMessage& windowMessage);
	void onClose(WindowUI::WindowMessage& windowMessage);

	void onSize(WindowUI::WindowMessage& windowMessage);

	void onPaint(WindowUI::WindowMessage& windowMessage);

	void onCommand(WindowUI::WindowMessage& windowMessage);
	void onAbout(WindowUI::WindowMessage& windowMessage);
	void onExit(WindowUI::WindowMessage& windowMessage);

public:
	void draw(HDC hdc, RECT& rect);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





