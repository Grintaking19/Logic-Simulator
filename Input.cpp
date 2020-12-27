#include "Input.h"
#include "Output.h"
#include <cstring>


Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int &x, int &y)
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

// This is the ASSCII value of 
const char Enter = '\r';
const char Escape = '\e';
const char Backspace ='\b';


string Input::GetSrting(Output *pOut)
{
	
	string str;
	char ch;
	pWind->FlushKeyQueue(); // we do this to overcome any miss clicks returned
	do
	{
		pWind->WaitKeyPress(ch); // we waits any clicks pressed by user from the window
		pOut->PrintMsg(str);  // here we display on the window as an Output the order or the message we want + the string we type 		
		
		if (ch == Backspace)
		{
			str.pop_back();
		}

		else if (ch == Escape)
		{
			if (!str.empty())
			{
				str.clear();
			}
		}

		else if (ch == Enter)
		{
			return;
		}
		else str.push_back(ch);
		
		
	} 
	while (c!=Escape || c!=Enter);

	return str;
  }




//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{	
	int x,y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if(UI.AppMode == DESIGN )	//application is in design mode
	{
		//[1] If user clicks on the Toolbar
		if ( y >= 0 && y < UI.ToolBarHeight)
		{	
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
			case ITM_EXIT: return EXIT;	
			
			default: return DSN_TOOL;	//A click on empty place in desgin toolbar
			}
		}
	
		//[2] User clicks on the drawing area
		if ( y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return SELECT;	//user want to select/unselect a component
		}
		
		//[3] User clicks on the status bar
		return STATUS_BAR;
	}
	else	//Application is in Simulation mode
	{
		return SIM_MODE;	//This should be changed after creating the compelete simulation bar 
	}

}


Input::~Input()
{
}
