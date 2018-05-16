#include <string.h>
#include <stdio.h>

#include <switch.h>

#include "kernel.h"
#include "system.h"

static Result SwitchIdent_InitServices(void)
{
	Result ret = 0;

	if (R_FAILED(ret = splInitialize()))
		return ret;
}

static Result SwitchIdent_TermServices(void)
{
	splExit();
}

int main(int argc, char **argv)
{
	SwitchIdent_InitServices();
	gfxInitDefault();

	//Initialize console. Using NULL as the second argument tells the console library to use the internal console structure as current one.
	consoleInit(NULL);

	printf("\x1b[1;1H"); //Move the cursor to the top left corner of the screen
	printf("\x1b[32;1mSwitchIdent 0.1\x1b[0m\n\n");

	printf("\x1b[31;1m*\x1b[0m System version: \x1b[31;1m%s\n", SwitchIdent_GetVersion());
	printf("\x1b[31;1m*\x1b[0m Hardware: \x1b[31;1m%s\x1b[0m (\x1b[31;1m%s\x1b[0m) \x1b[0m\n\n", SwitchIdent_GetHardwareType(), SwitchIdent_GetUnit());

	printf("\x1b[33;1m*\x1b[0m Language: \x1b[33;1m%s\n", SwitchIdent_GetLanguage());
	printf("\x1b[33;1m*\x1b[0m Region: \x1b[33;1m%s\n", SwitchIdent_GetRegion());

	printf("\n\x1b[32;1m> Press the plus key to exit =)\x1b[0m");

	while(appletMainLoop())
	{
		//Scan all the inputs. This should be done once for each frame
		hidScanInput();

		//hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
		u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if (kDown & KEY_PLUS) 
			break; // break in order to return to hbmenu

		gfxFlushBuffers();
		gfxSwapBuffers();
		gfxWaitForVsync();
	}

	gfxExit();
	SwitchIdent_TermServices();
	return 0;
}
