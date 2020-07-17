#ifndef LASER_H
#define LASER_H
#include "abstract.h"

/*!
 * \brief The Laser class
 */
class Laser : public Abstract
{
private:
    float radians_;
    sf::Texture laser_texture_;
    sf::Sprite laser_sprite_;
public:
    Laser(int pos_x_, int pos_y_, float rotation);
    ~Laser();
    void render(sf::RenderTarget& target);
    void animuj(const sf::Time &elapsed);
};

#endif // LASER_H
