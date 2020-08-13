#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#define here std::cout << "Here"

const int WIDTH = 420, HEIGHT = 420;
const int HALF_WIDTH = WIDTH/2, HALF_HEIGHT = HEIGHT/2;
const int BLOCK_SIZE = 20; //Each individual block drawns size
const int D_BLOCK_SIZE = BLOCK_SIZE * 2;
const int up = 0, right = 1, down = 2, left = 3;

bool MAZE_SOLVED = false;
bool moved = false;

sf::RectangleShape maze[WIDTH/BLOCK_SIZE][HEIGHT/BLOCK_SIZE];

sf::Color black(0, 0, 0);
sf::Color white(255, 255, 255);
sf::Color red(255, 0, 0);
sf::Color green(0, 255, 0);
sf::Color darkGreen(0, 120, 0);

sf::Vector2i greenPos;
std::vector<sf::Vector2i> exclusions; //Vector of holes in the concentric circles of the maze, to allow path to the center

bool PartOfCircle(int x, int y){
    /*Calculates whether or not a rectangle being made is a part of the
    black concentric circles that forms the basis of the maze*/
    if (y <= HALF_HEIGHT && y % D_BLOCK_SIZE == 0
    && x >= ((y / D_BLOCK_SIZE) * 2) * BLOCK_SIZE &&
    x - BLOCK_SIZE <= WIDTH - ((y / D_BLOCK_SIZE + 1) * 2) * BLOCK_SIZE){
        return true;
    }else if(y >= HALF_WIDTH && y % D_BLOCK_SIZE == 0 &&
    x - BLOCK_SIZE <= ((y / D_BLOCK_SIZE) * 2 - 1) * BLOCK_SIZE &&
    x - BLOCK_SIZE >= WIDTH - ((y / D_BLOCK_SIZE + 1) * 2) * BLOCK_SIZE){
        return true;
    }else if(x <= HALF_WIDTH && x % D_BLOCK_SIZE == 0
    && y >= ((x / D_BLOCK_SIZE) * 2) * BLOCK_SIZE &&
    y - BLOCK_SIZE <= HEIGHT - ((x / D_BLOCK_SIZE + 1) * 2) * BLOCK_SIZE){
        return true;
    }else if(x >= HALF_HEIGHT && x % D_BLOCK_SIZE == 0 &&
    y - BLOCK_SIZE <= ((x / D_BLOCK_SIZE) * 2 - 1) * BLOCK_SIZE &&
    y - BLOCK_SIZE >= HEIGHT - ((x / D_BLOCK_SIZE + 1) * 2) * BLOCK_SIZE){
        return true;
    }
    return false;
}

bool PartOfCenter(int x, int y){
    //Checks if given rectangle is part of the center a.k.a. the mazes end
    if (x >= HALF_WIDTH - (BLOCK_SIZE * 2) &&
    x <= HALF_WIDTH + BLOCK_SIZE &&
    y >= HALF_HEIGHT - (BLOCK_SIZE * 2) &&
    y <= HALF_HEIGHT + BLOCK_SIZE){
        return true;
    }
    return false;
}

sf::Vector2f StartingPoint(){
    //Creates a random starting point somewhere along the edge and returns the position
    int side = rand() % 4;
    int x, y;

    switch(side){
    case 0:
        x = 0;
        y = rand() % ((HEIGHT / BLOCK_SIZE) + 2) + 1;
        y *= BLOCK_SIZE;
        break;
    case 1:
        x = WIDTH - BLOCK_SIZE;
        y = rand() % ((HEIGHT / BLOCK_SIZE) + 2) + 1;
        y *= BLOCK_SIZE;
        break;
    case 2:
        x = rand() % ((WIDTH / BLOCK_SIZE) + 2) + 1;
        x *= BLOCK_SIZE;
        y = 0;
        break;
    case 3:
        x = rand() % ((WIDTH / BLOCK_SIZE) + 2) + 1;
        x *= BLOCK_SIZE;
        y = HEIGHT - BLOCK_SIZE;
        break;
    }

    sf::Vector2f start(x, y);
    return start;
}

void CreateBlockExceptions(){
    //Creates a certain number of blocking points that is checked in CreateMaze
    static int layer = 2;

    for (int i = 0; i <= 3; i++){
        int side = rand() % 4;
        int x, y;
        switch(side){
        case 0:
            x = (rand() % ((WIDTH/BLOCK_SIZE) - ((layer + 1) * 2))) + layer + 1;
            y = layer;
            break;
        case 1:
            x = (WIDTH/BLOCK_SIZE) - layer - 1;
            y = (rand() % ((HEIGHT/BLOCK_SIZE) - ((layer + 1) * 2))) + layer + 1;
            break;
        case 2:
            x = (rand() % ((WIDTH/BLOCK_SIZE) - ((layer + 1) * 2))) + layer + 1;
            y = ((HEIGHT/BLOCK_SIZE) - layer - 1);
            break;
        case 3:
            x = layer;
            y = (rand() % ((HEIGHT/BLOCK_SIZE) - ((layer + 1) * 2))) + layer + 1;
            break;
        }

        layer += 2;

        sf::Vector2i newException;
        newException.x = x;
        newException.y = y;
        exclusions.push_back(newException);
    }
}

