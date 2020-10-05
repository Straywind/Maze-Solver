#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

namespace globals{
    const int WIDTH = 420, HEIGHT = 420;
    const int BLOCK_SIZE = 20; //Each individual block drawns size
    const int BLOCK_WIDTH_NUM = WIDTH/BLOCK_SIZE;
    const int BLOCK_HEIGHT_NUM = HEIGHT/BLOCK_SIZE;
    const int HALF_WIDTH = WIDTH/2, HALF_HEIGHT = HEIGHT/2;

    const int D_BLOCK_SIZE = BLOCK_SIZE * 2;
    const int up = 0, right = 1, down = 2, left = 3;

    const sf::Color black(0, 0, 0);
    const sf::Color white(255, 255, 255);
    const sf::Color red(255, 0, 0);
    const sf::Color green(0, 255, 0);
    const sf::Color darkGreen(0, 120, 0);
}

#endif // GLOBALS_H_INCLUDED
