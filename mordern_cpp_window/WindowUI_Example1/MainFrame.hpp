#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI_Example1
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MainFrame : public WindowUI::BaseWindow
{
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

	bool onCommand(UINT uNotifyCode, int nID, HWND wndCtl);
	void onPaint(HDC hDC);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





