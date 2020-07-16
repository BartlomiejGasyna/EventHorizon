#ifndef ASTEROID1_H
#define ASTEROID1_H
#include "abstract.h"


class Asteroid1 : public Abstract
{
private:
    int velocity_x_;
    int velocity_y_;
    int asteroid_ID_;
    int object_ID_ = 1;
    //int HP;
public:
    Asteroid1(sf::Texture * texture, int life);
    void render(sf::RenderTarget& target);
    void animuj(const sf::Time &elapsed);
    void out_of_screen(sf::Vector2u size);
    bool collision(sf::FloatRect object);
    void to_center(sf::Vector2u size);
    std::pair<int, int>getVelocities();
    void set_asteroid_ID(int ID);
    int get_asteroid_ID();
    int get_object_ID();
    void reduce_HP(int damage);
};

#endif // ASTEROID1_H
