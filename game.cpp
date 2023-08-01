#include "game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "common.h"

//#define DEBUG_TEST 1

Game::Game()
    :width(CELL*XCELLS)
    ,height(CELL*YCELLS)
    ,lvl(0)
    ,gameWon(false)
    ,speedCounter(0)
    ,resetSpeed(250)
    ,dirY(DOWN)
    ,dirX(1)
    ,gameOver(false) {
    
    }

Game::~Game() {

}

void Game::Init(sf::RenderWindow& window){
    if (!font.loadFromFile("font.ttf")) {
        std::cout<<"Font not loaded"<<std::endl;
    }
    if (!music1.openFromFile("ping_pong_8bit_plop.ogg")) {
        std::cout<<"Sound not loaded"<<std::endl;
    }
    if (!music2.openFromFile("ping_pong_8bit_beeep.ogg")) {
        std::cout<<"Sound not loaded"<<std::endl;
    }

    paddle.Init();
    ball.Init();
    BuildLvl();
}

void Game::Update(int paddleDir, sf::RenderWindow& window) {
    if (gameOver || gameWon) {
        return;
    }

    speedCounter --;
    if (speedCounter % resetSpeed == 0) {
        speedCounter = resetSpeed;
        ball.Move(dirY, dirX);
        int BallX = ball.GetX();
        int BallY = ball.GetY();
        int PaddleX = paddle.GetX();
        int PaddleY = paddle.GetY();
        bool hit = HitPaddle(PaddleX,PaddleY,BallX,BallY);
        if (hit == true) {
            dirY = UP;
            int oneInFive;
            oneInFive = rand() % 5;
            if (oneInFive == 3) {
                dirX = -dirX;
            }
        }
        else {
            for(auto it = bricks.begin(); it != bricks.end();) {
                if ((*it).Hit(BallX, BallY)) {
                    music2.play();
                    bricks.erase(it);
                    if (bricks.size() == 0){
                        gameWon = true;
                    }
                    dirY = DOWN;
                    break;
                }
                else {
                    ++it;
                }
            }
            int bounds = CheckBounds(BallX,BallY);
            switch (bounds) {
                case BOTTOM:
                    gameOver = true;
                    break;
                case TOP:
                    dirY = DOWN;
                    break;
                case SIDE1:
                    dirX = -dirX;
                    break;
                case SIDE2:
                    dirX = -dirX;
                    break;
                default:
                    break;
            }
        }
    }

    paddle.Move(paddleDir, window);
}

void Game::Render(sf::RenderWindow& window) {
    paddle.Draw(window);
    ball.Draw(window);
    for (auto brick: bricks) {
        brick.Draw(window);
    }

    if(gameWon == true) {

        text.setFont(font); // font is a sf::Font
        text.setString("LEVEL COMPLETE!");
        text.setCharacterSize(40); // in pixels, not points!
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        text.setPosition(width/8 + CELL/4, height/3);
        window.draw(text);

        text.setString("Press SPACE to Continue");
        text.setCharacterSize(25); // in pixels, not points!
        text.setFillColor(sf::Color::Green);
        text.setPosition(width/8 + CELL/4, height/2 + 64);
        window.draw(text);
    }

    else if (IsGameOver()) {
        text.setFont(font); // font is a sf::Font
        text.setString("GAME OVER");
        text.setCharacterSize(64); // in pixels, not points!
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Bold | sf::Text::Underlined);
        text.setPosition(width/6, height/3);
        window.draw(text);

        text.setString("Press SPACE to Play Again");
        text.setCharacterSize(25); // in pixels, not points!
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Underlined);
        text.setPosition(width/8 + CELL/4, height/2 + 64);
        window.draw(text);

        std::string scoreString;
        std::string tempString;
        scoreString = "You lost on lvl ";
        tempString = std::to_string(lvl + 1);
        scoreString = scoreString + tempString;

        text.setString(scoreString);
        text.setCharacterSize(25); // in pixels, not points!
        text.setFillColor(sf::Color::Green);
        text.setStyle(sf::Text::Underlined);
        text.setPosition(width/4, height/2 + 2*CELL);
        window.draw(text);
    }
}

void Game::BuildLvl() {
#ifdef DEBUG_TEST
    for (int brickX = 0; brickX < 3; brickX++) {
        for (int brickY = 0; brickY < 1; brickY++) {
            brick.Init(CELL*brickX, CELL*brickY/2, brickY);
            bricks.push_back(brick);
        }
    }
    return;
#endif

    for (int brickX = 0; brickX < XCELLS; brickX++) {
        for (int brickY = 0; brickY < 4+lvl; brickY++) {
            brick.Init(CELL*brickX, CELL*brickY/2, brickY);
            bricks.push_back(brick);
        }
    }
}

bool Game::IsGameOver() {
    return gameOver;
}

void Game::Reset(sf::RenderWindow& window) {
    gameOver = false;
    gameWon = false;
    dirY = DOWN;
    dirX = 1;
    bricks.clear();
    Init(window);
}

bool Game::HitPaddle(int PaddleX,int PaddleY, int BallX, int BallY) {
    if (PaddleY == (BallY + CELL/2) && PaddleX <= BallX && (PaddleX + 2*CELL) >= BallX) {
        music1.play();
        return true;
    }
    return false;
}

// returns which side of the screen has been hit
int Game::CheckBounds(int ballX, int ballY) {
    if (ballY == 0) {
        return TOP;
    }
    else if (ballX == 0) {
        return SIDE1;
    }
    else if (ballX == (XCELLS*CELL - CELL/4)) {
        return SIDE2;
    }
    else if (ballY == YCELLS*CELL) {
        return BOTTOM;
    }
    return NONE;
}
