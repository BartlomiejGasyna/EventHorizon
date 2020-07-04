#ifndef LASER_H
#define LASER_H
#include "abstract.h"


class Laser : public Abstract
{
public:
    Laser(sf::Texture *texture, sf::Vector2f pos);
    ~Laser();
    void render(sf::RenderTarget& target);
    void animuj(const sf::Time &elapsed);
};

#endif // LASER_H
