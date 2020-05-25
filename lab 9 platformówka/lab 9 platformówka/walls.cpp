#include "walls.h"

walls::walls()
{

}

walls::walls(sf::Texture &textures, float x_, float y_, const sf::IntRect &Bounds_)
{
    setTexture(textures);
    setPosition(x_,y_);
    setTextureRect(Bounds_);
}
