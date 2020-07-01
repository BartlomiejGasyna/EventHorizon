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
