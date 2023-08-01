#ifndef BRICK_H
#define BRICK_H

#include <SFML/Graphics.hpp>
#include "coord.h"

class Brick {
public:
    Brick();
    ~Brick();

    void Init(int x, int y, int colour);
    void Update();
    void Draw(sf::RenderWindow& window);
    bool Hit(int x, int y) const;

private:

    unsigned int height;
    unsigned int width;

    sf::RectangleShape rectangle;
};

#endif
