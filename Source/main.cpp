#include <iostream>
#include <stdio.h>

#include "GL_Game.h"

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

// The MAIN function, from here we start the application and run the game loop
int main( )
{

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	
	GL_Game * glGame = new GL_Game();
    
    glGame->Update();
    
    glGame->Cleanup();

	delete glGame;
    
    return EXIT_SUCCESS;
    
}




