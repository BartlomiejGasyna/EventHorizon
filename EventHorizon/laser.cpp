#include "laser.h"

Laser::Laser(sf::Texture *texture, int pos_x_, int pos_y_, float rotation)
{
    this->Sprite.setTexture(*texture);
    this->Sprite.setScale(0.07f, 0.07f);
    this->Sprite.setPosition(pos_x_, pos_y_);
    this->radians = (rotation / 180) * M_PI;
}

Laser::~Laser()
{

}

void Laser::render(sf::RenderTarget &target)
{
    target.draw(this->Sprite);
}

void Laser::animuj(const sf::Time &elapsed)
{

}
void Laser::move()
{
    this->Sprite.move(4*sin(this->radians),-4*cos(this->radians));
}
