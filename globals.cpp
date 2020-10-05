#include <SFML/Graphics.hpp>

const int WIDTH = 420, HEIGHT = 420;
const int HALF_WIDTH = WIDTH/2, HALF_HEIGHT = HEIGHT/2;
const int BLOCK_SIZE = 20; //Each individual block drawns size
const int D_BLOCK_SIZE = BLOCK_SIZE * 2;
const int up = 0, right = 1, down = 2, left = 3;

sf::Color black(0, 0, 0);
sf::Color white(255, 255, 255);
sf::Color red(255, 0, 0);
sf::Color green(0, 255, 0);
sf::Color darkGreen(0, 120, 0);
