/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "main.hpp"

#include "WindowUI/Core.hpp"
#include "WindowUI/WindowMessageManipulator.hpp"

#include "WindowUI_Example1/OtherWindow.hpp"
#include "WindowUI_Example1/AboutDialog.hpp"
#include "WindowUI_Example1/AboutModelessDialog.hpp"
#include "WindowUI_Example1/View.hpp"
#include "WindowUI_Example1/MainFrame.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void WindowUI_Example1_Thread0(void)
{
	WindowUI::WindowMessageLoop windowMessageLoop;


	WindowUI_Example1::MainFrame mainFrame;


	WindowUI::debugPrintln(L"windowMessageLoop.runLoop() - begin");
	windowMessageLoop.runLoop();
	WindowUI::debugPrintln(L"windowMessageLoop.runLoop() - end");
}

void WindowUI_Example1_Thread1(void)
{
	WindowUI::WindowMessageLoop windowMessageLoop;


	WindowUI_Example1::MainFrame mainFrame;
	WindowUI_Example1::OtherWindow otherWindow;


	windowMessageLoop.runLoop();
}

void WindowUI_Example1_Thread2(void)
{
	WindowUI::WindowMessageLoop windowMessageLoop;


	WindowUI_Example1::MainFrame mainFrame;


	windowMessageLoop.runLoop();
}

void WindowUI_Example1_Main(void)
{
	//std::thread thread1(WindowUI_Example1_Thread1);
	//std::thread thread2(WindowUI_Example1_Thread2);


	WindowUI_Example1_Thread0();


	//thread1.join();
	//thread2.join();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
int APIENTRY wWinMain(
	HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR    lpCmdLine,
    int       nCmdShow
)
{
	WindowUI::getWindowInstance()->setHandle(hInstance);


	WindowUI_Example1_Main();


	return 0;
}
