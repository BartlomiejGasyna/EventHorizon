#ifndef LASER_H
#define LASER_H
#include "abstract.h"


class Laser : public Abstract
{
public:
    Laser(sf::Texture *texture, int pos_x_, int pos_y_);
    ~Laser();
    void render(sf::RenderTarget& target);
    void animuj(const sf::Time &elapsed);
};

#endif // LASER_H
