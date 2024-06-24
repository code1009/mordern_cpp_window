/////////////////////////////////////////////////////////////////////////////
//===========================================================================
#include "../framework.h"

#include "Core.hpp"
#include "WindowMessageManipulator.hpp"





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
namespace WindowUI
{





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





/////////////////////////////////////////////////////////////////////////////
//===========================================================================
}




