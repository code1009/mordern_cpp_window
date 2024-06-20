#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MainWindow : public Window
{
public:
	MainWindow();
	virtual ~MainWindow();

public:
	virtual void registerWindowMessageHandler(void) override;

public:
	void onCreate(void);
	void onDestory(void);
	void onClose(void);
};
