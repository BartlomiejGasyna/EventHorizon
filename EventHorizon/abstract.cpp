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
void Abstract::out_of_screen(sf::Vector2u size)
{

}
bool Abstract::collision(sf::FloatRect object)
{
    
}
void Abstract::to_center(sf::Vector2u size)
{
    
}
std::pair<int, int> Abstract::getVelocities()
{
    
}

int Abstract::get_ID()
{

}
