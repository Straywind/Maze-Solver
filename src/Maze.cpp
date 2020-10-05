#include "Maze.h"

Maze::Maze(){
    start = StartingPoint();
    centerPos = sf::Vector2i(globals::WIDTH/globals::BLOCK_SIZE/2, globals::HEIGHT/globals::BLOCK_SIZE/2);

    //Sets information for each node "block"
    for (int x = 0; x < globals::WIDTH; x += globals::BLOCK_SIZE){
        std::vector<block> newBlockVector;
        for (int y = 0; y < globals::HEIGHT; y += globals::BLOCK_SIZE){
            block new_block;

            ///block.shape info
            sf::RectangleShape rec;
            rec.setSize(sf::Vector2f(globals::BLOCK_SIZE, globals::BLOCK_SIZE));
            rec.setPosition(x, y);

            //Creates basic grid
            if (PartOfCircle(x, y)){
                rec.setFillColor(globals::black);
            }else{

                rec.setFillColor(globals::white);
            }
            if (PartOfCenter(x, y)){
                rec.setFillColor(globals::red);
            }

            //Starting point
            if (rec.getPosition() == start){
                rec.setFillColor(globals::green);
                greenPos.x = x/globals::BLOCK_SIZE;
                greenPos.y = y/globals::BLOCK_SIZE;
            }
            new_block.shape = rec;

            ///block costs and parent position info
            new_block.fCost = FLT_MAX;
            new_block.gCost = FLT_MAX;
            new_block.hCost = FLT_MAX;
            new_block.pos = sf::Vector2i(x/globals::BLOCK_SIZE, y/globals::BLOCK_SIZE);
            new_block.parentPos = sf::Vector2i(-1, -1);

            newBlockVector.push_back(new_block);
        }
        maze.push_back(newBlockVector);
    }

    std::vector<sf::Vector2i> exclusions = CreateBlockExceptions();
    for (unsigned int k = 0; k < exclusions.size(); k++){
        maze[exclusions[k].x][exclusions[k].y].shape.setFillColor(globals::white);
    }
}

void Maze::Draw(sf::RenderWindow &renderWindow){
    //Draws the entire maze to render window
    for (unsigned int i = 0; i < maze.size(); i++){
        for (unsigned int j = 0; j < maze[i].size(); j++){
            renderWindow.draw(maze[i][j].shape);
        }
    }
}

std::vector<sf::Vector2i> Maze::CreateBlockExceptions(){
    //Creates a certain number of blocking points that is checked in ctor
    std::vector<sf::Vector2i> exclusions; //Vector of holes in the concentric circles of the maze, to allow path to the center
    static int layer = 2;

    for (int i = 0; i <= 3; i++){
        int side = rand() % 4;
        int x, y;
        switch(side){
        case 0:
            x = (rand() % ((globals::WIDTH / globals::BLOCK_SIZE) - ((layer + 1) * 2))) + layer + 1;
            y = layer;
            break;
        case 1:
            x = (globals::WIDTH / globals::BLOCK_SIZE) - layer - 1;
            y = (rand() % ((globals::HEIGHT/globals::BLOCK_SIZE) - ((layer + 1) * 2))) + layer + 1;
            break;
        case 2:
            x = (rand() % ((globals::WIDTH / globals::BLOCK_SIZE) - ((layer + 1) * 2))) + layer + 1;
            y = ((globals::HEIGHT/globals::BLOCK_SIZE) - layer - 1);
            break;
        case 3:
            x = layer;
            y = (rand() % ((globals::HEIGHT / globals::BLOCK_SIZE) - ((layer + 1) * 2))) + layer + 1;
            break;
        }

        layer += 2;

        sf::Vector2i newException;
        newException.x = x;
        newException.y = y;
        exclusions.push_back(newException);
    }
    return exclusions;
}

