#ifndef ASTEROID1_H
#define ASTEROID1_H
#include "abstract.h"


class Asteroid1 : public Abstract
{
private:
    int velocity_x_;
    int velocity_y_;
    int object_ID_ = 1;
public:
    Asteroid1(sf::Texture * texture, int life);
    void render(sf::RenderTarget& target);
    void animuj(const sf::Time &elapsed);
    void out_of_screen(sf::Vector2u size);
    bool collision(sf::FloatRect object);
    void to_center(sf::Vector2u size);
    std::pair<int, int>getVelocities();
    void create_asteroids(sf::RenderTarget &target);
    int get_ID();
};

#endif // ASTEROID1_H
