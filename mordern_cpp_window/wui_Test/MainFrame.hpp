#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui_Test
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MainFrame : public wui::BasicWindow
{
public:
	std::shared_ptr<AboutModelessDialog> _AboutModelessDialog;
	std::shared_ptr<View> _View;

public:
	MainFrame();
	virtual ~MainFrame();

public:
	virtual void registerWindowMessageHandler(void) override;
	virtual void initializeWindowClass(void) override;

public:
	void onNcCreate(void);
	void onNcDestory(void);

	void onCreate(void);
	void onDestory(void);
	void onClose(void);

	void onPaint(HDC hDC);

	void onSize(wui::WindowMessage* windowMessage);

	bool onCommand(UINT uNotifyCode, int nID, HWND wndCtl);
	void onAbout(void);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





