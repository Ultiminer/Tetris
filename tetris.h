#ifndef TETRIS_H_
#define TETRIS_H_

constexpr size_t TETRIS_TILE_SIZE{30};
constexpr size_t TETRIS_TILES_WIDE{10};
constexpr size_t TETRIS_TILES_HIGH{25};
constexpr float boardWidth{TETRIS_TILE_SIZE*TETRIS_TILES_WIDE};
constexpr float boardHeight{TETRIS_TILE_SIZE*TETRIS_TILES_HIGH};


#define FGE_WINDOW_TITLE "TETRIS"
#define FGE_WINDOW_WIDTH {TETRIS_TILE_SIZE*(TETRIS_TILES_WIDE+8)}
#define FGE_WINDOW_HEIGHT {TETRIS_TILE_SIZE*(TETRIS_TILES_HIGH+1)}

#include "FGE_setup.h"
#include "FGE_color.h"




namespace Tetris{
struct Board
{
    const float posX;
    const float posY;


    FGE_Color bgColor=FGE::black; 
    FGE_Color lineColor=FGE::white; 

    std::vector<float> points; 
    FGE::SRect rect; 
    Board(float PosX,float PosY):posX(PosX),posY(PosY)
    {
        points.reserve(TETRIS_TILE_SIZE*4);
        for(float x=0; x<boardWidth;x+=TETRIS_TILE_SIZE)
        {
            points.push_back(posX+x);points.push_back(posY);
            points.push_back(posX+x);points.push_back(posY+boardHeight);
        }
        for(float y=0; y<boardHeight;y+=TETRIS_TILE_SIZE)
        {
            points.push_back(posX);points.push_back(posY+y);
            points.push_back(posX+boardWidth);points.push_back(posY+y);
        }
    }
    inline void Draw()noexcept
    {
     
        rect.SetXM(posX+(TETRIS_TILE_SIZE*(TETRIS_TILES_WIDE))/2).SetYM(posY+(TETRIS_TILE_SIZE*(TETRIS_TILES_HIGH))/2).SetW2(TETRIS_TILE_SIZE*TETRIS_TILES_WIDE/2).SetH2(TETRIS_TILE_SIZE*TETRIS_TILES_HIGH/2).UpdateShape().Draw(bgColor).DrawBorder(lineColor);
        FGE_SetColor(lineColor); 
        __FGE_PRIM_RENDER_DRAW_LINES((float*)points.data(),points.size()/2);
    }
};

enum RotateState{
    DEFAULT,
    STATE_1,
    STATE_2,
    STATE_3
};

struct PieceElements
{
    
};

struct BlockPiece
{
    size_t mI=0; 
    size_t mJ=0; 
    BlockPiece(){}
    BlockPiece(size_t MI, size_t MJ):mI(MI),mJ(MJ)
    {}
    inline PieceElements GenerateTiles(const RotateState& state)
    {
        return ; 
    }

};

};





#endif