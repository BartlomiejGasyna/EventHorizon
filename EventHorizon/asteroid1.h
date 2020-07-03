#ifndef ASTEROID1_H
#define ASTEROID1_H
#include "abstract.h"


class Asteroid1 : public Abstract
{
private:
    int velocity_x_;
    int velocity_y_;
public:
    Asteroid1(float x, float y, sf::Texture * texture);
    void render(sf::RenderTarget& target);
    void animuj(const sf::Time &elapsed);
    void out_of_screen(sf::Vector2u size);
    bool collision(sf::FloatRect object);
    void to_center(sf::Vector2u size);
};

#endif // ASTEROID1_H
