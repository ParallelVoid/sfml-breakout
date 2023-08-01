#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include "coord.h"
#include "common.h"

class Ball {
public:
    Ball();
    ~Ball();

    void Init();
    void Update();
    void Draw(sf::RenderWindow& window);
    void Move(int dirY, int dirX);
    int GetX();
    int GetY();

private:
    const unsigned int radius;
    unsigned int y;
    unsigned int x;

    sf::CircleShape circle;
};

#endif