void CreateMaze(){
    //Creates the maze
    sf::Vector2f start = StartingPoint();

    for (int x = 0; x < WIDTH; x += BLOCK_SIZE){
        for (int y = 0; y < HEIGHT; y += BLOCK_SIZE){
            sf::RectangleShape rec;
            rec.setSize(sf::Vector2f(BLOCK_SIZE, BLOCK_SIZE));
            rec.setPosition(x, y);

            ///Creates basic grid
            if (PartOfCircle(x, y)){
                rec.setFillColor(black);
            }else{

                rec.setFillColor(white);
            }
            if (PartOfCenter(x, y)){
                rec.setFillColor(red);
            }

            ///Starting point
            if (rec.getPosition() == start){
                rec.setFillColor(green);
                greenPos.x = x/BLOCK_SIZE;
                greenPos.y = y/BLOCK_SIZE;
            }

            maze[x/BLOCK_SIZE][y/BLOCK_SIZE] = rec;
        }
    }

    CreateBlockExceptions();
    for (int k = 0; k < exclusions.size(); k++){
        maze[exclusions[k].x][exclusions[k].y].setFillColor(white);
    }
}

void MoveGreenSquare(int direction){
    //Will move the green square in a direction IF AND ONLY IF there is not a black square in that direction
    sf::Color squareCol;
    switch (direction){
    case up:
        squareCol = maze[greenPos.x][greenPos.y - 1].getFillColor();
        if (squareCol != black){
            maze[greenPos.x][greenPos.y - 1].setFillColor(green);
            if (squareCol != darkGreen){
                maze[greenPos.x][greenPos.y].setFillColor(darkGreen);
            }else{
                maze[greenPos.x][greenPos.y].setFillColor(white);
            }
            greenPos.y -= 1;
        }
        break;
    case right:
        squareCol = maze[greenPos.x + 1][greenPos.y].getFillColor();
        if (squareCol != black){
            maze[greenPos.x + 1][greenPos.y].setFillColor(green);
            if (squareCol != darkGreen){
                maze[greenPos.x][greenPos.y].setFillColor(darkGreen);
            }else{
                maze[greenPos.x][greenPos.y].setFillColor(white);
            }
            greenPos.x += 1;
        }
        break;
    case down:
        squareCol = maze[greenPos.x][greenPos.y + 1].getFillColor();
        if (squareCol != black){
            maze[greenPos.x][greenPos.y + 1].setFillColor(green);
            if (squareCol != darkGreen){
                maze[greenPos.x][greenPos.y].setFillColor(darkGreen);
            }else{
                maze[greenPos.x][greenPos.y].setFillColor(white);
            }
            greenPos.y += 1;
        }
        break;
    case left:
        squareCol = maze[greenPos.x - 1][greenPos.y].getFillColor();
        if (squareCol != black){
            maze[greenPos.x - 1][greenPos.y].setFillColor(green);
            if (squareCol != darkGreen){
                maze[greenPos.x][greenPos.y].setFillColor(darkGreen);
            }else{
                maze[greenPos.x][greenPos.y].setFillColor(white);
            }            greenPos.x -= 1;
        }
        break;
    }

    if (squareCol == red){
        MAZE_SOLVED = true;
        std::cout << "Maze has been solved!";
    }
}

int main(){
    srand(time(NULL));
    CreateMaze();

    // Create the main window
    sf::RenderWindow app(sf::VideoMode(WIDTH, HEIGHT), "Maze");

	// Start the game loop
    while (app.isOpen()){
        // Process events
        sf::Event event;
        while (app.pollEvent(event)){
            // Close window : exit
            if (event.type == sf::Event::Closed){
                app.close();
            }
        }

        if (!MAZE_SOLVED){
            ///Controls
            if (!moved){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
                    MoveGreenSquare(up);
                    moved = true;
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                    MoveGreenSquare(down);
                    moved = true;
                }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    MoveGreenSquare(left);
                    moved = true;
                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    MoveGreenSquare(right);
                    moved = true;
                }
            }
            if (event.type == sf::Event::KeyReleased){
                moved = false;
            }

            // Clear screen
            app.clear();

            //Draw all rects
            for (int i = 0; i < WIDTH/BLOCK_SIZE; i++){
                for (int j = 0; j < HEIGHT/BLOCK_SIZE; j++){
                    app.draw(maze[i][j]);
                }

            }

            // Update the window
            app.display();
        }
    }

    return EXIT_SUCCESS;
}
