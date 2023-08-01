#ifndef PADDLE_H
#define PADDLE_H

#include <SFML/Graphics.hpp>

class Paddle{
public:
    Paddle();
    ~Paddle();

    void Init();
    void Update();
    void Draw(sf::RenderWindow& window);
    void Reset();
    void Move(int dir, sf::RenderWindow& window);
    int GetX();
    int GetY();

private:
    const unsigned int height;
    const unsigned int width;
    int x;
    int y;

    sf::RectangleShape rectangle;
};

#endif
