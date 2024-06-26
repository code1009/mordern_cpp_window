/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "main.hpp"

//===========================================================================
#include "WindowUI/Core.hpp"
#include "WindowUI/WindowMessageManipulator.hpp"
#include "WindowUI/WindowFunction.hpp"

//===========================================================================
#include "WindowUI_Test/OtherWindow.hpp"
#include "WindowUI_Test/AboutDialog.hpp"
#include "WindowUI_Test/AboutModelessDialog.hpp"
#include "WindowUI_Test/View.hpp"
#include "WindowUI_Test/MainFrame.hpp"

//===========================================================================
#include "WindowUI_Example1/AboutDialog.hpp"
#include "WindowUI_Example1/View.hpp"
#include "WindowUI_Example1/MainFrame.hpp"

//===========================================================================
#include "WindowUI_Example2/AboutDialog.hpp"
#include "WindowUI_Example2/MainFrame.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void WindowUI_Test_Thread0(void)
{
	WindowUI::WindowMessageLoop windowMessageLoop;


	WindowUI_Test::MainFrame mainFrame;


	WindowUI::debugPrintln(L"windowMessageLoop.runLoop() - begin");
	windowMessageLoop.runLoop();
	WindowUI::debugPrintln(L"windowMessageLoop.runLoop() - end");
}

void WindowUI_Test_Thread1(void)
{
	WindowUI::WindowMessageLoop windowMessageLoop;


	WindowUI_Test::MainFrame mainFrame;
	WindowUI_Test::OtherWindow otherWindow;


	windowMessageLoop.runLoop();
}

void WindowUI_Test_Thread2(void)
{
	WindowUI::WindowMessageLoop windowMessageLoop;


	WindowUI_Test::MainFrame mainFrame;


	windowMessageLoop.runLoop();
}

void WindowUI_Test_Main(void)
{
	//std::thread thread1(WindowUI_Test_Thread1);
	//std::thread thread2(WindowUI_Test_Thread2);


	WindowUI_Test_Thread0();


	//thread1.join();
	//thread2.join();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void WindowUI_Example1_Main(void)
{
	WindowUI::WindowMessageLoop windowMessageLoop;


	WindowUI_Example1::MainFrame mainFrame;


	WindowUI::debugPrintln(L"windowMessageLoop.runLoop() - begin");
	windowMessageLoop.runLoop();
	WindowUI::debugPrintln(L"windowMessageLoop.runLoop() - end");
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void WindowUI_Example2_Main(void)
{
	WindowUI::WindowMessageLoop windowMessageLoop;


	WindowUI_Example2::MainFrame mainFrame;


	windowMessageLoop.runLoop();
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
	/*
	구성 속성/
		C/C++/
			출력 파일/
				개체 파일 이름: $(IntDir)
				에서
				개체 파일 이름: $(IntDir)%(RelativeDir)
				으로
	*/
	WindowUI::getWindowInstance()->setHandle(hInstance);

	//WindowUI_Test_Main();
	//WindowUI_Example1_Main();
	WindowUI_Example2_Main();


	return 0;
}
