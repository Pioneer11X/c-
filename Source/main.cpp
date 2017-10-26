#include <iostream>
#include <stdio.h>

#include "GL_Game.h"

// The MAIN function, from here we start the application and run the game loop
int main( )
{
	
	GL_Game * glGame = new GL_Game();
    
    glGame->Update();
    
    glGame->Cleanup();

	delete glGame;
    
    return EXIT_SUCCESS;
    
}




