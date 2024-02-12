#include <iostream>
#include "tetris.h"
#include "math.h"
//This library can be super extended with any kind of SDL, SDL2, or OpenGL functionality 
int FGE_Main()
{
    BUILD_ALL_TARGETS;
    //Creating the window context
    FGE::Window wind= FGE_General_Init();
    
    Tetris::Board board={-boardWidth/2,-boardHeight/2}; 
    FGE_Loop_Start(wind)
       board.Draw();
    FGE_Loop_End(wind)
    

    FGE_Return();
}