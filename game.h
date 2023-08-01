#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "paddle.h"
#include "brick.h"
#include "ball.h"

class Game {
public:
    Game();
    ~Game();

    void Init(sf::RenderWindow& window);
    void Update(int paddleDir, sf::RenderWindow& window); // update AI
    void Render(sf::RenderWindow& window); // draw
    bool IsGameOver();
    void Reset(sf::RenderWindow& window);

private:
    void BuildLvl();
    bool HitPaddle(int paddleX,int paddleY, int ballX, int ballY);
    void Generate();
    int CheckBounds(int ballX, int ballY);

public:
    const unsigned int width;
    const unsigned int height;
    unsigned int lvl;
    bool gameWon;

private:
    Paddle paddle;
    Brick brick;
    std::vector <Brick> bricks;
    Ball ball;
    sf::Font font;
    sf::Text text;
    sf::Music music1;
    sf::Music music2;
    unsigned int speedCounter;
    unsigned int resetSpeed;
    int dirY;
    int dirX;
    bool gameOver;
};

#endif
