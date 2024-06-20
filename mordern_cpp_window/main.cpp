/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "main.hpp"

#include "WindowAPI.hpp"
#include "MainWindow.hpp"
#include "OtherWindow.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
void window0Thread(void)
{
	WindowMessageLoop windowMessageLoop;


	MainWindow mainWindow;
	OtherWindow otherWindow;

	print("windowMessageLoop.runLoop() - begin");
	windowMessageLoop.runLoop();
	print("windowMessageLoop.runLoop() - end");
}

void window1thread(void)
{
	WindowMessageLoop windowMessageLoop;


	MainWindow mainWindow;


	windowMessageLoop.runLoop();
}

void window2thread(void)
{
	WindowMessageLoop windowMessageLoop;


	MainWindow mainWindow;


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



	std::thread thread1(window1thread);
	std::thread thread2(window2thread);


	window0Thread();

	thread1.join();
	thread2.join();

	return 0;
}
