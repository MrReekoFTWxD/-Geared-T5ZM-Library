# Black Ops Zombies 


* This is a .lib and Header file for Black Ops 1 Zombies! For helping getting started on making offhost menu for zombies or campaign. 
* This contains:
  * Structs: UiContext, Centity, CG, CGS
  * Engine Functions: DrawShader, DrawText, DrawLine, AimTarget_GetTagPos, Cbuf_AddText, Dvar_GetBool, WorldToScreen...
  * For Steam Update: 378 [64.18.17.13]

## Installation

Install by adding the Header File to your project and Add the lib inside C/C++ Additional Include Directories 

## Usage

```cpp
#include "T5ZM.h"

//Start by calling 

//Defining Colors - I use the color structure so do

Color_t Red = {1,0,0,1};
/*
Engine.CG_DrawRotatedPic(100,100,100,100,0,Red, "white");

 Then i set up where you can define colors just in the call instead of needing to have a section just for colors
Engine.CG_DrawRotatedPic(100,100,100,100,0,Color(1,0,0,1), "white");
 or 
Engine.CG_DrawRotatedPic(100,100,100,100,0,Color(255,0,0,255), "white");


*/

void YourHook(){
	Engine.Init();
	//Need your own ingame check here then do below WIll add a inGameCheck later
		getStructs();
}

BOOL APIENTRY DllMain( HMODULE hModule,DWORD  ul_reason_for_call,LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
	YourHook();
   	
	 
	break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

```
