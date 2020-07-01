#include "asteroid1.h"

Asteroid1::Asteroid1(float x, float y, sf::Texture *texture, int velocity_x, int velocity_y)
{
    this->setTexture(*texture);
    this->setPosition(x, y);
    this->velocity_y_ = velocity_y;
    this->velocity_x_ = velocity_x;
}

void Asteroid1::render(sf::RenderTarget &target)
{
    target.draw(this->Sprite);
}

void Asteroid1::animuj(const sf::Time &elapsed)
{
    this->move(velocity_x_*elapsed.asSeconds(), velocity_y_*elapsed.asSeconds());
}
