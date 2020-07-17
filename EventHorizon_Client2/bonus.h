#ifndef BONUS_H
#define BONUS_H
#include "abstract.h"


/*!
 * \brief The Bonus class
 */
class Bonus : public Abstract
{
    sf::Texture bonus_texture_;
    sf::Sprite bonus_sprite_;
    int velocity_x_;
    int velocity_y_;
    int object_ID_ = 2;
public:
    Bonus();
    ~Bonus();
    void render(sf::RenderTarget& target);
    void animuj(const sf::Time &elapsed);
    void to_center(sf::Vector2u size);
    void out_of_screen(sf::Vector2u size);
    int get_object_ID();
};

#endif // BONUS_H
