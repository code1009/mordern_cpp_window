/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "main.hpp"

#include "WindowAPI.hpp"
#include "MainFrame.hpp"
#include "OtherWindow.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void window0Thread(void)
{
	WindowMessageLoop windowMessageLoop;


	MainFrame mainFrame;


	debugPrintln(L"windowMessageLoop.runLoop() - begin");
	windowMessageLoop.runLoop();
	debugPrintln(L"windowMessageLoop.runLoop() - end");

	/*

MainFrame.ctor() - begin
MainFrame.onNcCreate()
MainFrame.onCreate()
MainFrame.ctor() - end

windowMessageLoop.runLoop() - begin

MainFrame.onClose() - begin

MainFrame.onDestory() - begin
MainFrame.onDestory() - end
MainFrame.onNcDestory()

MainFrame.onClose() - end

windowMessageLoop.runLoop() - end

MainFrame.dtor()

	*/
}

void window1thread(void)
{
	WindowMessageLoop windowMessageLoop;


	MainFrame mainFrame;
	OtherWindow otherWindow;


	windowMessageLoop.runLoop();
}

void window2thread(void)
{
	WindowMessageLoop windowMessageLoop;


	MainFrame mainFrame;


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
	getWindowInstance()->setHandle(hInstance);



	//std::thread thread1(window1thread);
	//std::thread thread2(window2thread);


	window0Thread();


	//thread1.join();
	//thread2.join();

	return 0;
}
