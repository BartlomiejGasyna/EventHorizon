#ifndef WALLS_H
#define WALLS_H

#include "elementsceny.h"

class walls : public ElementSceny
{
public:
    walls();
    walls(sf::Texture &textures, float x_, float y_, const sf::IntRect &Bounds_);
};

#endif // WALLS_H
