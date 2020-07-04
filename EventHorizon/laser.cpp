#include "laser.h"

Laser::Laser(sf::Texture *texture, sf::Vector2f pos)
{
    this->Sprite.setTexture(*texture);
    this->Sprite.setScale(0.07f, 0.07f);
    this->Sprite.setPosition(pos);
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
