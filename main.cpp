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
    board.Add(Tetris::GenerateBlockTiles(0,0)); 
    int y=0; 
    FGE_Loop_Start(wind)
      board.Draw();
      board.ChangeTopPiece(Tetris::GenerateBlockTiles(0,y));
      y++;
    FGE_Loop_End(wind)
    

    FGE_Return();
}