#include "ASharp.h"

ASharp::ASharp(Maze *NMZ){
    MZ = NMZ;

    //Set all closedList items to false
    std::memset(closedList, false, sizeof(closedList));

    //Uses A* algorithm to find the fastest solution through the maze
    sf::Vector2i curPos = MZ->greenPos;
    sf::Vector2i centerPos = MZ->centerPos;
    std::vector<std::vector<block>> maze = MZ->maze;

    maze[curPos.x][curPos.y].fCost = 0.0;
    maze[curPos.x][curPos.y].gCost = 0.0;
    maze[curPos.x][curPos.y].hCost = 0.0;
    maze[curPos.x][curPos.y].parentPos = curPos;
    openList.emplace_back(maze[curPos.x][curPos.y]);

    while (!openList.empty() && openList.size() < (globals::WIDTH/globals::BLOCK_SIZE) * (globals::HEIGHT/globals::BLOCK_SIZE)){
        block route = *openList.begin();

        openList.erase(openList.begin());

        curPos = route.pos;
        closedList[curPos.x][curPos.y] = true;

        double fNew, gNew, hNew;
        for (int i = 0; i < 4; i++){
            int curNeighbourX = curPos.x, curNeighbourY = curPos.y;
            bool shouldProcess = false; //If a block should not be processed, this prevents it from being done
                                        //i.e. block does not exist

            switch(i){
            case 0:
                if (curPos.y != 0){
                    curNeighbourY -= 1;
                    shouldProcess = true;
                }
                break;
            case 1:
                if (curPos.x != globals::BLOCK_WIDTH_NUM - 1){
                    curNeighbourX += 1;
                    shouldProcess = true;
                }
                break;
            case 2:
                if (curPos.y != globals::BLOCK_HEIGHT_NUM - 1){
                    curNeighbourY += 1;
                    shouldProcess = true;
                }
                break;
            case 3:
                if (curPos.x != 0){
                    curNeighbourX -= 1;
                    shouldProcess = true;
                }
                break;
            }

            if (shouldProcess){
                if (MZ->SquareIsValid(maze[curNeighbourX][curNeighbourY].shape.getFillColor())){
                    if (maze[curNeighbourX][curNeighbourY].shape.getFillColor() == globals::red){
                        //A route is found, path is now made
                        MZ->maze[curNeighbourX][curNeighbourY].parentPos = curPos;
                        MZ->centerPos.x = curNeighbourX; //Must be assigned here because program will otherwise attempt accessing -1 position (assigned to each parent pos in maze ctor)
                        MZ->centerPos.y = curNeighbourY;
                        path = makePath();
                    }else if(!closedList[curNeighbourX][curNeighbourY]){
                        gNew = route.gCost + 1.0;
                        hNew = CalculateHeuristic(curNeighbourX, curNeighbourY, centerPos);
                        fNew = gNew + hNew;

                        //Checks if this path is better than the one previous
                        if (MZ->maze[curNeighbourX][curNeighbourY].fCost == FLT_MAX ||
                            MZ->maze[curNeighbourX][curNeighbourY].fCost > fNew){
                            MZ->maze[curNeighbourX][curNeighbourY].fCost = fNew;
                            MZ->maze[curNeighbourX][curNeighbourY].gCost = gNew;
                            MZ->maze[curNeighbourX][curNeighbourY].hCost = hNew;
                            MZ->maze[curNeighbourX][curNeighbourY].parentPos = curPos;
                            openList.emplace_back(MZ->maze[curNeighbourX][curNeighbourY]);
                        }
                    }
                }
            }
            shouldProcess = false;
        }
    }

    if (path.empty()){
        std::cout << "Maze has no solution" << std::endl;
    }
}

double ASharp::CalculateHeuristic(int x, int y, sf::Vector2i pos){
    //Returns the "h" value for A* algorithm. h is an appoximation of distance from a point to the mazes end.
    //h must not be greater than the actual distance
    double h = (sqrt((x - pos.x)*(x - pos.x)
            + (y - pos.y)*(y - pos.y)));
    return h;
}

std::vector<block> ASharp::makePath(){
    //Creates a path from start to finish
    std::cout << "Found path";
    int x = MZ->centerPos.x;
    int y = MZ->centerPos.y;
    std::stack<block> path;
    std::vector<block> usablePath;

    while (!(MZ->maze[x][y].parentPos.x != x &&
    MZ->maze[x][y].parentPos.y != y)){
        path.push(MZ->maze[x][y]);
        MZ->maze[x][y].shape.setFillColor(globals::green);
        x = MZ->maze[x][y].parentPos.x;
        y = MZ->maze[x][y].parentPos.y;
    }
    path.push(MZ->maze[x][y]);

    while (!path.empty()){
        block top = path.top();
        path.pop();
        usablePath.emplace_back(top);
    }

    return usablePath;
}
