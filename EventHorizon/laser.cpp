#include "laser.h"

Laser::Laser(sf::Texture *texture, int pos_x_, int pos_y_)
{
    this->Sprite.setTexture(*texture);
    this->Sprite.setScale(0.07f, 0.07f);
    this->Sprite.setPosition(pos_x_, pos_y_);
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
