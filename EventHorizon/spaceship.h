#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "abstract.h"

class Spaceship : public Abstract
{
public:
private:
    int velocity_y_;
    int velocity_x_;
    float alpha;
    float r;
public:
    int hp;
    int points;
    Spaceship(float x, float y,  sf::Texture* texture, int velocity_x, int velocity_y, sf::RenderTarget &target);
    void render(sf::RenderTarget& target);
    void animuj(const sf::Time &elapsed);
    void draw(sf::RenderTarget &target, sf::RenderStates states);
};

#endif // SPACESHIP_H
