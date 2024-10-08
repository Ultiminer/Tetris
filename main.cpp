#include <iostream>
#include "tetris.h"
#include "math.h"
//This library can be super extended with any kind of SDL, SDL2, or OpenGL functionality 
#include "FGE_random.h"
int FGE_Main()
{
    BUILD_ALL_TARGETS;
    //Creating the window context
    FGE::Window wind= FGE_General_Init();
    
    Tetris::Board board={-boardWidth/2,-boardHeight/2}; 

    size_t deltaTime=150;
    size_t currentTicks;
    unsigned int rotState=0;
    unsigned int tileKind=random.int_rand(4);
    unsigned int spawnX=random.int_rand(TETRIS_TILES_WIDE);
    board.Add(Tetris::GenerateTiles(spawnX,0,Tetris::RotateState::STATE_3,(Tetris::TileType)tileKind)); 

    FGE_Loop_Start(wind);

    board.Draw();

    if(wind.KeyDown(SDLK_SPACE)||wind.KeyDown(SDLK_RETURN)){
      rotState++;
      board.ChangeTopPiece(Tetris::GenerateTiles(board.GetTopPieceX(),board.GetTopPieceY(),(Tetris::RotateState)(rotState%4),(Tetris::TileType)(tileKind%5)));
      if(board.TopPieceCollides()>0)
      {
      rotState--;
      board.ChangeTopPiece(Tetris::GenerateTiles(board.GetTopPieceX(),board.GetTopPieceY(),(Tetris::RotateState)(rotState%4),(Tetris::TileType)(tileKind%5)));
      }
    };
  	if(wind.KeyDown(SDLK_d)||wind.KeyDown(SDLK_RIGHT)){
      board.AddTopPieceX(1);
      if(board.TopPieceCollides()==3)board.AddTopPieceX(-1);
    };
    if(board.TopPieceCollides()==1) board.AddTopPieceX(-1);
    if((wind.KeyDown(SDLK_a)||wind.KeyDown(SDLK_LEFT))&&board.GetTopPieceX()>0){
      board.AddTopPieceX(-1);
      if(board.TopPieceCollides()==3)board.AddTopPieceX(1);
    };
    if((wind.KeyDown(SDLK_DOWN)||wind.KeyDown(SDLK_s))&&board.GetTopPieceY()<TETRIS_TILES_HIGH-4)
    {
      if(board.TopPieceCollides()==0){
        board.AddTopPieceY(1);
        if(board.TopPieceCollides()>0)board.AddTopPieceY(-1);
      }

    }
     
    if(currentTicks+deltaTime<SDL_GetTicks()){
      currentTicks=SDL_GetTicks();
    board.AddTopPieceY(1);

    if(board.TopPieceCollides()==3){
      board.AddTopPieceY(-1);
      tileKind++;
      spawnX=random.int_rand(TETRIS_TILES_WIDE);
      board.Add(Tetris::GenerateTiles(spawnX,0,Tetris::RotateState::STATE_3,(Tetris::TileType)(tileKind%5)));
      if(board.CheckLineFull())
      deltaTime--;
      
    }else
    if(board.GetTopPieceY()==TETRIS_TILES_HIGH-3)
    {
      tileKind++;
      spawnX=random.int_rand(TETRIS_TILES_WIDE);
      board.Add(Tetris::GenerateTiles(spawnX,0,Tetris::RotateState::STATE_3,(Tetris::TileType)(tileKind%5)));
      if(board.CheckLineFull())
      deltaTime--;
    }
    
    }
    

    FGE_Loop_End(wind);
    

    FGE_Return();
}