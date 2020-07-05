#ifndef LASER_H
#define LASER_H
#include "abstract.h"


class Laser : public Abstract
{
private:
    float radians;
public:
    Laser(sf::Texture *texture, int pos_x_, int pos_y_, float rotation);
    ~Laser();
    void render(sf::RenderTarget& target);
    void animuj(const sf::Time &elapsed);
    void move();
};

#endif // LASER_H
