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
    const unsigned char tilesOffset=16;

    constexpr unsigned char size()const
    {
        return 16;
    }
    constexpr unsigned char width()const
    {
        return 4;
    }
    constexpr unsigned char height()const
    {
        return 4;
    }
    void set(unsigned char id)
    {
        data+=1<<(id+tilesOffset);
    }
    void unset(unsigned char id)
    {
        NCM_UnSetBit(data,id+tilesOffset);
    }
    void unset(char x, char y)
    {
        NCM_UnSetBit(data,x+4*y+tilesOffset);
    }
    void set(char x, char y)
    {
        set(x+4*y);
    }
   
    bool isSet(unsigned char id)const
    {
        return  NCM_GetBit(data,tilesOffset+id); 
    }
    bool isSet(char x, char y)
    {
        return NCM_GetBit(data,tilesOffset+x+4*y);
    }
    PieceStructure& setPos( int x, int y)
    {
        data+=x+256*y;
        return *this;
    }
    unsigned char getX()const
    {
       return data&0xFF;
    }
    unsigned char getY()const
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
struct CPoint
{
    char x; char y; 
};

struct Board
{
    const float posX;
    const float posY;


    FGE_Color bgColor=FGE::black; 
    FGE_Color lineColor=FGE::white; 
    FGE_Color pieceColor=FGE::greenyellow; 

    std::vector<float> points; 
    FGE::SRect boardRect; 
    std::vector<CPoint> pieces; 
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
        boardRect.SetXM(posX+(TETRIS_TILE_SIZE*(TETRIS_TILES_WIDE))/2).SetYM(posY+(TETRIS_TILE_SIZE*(TETRIS_TILES_HIGH))/2).SetW2(TETRIS_TILE_SIZE*TETRIS_TILES_WIDE/2).SetH2(TETRIS_TILE_SIZE*TETRIS_TILES_HIGH/2).UpdateShape();
    }
    inline void Add(const PieceStructure& structure)noexcept
    {
        for(unsigned char i=0; i<16;++i)
        {
           if(topPiece.isSet(i))
           pieces.push_back({(char)(topPiece.getX()+(i%4)),(char)(topPiece.getY()+i/4)});
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
        boardRect.Draw(bgColor).DrawBorder(lineColor);
        for(size_t i=0; i<16;++i)
        if(topPiece.isSet(i))
        {
            float tPosY{posY+boardHeight-topPiece.getY()*TETRIS_TILE_SIZE-((int)(i/4))*TETRIS_TILE_SIZE+TETRIS_TILE_SIZE/2};
            FGE::SRect topRect={posX+topPiece.getX()*TETRIS_TILE_SIZE+(i%4)*TETRIS_TILE_SIZE+TETRIS_TILE_SIZE/2,tPosY,TETRIS_TILE_SIZE/2,TETRIS_TILE_SIZE/2}; 
            //std::cout<<"x: "<<el.getX()<<"y: "<<el.getY()<<std::endl;
            topRect.UpdateShape().Draw(pieceColor);
        }
        for(auto& el: pieces){
        FGE::SRect pieceRect={posX+el.x*(TETRIS_TILE_SIZE)+TETRIS_TILE_SIZE/2,posY+boardHeight-((el.y)*(TETRIS_TILE_SIZE)-TETRIS_TILE_SIZE/2),TETRIS_TILE_SIZE/2,TETRIS_TILE_SIZE/2};
        pieceRect.UpdateShape().Draw(pieceColor);
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
        std::vector<CPoint> tpTiles;
        for(size_t j=0; j<16;++j)if(topPiece.isSet(j)){
            tpTiles.push_back({(char)(topPiece.getX()+j%4),(char)(topPiece.getY()+j/4)});
            if(tpTiles.back().x>(char)(TETRIS_TILES_WIDE-1))return 1;
        }

        for(auto& el:pieces)
        {
            if((el.x==tpTiles.at(0).x&&el.y==tpTiles.at(0).y)||
            (el.x==tpTiles.at(1).x&&el.y==tpTiles.at(1).y)||
            (el.x==tpTiles.at(2).x&&el.y==tpTiles.at(2).y)||
            (el.x==tpTiles.at(3).x&&el.y==tpTiles.at(3).y))
            {return 3;}
        }
        return false; 
    }


    void CheckLineFull()
    {
       std::array<size_t,TETRIS_TILES_HIGH+2>numY={0};
       for(auto& el:pieces)numY.at(el.y)++;

       for(size_t y=0;y<=TETRIS_TILES_HIGH;y++)
       if(numY[y]==TETRIS_TILES_WIDE)
       for(size_t i=0; i<pieces.size();++i)
       if(pieces.at(i).y==y){pieces.erase(pieces.begin()+i);i--;}
        else if (pieces.at(i).y<y)pieces.at(i).y++;
        
    }
};



};





#endif