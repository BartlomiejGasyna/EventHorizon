#include "abstract.h"

Abstract::Abstract()
{

}

Abstract::~Abstract()
{

}

void Abstract::setTexture(sf::Texture &texture)
{
    this->Sprite.setTexture(texture);
}

void Abstract::setPosition(const float x, const float y)
{
    this->Sprite.setPosition(x, y);
}

void Abstract::move(const float x, const float y)
{
    this->Sprite.move({ x, y });
}
bool Abstract::out_of_screen(sf::Vector2u size)
{
    if (Sprite.getPosition().x < 0 || Sprite.getPosition().x > size.x ||
        Sprite.getPosition().y < 0 || Sprite.getPosition().y > size.y)
    {
        Sprite.setPosition(size.x/2,size.y/2);
        return true;
    }
}
