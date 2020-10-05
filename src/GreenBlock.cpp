#include "GreenBlock.h"

GreenBlock::GreenBlock(){
}

void GreenBlock::MoveSetFillColor(int direction, Maze *MZ){
    //Sets fill color of new pos and old pos
    sf::Color squareCol;
    switch(direction){
    case globals::up:
        squareCol = MZ->maze[MZ->greenPos.x][MZ->greenPos.y - 1].shape.getFillColor();
        if (MZ->SquareIsValid(squareCol)){
            MZ->maze[MZ->greenPos.x][MZ->greenPos.y - 1].shape.setFillColor(globals::green);
            if (squareCol != globals::darkGreen){
                MZ->maze[MZ->greenPos.x][MZ->greenPos.y].shape.setFillColor(globals::darkGreen);
            }else{
                MZ->maze[MZ->greenPos.x][MZ->greenPos.y].shape.setFillColor(globals::white);
            }
            MZ->greenPos.y -= 1;
        }
        break;

    case globals::right:
        squareCol = MZ->maze[MZ->greenPos.x + 1][MZ->greenPos.y].shape.getFillColor();
        if (MZ->SquareIsValid(squareCol)){
            MZ->maze[MZ->greenPos.x + 1][MZ->greenPos.y].shape.setFillColor(globals::green);
            if (squareCol != globals::darkGreen){
                MZ->maze[MZ->greenPos.x][MZ->greenPos.y].shape.setFillColor(globals::darkGreen);
            }else{
                MZ->maze[MZ->greenPos.x][MZ->greenPos.y].shape.setFillColor(globals::white);
            }
            MZ->greenPos.x += 1;
        }
        break;

    case globals::down:
        squareCol = MZ->maze[MZ->greenPos.x ][MZ->greenPos.y + 1].shape.getFillColor();
        if (MZ->SquareIsValid(squareCol)){
            MZ->maze[MZ->greenPos.x][MZ->greenPos.y + 1].shape.setFillColor(globals::green);
            if (squareCol != globals::darkGreen){
                MZ->maze[MZ->greenPos.x][MZ->greenPos.y].shape.setFillColor(globals::darkGreen);
            }else{
                MZ->maze[MZ->greenPos.x][MZ->greenPos.y].shape.setFillColor(globals::white);
            }
            MZ->greenPos.y += 1;
        }
        break;

    case globals::left:
        squareCol = MZ->maze[MZ->greenPos.x - 1][MZ->greenPos.y].shape.getFillColor();
        if (MZ->SquareIsValid(squareCol)){
            MZ->maze[MZ->greenPos.x - 1][MZ->greenPos.y].shape.setFillColor(globals::green);
            if (squareCol != globals::darkGreen){
                MZ->maze[MZ->greenPos.x][MZ->greenPos.y].shape.setFillColor(globals::darkGreen);
            }else{
                MZ->maze[MZ->greenPos.x][MZ->greenPos.y].shape.setFillColor(globals::white);
            }
            MZ->greenPos.x -= 1;
        }
        break;
    }
}

void GreenBlock::Move(int direction, Maze *MZ){
    //Will move the globals::green square in a direction IF AND ONLY IF there is not a globals::black square in that direction
    MoveSetFillColor(direction, MZ);
    if (MZ->IsMazeSolved()){
        std::cout << "Maze has been solved!";
    }
}
