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
    board.Add(Tetris::GenerateTTiles(0,0,Tetris::RotateState::STATE_3)); 

    unsigned int y=0;
    int x=0; 
    unsigned int rotState=0;


    FGE_Loop_Start(wind)


    board.Draw();
    if(wind.KeyDown(SDLK_SPACE)||wind.KeyDown(SDLK_RETURN))rotState++;
  	if(wind.KeyDown(SDLK_d)||wind.KeyDown(SDLK_RIGHT))x++;
    if(wind.KeyDown(SDLK_a)||wind.KeyDown(SDLK_LEFT))x--;

    if(x<0)x=0;else
    if(x>TETRIS_TILES_WIDE-3)x=TETRIS_TILES_WIDE-3;

    if(SDL_GetTicks()%30==0){
    if(y<TETRIS_TILES_HIGH-3)y++;
    }
    board.ChangeTopPiece(Tetris::GenerateTTiles(x,y,(Tetris::RotateState)(rotState%4)));


    FGE_Loop_End(wind)
    

    FGE_Return();
}