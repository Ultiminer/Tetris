#ifndef TETRIS_H_
#define TETRIS_H_

constexpr size_t TETRIS_TILE_SIZE{30};
constexpr size_t TETRIS_TILES_WIDE{10};
constexpr size_t TETRIS_TILES_HIGH{25};
constexpr float boardWidth{TETRIS_TILE_SIZE*TETRIS_TILES_WIDE};
constexpr float boardHeight{TETRIS_TILE_SIZE*TETRIS_TILES_HIGH};

#define FGE_FAST_VSYNC
#define FGE_WINDOW_TITLE "TETRIS"
#define FGE_WINDOW_WIDTH {TETRIS_TILE_SIZE*(TETRIS_TILES_WIDE+8)}
#define FGE_WINDOW_HEIGHT {TETRIS_TILE_SIZE*(TETRIS_TILES_HIGH+1)}
//#define FGE_FAST_VSYNC

#include "FGE_setup.h"
#include "FGE_color.h"
#include "nice_cpp_macros.h"
#include <iostream>

namespace Tetris{
using TETRIS_DATA=size_t; 

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
    const size_t tilesOffset=16;

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
    void unset(size_t id)
    {
        NCM_UnSetBit(data,id+tilesOffset);
    }
    void unset(size_t x, size_t y)
    {
        NCM_UnSetBit(data,x+4*y+tilesOffset);
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
    PieceStructure& setPos( int x, int y)
    {
        data+=x+256*y;
        return *this;
    }
    unsigned int getX()const
    {
       return data&0xFF;
    }
    unsigned int getY()const
    {
        return (data&0xFF00)>>8;
    }
};

enum TileType{
    BLOCK,
    LINE,
    SQUIGGLY,
    L,
    T
};

inline PieceStructure GenerateBlockTiles(const unsigned char xPos,const unsigned char yPos)noexcept
{
    PieceStructure retVal;
    retVal.setPos(xPos,yPos);
    retVal.set(0,2);
    retVal.set(1,2);
    retVal.set(0,3);
    retVal.set(1,3);

    return retVal; 
}
inline PieceStructure GenerateLineTiles(const unsigned char xPos,const unsigned char yPos,const RotateState& state)noexcept
{
    PieceStructure retVal;
    retVal.setPos(xPos,yPos);

    if(((int)state)%2==0)
    {
    retVal.set(0,3);
    retVal.set(1,3);
    retVal.set(2,3);
    retVal.set(3,3);

    return retVal; 
    }
    
    retVal.set(0,0);
    retVal.set(0,1);
    retVal.set(0,2);
    retVal.set(0,3);
    

    return retVal; 
}
inline PieceStructure GenerateSquigglyTiles(const unsigned char xPos,const unsigned char yPos,const RotateState& state)noexcept
{
    PieceStructure retVal;
    retVal.setPos(xPos,yPos);

    if(((int)state)==0)
    {
        
    retVal.set(0,3);
    retVal.set(1,3);
    retVal.set(1,2);
    retVal.set(2,2);

    return retVal; 
    }
    if(((int)state)==1)
    {
    retVal.set(0,3);
    retVal.set(0,2);
    retVal.set(1,2);
    retVal.set(1,1);

    return retVal; 
    }
    if(((int)state)==2)
    {
    retVal.set(2,3);
    retVal.set(1,3);
    retVal.set(1,2);
    retVal.set(0,2);


    return retVal; 
    }
    retVal.set(1,3);
    retVal.set(1,2);
    retVal.set(0,2);
    retVal.set(0,1);
    

    return retVal; 
}
inline PieceStructure GenerateLTiles(const unsigned char xPos,const unsigned char yPos,const RotateState& state)noexcept
{
    PieceStructure retVal;
    retVal.setPos(xPos,yPos);

    if(((int)state)==2)
    {
        
    retVal.set(0,3);
    retVal.set(1,3);
    retVal.set(2,3);
    retVal.set(2,2);

    return retVal; 
    }
    if(((int)state)==1)
    {
    retVal.set(1,3);
    retVal.set(1,2);
    retVal.set(1,1);
    retVal.set(0,1);

    return retVal; 
    }
    if(((int)state)==0)
    {
    retVal.set(0,2);
    retVal.set(1,2);
    retVal.set(2,2);
    retVal.set(0,3);


    return retVal; 
    }
    retVal.set(0,1);
    retVal.set(0,2);
    retVal.set(0,3);
    retVal.set(1,3);
    

    return retVal; 
}
inline PieceStructure GenerateTTiles(const unsigned char xPos,const unsigned char yPos,const RotateState& state)noexcept
{
    PieceStructure retVal;
    retVal.setPos(xPos,yPos);

    if(((int)state)==2)
    {
        
    retVal.set(0,3);
    retVal.set(1,3);
    retVal.set(2,3);
    retVal.set(1,2);

    return retVal; 
    }
    if(((int)state)==1)
    {
    retVal.set(1,3);
    retVal.set(1,2);
    retVal.set(1,1);
    retVal.set(0,2);

    return retVal; 
    }
    if(((int)state)==0)
    {
    retVal.set(0,2);
    retVal.set(1,2);
    retVal.set(2,2);
    retVal.set(1,3);


    return retVal; 
    }
    retVal.set(0,3);
    retVal.set(0,2);
    retVal.set(0,1);
    retVal.set(1,2);
    

    return retVal; 
}

inline PieceStructure GenerateTiles(const unsigned char xPos,const unsigned char yPos,const RotateState& state, const TileType& tileT)
{
    switch(tileT)
    {
        case TileType::BLOCK:
        return GenerateBlockTiles(xPos,yPos);
        break;
        case TileType::LINE:
        return GenerateLineTiles(xPos,yPos,state);
        break;
        case TileType::SQUIGGLY:
        return GenerateSquigglyTiles(xPos,yPos,state);
        break;
        case TileType::L:
        return GenerateLTiles(xPos,yPos,state);
        break;
        case TileType::T:
        return GenerateTTiles(xPos,yPos,state);
        break;
    }

   return GenerateTTiles(xPos,yPos,state);
}

struct UPoint{
size_t x; size_t y;
};
struct Board
{
    const float posX;
    const float posY;


