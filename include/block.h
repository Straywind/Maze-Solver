#ifndef BLOCK_H_INCLUDED
#define BLOCK_H_INCLUDED

struct block{
    sf::Vector2i pos;
    sf::Vector2i parentPos;
    sf::RectangleShape shape;
    float gCost;
    float hCost;
    float fCost;
};


#endif // BLOCK_H_INCLUDED
