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
#include "nice_cpp_macros.h"
#include <iostream>

namespace Tetris{
using TETRIS_DATA=unsigned int; 
enum RotateState{
    DEFAULT,
    STATE_1,
    STATE_2,
    STATE_3
};

/*ASSUMES THAT EVERY PIECE CAN BE CONSTRUCTED WITHIN AN 4x4 grid
0100
0100 
0100
0100
*/
struct PieceStructure
{
    TETRIS_DATA data=0;
    const size_t tilesOffset=8;

    constexpr size_t size()const
    {
        return 16;
    }
    constexpr size_t width()const
    {
        return 4;
    }
    constexpr size_t height()const
    {
        return 4;
    }
    void set(size_t id)
    {
        data+=1<<(id+tilesOffset);
    }
    void set(size_t x, size_t y)
    {
        set(x+4*y);
    }
   
    bool isSet(size_t id)const
    {
        return  NCM_GetBit(data,tilesOffset+id); 
    }
    bool isSet(size_t x, size_t y)
    {
        return NCM_GetBit(data,tilesOffset+x+4*y);
    }
    void setPos(unsigned int x,unsigned int y)
    {
        data+=x+16*y;
    }
    unsigned int getX()const
    {
        return data&(0xF);
    }
    unsigned int getY()const
    {
        return (data&(0xF0))>>4;
    }
};


inline PieceStructure GenerateBlockTiles(const unsigned char xPos,const unsigned char yPos)noexcept
{
    PieceStructure retVal;
    retVal.setPos(xPos,yPos);
    retVal.set(1,1);
    retVal.set(2,1);
    retVal.set(1,2);
    retVal.set(2,2);

    return retVal; 
}




struct Board
{
    const float posX;
    const float posY;


    FGE_Color bgColor=FGE::black; 
    FGE_Color lineColor=FGE::white; 
    FGE_Color pieceColor=FGE::greenyellow; 

    std::vector<float> points; 
    FGE::SRect rect; 
    std::vector<PieceStructure>pieces;
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
    inline void Add(const PieceStructure& structure)noexcept
    {
        pieces.push_back(structure);
    }
    void ChangeTopPiece(const PieceStructure& structure)noexcept
    {
        pieces.back().data=structure.data;
    }
    inline void Draw()noexcept
    {   
        rect.SetXM(posX+(TETRIS_TILE_SIZE*(TETRIS_TILES_WIDE))/2).SetYM(posY+(TETRIS_TILE_SIZE*(TETRIS_TILES_HIGH))/2).SetW2(TETRIS_TILE_SIZE*TETRIS_TILES_WIDE/2).SetH2(TETRIS_TILE_SIZE*TETRIS_TILES_HIGH/2).UpdateShape().Draw(bgColor).DrawBorder(lineColor);
        for(auto& el: pieces)for(size_t i=0; i<16;++i)
        if(el.isSet(i))
        {
            FGE::SRect rect={posX+el.getX()*TETRIS_TILE_SIZE+(i%4)*TETRIS_TILE_SIZE+TETRIS_TILE_SIZE/2,posY+el.getY()*TETRIS_TILE_SIZE+((int)(i/4))*TETRIS_TILE_SIZE+TETRIS_TILE_SIZE/2,TETRIS_TILE_SIZE/2,TETRIS_TILE_SIZE/2}; 
            rect.UpdateShape().Draw(pieceColor);
        }
        FGE_SetColor(lineColor); 
        __FGE_PRIM_RENDER_DRAW_LINES((float*)points.data(),points.size()/2);
    }
};



};





#endif