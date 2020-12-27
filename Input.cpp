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
		
		
	} while (c!=Escape || c!=Enter);

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
			ITM_AND2 = 0;
			ITM_OR2 = 1;
			ITM_NOT = 2;
			ITM_BUFF = 3;
			ITM_AND3 = 4;
			ITM_NAND = 5;
			ITM_NOR2 = 6;
			ITM_NOR3 = 7;
			ITM_XOR2 = 8;
			ITM_XOR3 = 9;
			ITM_XNOR = 10;
			ITM_SWITCH = 11;
			ITM_LED = 12;
			ITM_CONNECTION = 13;
			ITM_EXIT = 14;
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.ToolItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_AND2: return ADD_AND_GATE_2;
			case ITM_OR2: return ADD_OR_GATE_2;
					//Ali//
			case ITM_AND3: return ADD_AND_GATE_3;
			case ITM_NOT: return ADD_NOT_GATE;
			case ITM_BUFF: return ADD_Buff;
			case ITM_NAND:return ADD_NAND_GATE_2;
			case ITM_NOR2:return ADD_NOR_GATE_2;
			case ITM_NOR3:return ADD_NOR_GATE_3;
			case ITM_XOR2:return ADD_XOR_GATE_2;
			case ITM_XOR3:return ADD_XOR_GATE_3;
			case ITM_XNOR:return ADD_XNOR_GATE_2;
			case ITM_SWITCH:return ADD_Switch;
			case ITM_LED:return ADD_LED;
			case ITM_CONNECTION:return ADD_CONNECTION;	

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
