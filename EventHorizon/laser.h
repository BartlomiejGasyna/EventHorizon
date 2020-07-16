#ifndef LASER_H
#define LASER_H
#include "abstract.h"


class Laser : public Abstract
{
private:
    float radians;
    sf::Texture laser_texture_;
    sf::Sprite laser_sprite_;
public:
    Laser(int pos_x_, int pos_y_, float rotation);
    ~Laser();
    void render(sf::RenderTarget& target);
    void animuj(const sf::Time &elapsed);
    void move();
};

#endif // LASER_H
