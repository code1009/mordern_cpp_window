/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "framework.h"

#include "WindowUI.hpp"
#include "WindowUI_WindowMessageManipulator.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
WindowMessageManipulator::WindowMessageManipulator(WindowMessage* windowMessage) :
	_windowMessage{ windowMessage }
{
}

WindowMessageManipulator::~WindowMessageManipulator()
{
}

WindowMessage* WindowMessageManipulator::getWindowMessage(void)
{
	return _windowMessage;
}





