/////////////////////////////////////////////////////////////////////////////
//===========================================================================
/*
구성 속성/
	C/C++/
		출력 파일/
			개체 파일 이름: $(IntDir)
			에서
			개체 파일 이름: $(IntDir)%(RelativeDir)
			으로
*/

//===========================================================================
#include "main.hpp"

#include <winternl.h>

#include <atlbase.h>
#include <atlhost.h>


//===========================================================================
#include "wui/Core.hpp"
#include "wui/WindowMessageManipulator.hpp"
#include "wui/WindowFunction.hpp"

//===========================================================================
#include "wui_Test/OtherWindow.hpp"
#include "wui_Test/AboutDialog.hpp"
#include "wui_Test/AboutModelessDialog.hpp"
#include "wui_Test/View.hpp"
#include "wui_Test/MainFrame.hpp"

//===========================================================================
#include "wui_Example1/AboutDialog.hpp"
#include "wui_Example1/View.hpp"
#include "wui_Example1/MainFrame.hpp"

//===========================================================================
#include "wui_Example2/AboutDialog.hpp"
#include "wui_Example2/MainFrame.hpp"

//===========================================================================
#include "wui_Example3/AboutDialog.hpp"
#include "wui_Example3/MainFrame.hpp"




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void wui_Test_Thread0(void)
{
	wui::WindowMessageLoop windowMessageLoop;


	wui_Test::MainFrame mainFrame;


	wui::debugPrintln(L"windowMessageLoop.runLoop() - begin");
	windowMessageLoop.runLoop();
	wui::debugPrintln(L"windowMessageLoop.runLoop() - end");
}

void wui_Test_Thread1(void)
{
	wui::WindowMessageLoop windowMessageLoop;


	wui_Test::MainFrame mainFrame;
	wui_Test::OtherWindow otherWindow;


	windowMessageLoop.runLoop();
}

void wui_Test_Thread2(void)
{
	wui::WindowMessageLoop windowMessageLoop;


	wui_Test::MainFrame mainFrame;


	windowMessageLoop.runLoop();
}

void wui_Test_Main(void)
{
	//std::thread thread1(wui_Test_Thread1);
	//std::thread thread2(wui_Test_Thread2);


	wui_Test_Thread0();


	//thread1.join();
	//thread2.join();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void wui_Example1_Main(void)
{
	wui::WindowMessageLoop windowMessageLoop;


	wui_Example1::MainFrame mainFrame;


	wui::debugPrintln(L"windowMessageLoop.runLoop() - begin");
	windowMessageLoop.runLoop();
	wui::debugPrintln(L"windowMessageLoop.runLoop() - end");
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void wui_Example2_Main(void)
{
	wui::WindowMessageLoop windowMessageLoop;


	wui_Example2::MainFrame mainFrame;


	windowMessageLoop.runLoop();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void wui_Example3_Main(void)
{
	wui::WindowMessageLoop windowMessageLoop;


	wui_Example3::MainFrame mainFrame;


	windowMessageLoop.runLoop();
}




/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void Run(void)
{
	//wui_Test_Main();
	//wui_Example1_Main();
	//wui_Example2_Main();
	wui_Example3_Main();
}





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
CComModule _Module;

//===========================================================================
int APIENTRY wWinMain(
	HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPWSTR    lpCmdLine,
    int       nCmdShow
)
{
	//------------------------------------------------------------------------
	if (FAILED(CoInitialize(NULL)))
	{
		return 0;
	}


	//------------------------------------------------------------------------
	::AtlAxWinInit();


	//------------------------------------------------------------------------
	wui::getWindowInstance()->setHandle(hInstance);
	Run();



	//------------------------------------------------------------------------
	::AtlAxWinTerm();
	CoUninitialize();


	return 0;
}
