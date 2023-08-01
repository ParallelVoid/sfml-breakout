#include "brick.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "common.h"

Brick::Brick()
    :height(CELL/2)
    ,width(CELL-2) {

}

Brick::~Brick() {

}

void Brick::Init(int x, int y, int colour) {
    rectangle.setSize(sf::Vector2f(width, height));
    rectangle.setPosition(x,y);
    if (colour%2 == 0) {
        rectangle.setFillColor(sf::Color::Yellow);
    }
    else {
        rectangle.setFillColor(sf::Color(255,128,0));
    }
}

void Brick::Update() {

}

void Brick::Draw(sf::RenderWindow& window) {
    window.draw(rectangle);
}

bool Brick::Hit(int x, int y) const {
    int bx = rectangle.getPosition().x;
    int by = rectangle.getPosition().y;
    if (bx <= x && bx + width >= x && by <= y && by + height >= y) {
        return true;
    }
    return false;
}
