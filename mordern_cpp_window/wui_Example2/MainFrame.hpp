﻿#pragma once





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace wui_Example2
{





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
class MainFrame : public wui::BasicWindow
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
	void onCreate(wui::WindowMessage* windowMessage);
	void onDestory(wui::WindowMessage* windowMessage);
	void onClose(wui::WindowMessage* windowMessage);

	void onSize(wui::WindowMessage* windowMessage);

	void onCommand(wui::WindowMessage* windowMessage);
	void onAbout(wui::WindowMessage* windowMessage);
	void onExit(wui::WindowMessage* windowMessage);
	void onTest1(wui::WindowMessage* windowMessage);
	void onTest2(wui::WindowMessage* windowMessage);
};





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}





