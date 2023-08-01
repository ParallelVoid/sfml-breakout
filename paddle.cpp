#include "paddle.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "common.h"

Paddle::Paddle()
    :height(CELL*2)
    ,width(CELL)
    ,x(0)
    ,y(8*CELL) {

}

Paddle::~Paddle() {
    
}

void Paddle::Init() {
    rectangle.setSize(sf::Vector2f(height, width));
    rectangle.setPosition(x,y);
    rectangle.setFillColor(sf::Color::Red);
}

void Paddle::Update() {
    // update the paddle
}

void Paddle::Draw(sf::RenderWindow& window) {
    window.draw(rectangle);
}

void Paddle::Reset() {
    //reset when game restarts
}

void Paddle::Move(int dir, sf::RenderWindow& window) {
    if (dir == RIGHT && (x + CELL) < CELL*(XCELLS - 1)) {
        x += CELL/4;
    }
    if (dir == LEFT && x > NONE) {
        x -= CELL/4;
    }
    rectangle.setPosition(x,y);
}

int Paddle::GetX() {
    return x;
}

int Paddle::GetY() {
    return y;
}