sf::Vector2f Maze::StartingPoint(){
    //Creates a random starting point somewhere along the edge and returns the position
    int side = rand() % 4;
    int x, y;

    switch(side){
    case 0:
        x = rand() % ((globals::WIDTH / globals::BLOCK_SIZE) - 2) + 1;
        x *= globals::BLOCK_SIZE;
        y = 0;
        break;
    case 1:
        x = globals::WIDTH - globals::BLOCK_SIZE;
        y = rand() % ((globals::HEIGHT / globals::BLOCK_SIZE) - 2) + 1;
        y *= globals::BLOCK_SIZE;
        break;
    case 2:
        x = rand() % ((globals::WIDTH / globals::BLOCK_SIZE) - 2) + 1;
        x *= globals::BLOCK_SIZE;
        y = globals::HEIGHT - globals::BLOCK_SIZE;
        break;
    case 3:
        x = 0;
        y = rand() % ((globals::HEIGHT / globals::BLOCK_SIZE) - 2) + 1;
        y *= globals::BLOCK_SIZE;
        break;
    }

    sf::Vector2f start(x, y);
    //std::cout << "Starting coordinates - X: " << start.x / 20 << " Y: " << start.y / 20 << std::endl;
    return start;
}

bool Maze::PartOfCircle(int x, int y){
    /*Calculates whether or not a rectangle being made is a part of the
    black concentric circles that form the walls of the maze*/
    if (y <= globals::HALF_HEIGHT && y % globals::D_BLOCK_SIZE == 0
    && x >= ((y / globals::D_BLOCK_SIZE) * 2) * globals::BLOCK_SIZE &&
    x - globals::BLOCK_SIZE <= globals::WIDTH - ((y / globals::D_BLOCK_SIZE + 1) * 2) * globals::BLOCK_SIZE){
        return true;
    }else if(y >= globals::HALF_WIDTH && y % globals::D_BLOCK_SIZE == 0 &&
    x - globals::BLOCK_SIZE <= ((y / globals::D_BLOCK_SIZE) * 2 - 1) * globals::BLOCK_SIZE &&
    x - globals::BLOCK_SIZE >= globals::WIDTH - ((y / globals::D_BLOCK_SIZE + 1) * 2) * globals::BLOCK_SIZE){
        return true;
    }else if(x <= globals::HALF_WIDTH && x % globals::D_BLOCK_SIZE == 0
    && y >= ((x / globals::D_BLOCK_SIZE) * 2) * globals::BLOCK_SIZE &&
    y - globals::BLOCK_SIZE <= globals::HEIGHT - ((x / globals::D_BLOCK_SIZE + 1) * 2) * globals::BLOCK_SIZE){
        return true;
    }else if(x >= globals::HALF_HEIGHT && x % globals::D_BLOCK_SIZE == 0 &&
    y - globals::BLOCK_SIZE <= ((x / globals::D_BLOCK_SIZE) * 2 - 1) * globals::BLOCK_SIZE &&
    y - globals::BLOCK_SIZE >= globals::HEIGHT - ((x / globals::D_BLOCK_SIZE + 1) * 2) * globals::BLOCK_SIZE){
        return true;
    }
    return false;
}

bool Maze::PartOfCenter(int x, int y){
    //Checks if given rectangle is part of the center a.k.a. the mazes end
    //x and y are actually pixel location, not block location
    if (x >= globals::HALF_WIDTH - (globals::BLOCK_SIZE * 2) &&
    x <= globals::HALF_WIDTH + globals::BLOCK_SIZE &&
    y >= globals::HALF_HEIGHT - (globals::BLOCK_SIZE * 2) &&
    y <= globals::HALF_HEIGHT + globals::BLOCK_SIZE){
        return true;
    }
    return false;
}

bool Maze::IsMazeSolved(){
    if (PartOfCenter(greenPos.x * globals::BLOCK_SIZE, greenPos.y * globals::BLOCK_SIZE)){
        return true;
    }
    return false;
}

bool Maze::SquareIsValid(sf::Vector2i pos){
    //Checks if a given square is open to movement
    if (maze[pos.x][pos.y].shape.getFillColor() == globals::black){
        return false;
    }
    return true;
}

bool Maze::SquareIsValid(sf::Color col){
    //Checks if a given square is open to movement
    if (col == globals::black){
        return false;
    }
    return true;
}
