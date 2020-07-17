#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "abstract.h"


/*!
 * \brief The Background class
 */
class Background : public Abstract
{
private:
    sf::Texture background1_texture_;
    sf::Texture background2_texture_;
    sf::Sprite background1_sprite_;
    sf::Sprite background2_sprite_;
public:
    Background(float x, float y, sf::RenderWindow &window);
    void render(sf::RenderTarget& target);
    void animuj(const sf::Time &elapsed);
};

#endif // BACKGROUND_H
