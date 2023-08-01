#include "ball.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Ball::Ball()
    :radius(CELL/4) {

    }

Ball::~Ball() {

}

void Ball::Init() {
    x = CELL*XCELLS/2;
    y = CELL*YCELLS/2;
    circle.setRadius(radius);
    circle.setPosition(x,y);
    circle.setFillColor(sf::Color::White);
}

void Ball::Update() {

}

void Ball::Draw(sf::RenderWindow& window) {
    window.draw(circle);
}

void Ball::Move(int dirY, int dirX) {
    y = y - (CELL/4)*dirY;
    x = x - (CELL/4)*dirX;
    circle.setPosition(x,y);
}

int Ball::GetX() {
    return x;
}

int Ball::GetY() {
    return y;
}
