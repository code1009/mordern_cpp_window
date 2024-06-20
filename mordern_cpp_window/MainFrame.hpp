#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MainFrame : public Window
{
public:
	MainFrame();
	virtual ~MainFrame();

public:
	virtual void registerWindowMessageHandler(void) override;
	virtual void initializeWindowClass(void) override;

public:
	void onCreate(void);
	void onDestory(void);
	void onClose(void);

	bool onCommand(UINT uNotifyCode, int nID, HWND wndCtl);
	void onPaint(HDC hDC);
};