    FGE_Color bgColor=FGE::black; 
    FGE_Color lineColor=FGE::white; 
    FGE_Color pieceColor=FGE::greenyellow; 

    std::vector<float> points; 
    FGE::SRect rect; 
    std::array<bool,TETRIS_TILES_WIDE*TETRIS_TILES_HIGH> pieces; 
    PieceStructure topPiece;
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
        rect.SetXM(posX+(TETRIS_TILE_SIZE*(TETRIS_TILES_WIDE))/2).SetYM(posY+(TETRIS_TILE_SIZE*(TETRIS_TILES_HIGH))/2).SetW2(TETRIS_TILE_SIZE*TETRIS_TILES_WIDE/2).SetH2(TETRIS_TILE_SIZE*TETRIS_TILES_HIGH/2).UpdateShape();
    }
    inline void Add(const PieceStructure& structure)noexcept
    {
        for(size_t i=0; i<16;++i)
        {
           if(topPiece.isSet(i))
           pieces.at(i)=true;
        }
        topPiece.data=structure.data;
    }
    void AddTopPieceY(int y)noexcept
    {
        topPiece.setPos(0,y);
    }
    void AddTopPieceX(int x)noexcept
    {
        topPiece.setPos(x,0);
    }
    void ChangeTopPiece(const PieceStructure& structure)noexcept
    {
        topPiece.data=structure.data;
    }
    inline void Draw()noexcept
    {   
        rect.Draw(bgColor).DrawBorder(lineColor);
        for(size_t i=0; i<16;++i)
        if(topPiece.isSet(i))
        {
            float tPosY{posY+boardHeight-topPiece.getY()*TETRIS_TILE_SIZE-((int)(i/4))*TETRIS_TILE_SIZE+TETRIS_TILE_SIZE/2};
            FGE::SRect rect={posX+topPiece.getX()*TETRIS_TILE_SIZE+(i%4)*TETRIS_TILE_SIZE+TETRIS_TILE_SIZE/2,tPosY,TETRIS_TILE_SIZE/2,TETRIS_TILE_SIZE/2}; 
            //std::cout<<"x: "<<el.getX()<<"y: "<<el.getY()<<std::endl;
            rect.UpdateShape().Draw(pieceColor);
        }
        for(size_t i=0; i<TETRIS_TILES_HIGH*TETRIS_TILES_HIGH;++i)
        if(pieces.at(i))
        {
            FGE::SRect rect={posX+(i%TETRIS_TILES_WIDE)*TETRIS_TILE_SIZE,posY+(i/TETRIS_TILES_WIDE)*TETRIS_TILE_SIZE,TETRIS_TILE_SIZE,TETRIS_TILE_SIZE};
            rect.UpdateShape().Draw(pieceColor);
        }

        FGE_SetColor(lineColor); 
        __FGE_PRIM_RENDER_DRAW_LINES((float*)points.data(),points.size()/2);
    }
    int GetTopPieceX()
    {
        return topPiece.getX();
    }
    int GetTopPieceY()
    {
        return topPiece.getY();
    }
    /*
    0..no collision
    1..collision with right side
    2..collision with floor
    3..collision with other pieces 

    */
    int TopPieceCollides()noexcept
    {
        std::vector<UPoint> tpTiles;
        for(size_t j=0; j<16;++j)if(topPiece.isSet(j)){
            tpTiles.push_back({(topPiece.getX()+j%4),(topPiece.getY()+j/4)});
            if(tpTiles.back().x>TETRIS_TILES_WIDE-1)return 1;
        }

       /* for(size_t i=0; i< pieces.size()-1;++i)
        for(size_t j=0; j<16;++j)
        if(pieces.at(i).isSet(j))
        {
            const size_t X{pieces.at(i).getX()+j%4}; const size_t Y{pieces.at(i).getY()+j/4};
            if((X==tpTiles.at(0).x&&Y==tpTiles.at(0).y)||(X==tpTiles.at(1).x&&Y==tpTiles.at(1).y)||(X==tpTiles.at(2).x&&Y==tpTiles.at(2).y)||(X==tpTiles.at(3).x&&Y==tpTiles.at(3).y))
            {return 3;}
        }*/
        return false; 
    }


    void CheckLineFull()
    {
       /* std::array<size_t,TETRIS_TILES_HIGH+2>numY={0};
        for(size_t i=0; i< pieces.size()-1;++i)
        for(size_t j=0; j<16;++j)
       if(pieces.at(i).isSet(j))
        {
            const size_t Y{pieces.at(i).getY()+j/4};
            numY.at(Y)++;
        }

        for(size_t y=0;y<=TETRIS_TILES_HIGH;y++)
        {
            if(numY[y]==10)
            {
                for(size_t i=0; i< pieces.size()-1;++i)
                {
                 for(size_t j=0; j<16;++j)
                 if(pieces.at(i).isSet(j))
                 {
                    const size_t Y{pieces.at(i).getY()+j/4};
                    //std::cout<<y;
                    if(Y==y)pieces.at(i).unset(j);
                   
                 }
                 for(size_t j=0; j<16;++j)
                 if(pieces.at(i).isSet(j))
                 {
                    const size_t Y{pieces.at(i).getY()+j/4};
                    if(Y<y)pieces.at(i).setPos(0,1);
                 }
                }
            }
        }*/
    }
};



};





#endif