#include "spaceship.h"

Spaceship::Spaceship(float x, float y, sf::Texture &texture, int velocity_x, int velocity_y, sf::RenderTarget &target)
{
    alpha = 10;
    r = 10;
    setOrigin(31,-435);
    setPosition(x, y);
    setScale(1.2, 1.2);
    setTextureRect(sf::IntRect(0,0,70,72));
    setTexture(texture);
    

}

void Spaceship::render(sf::RenderTarget &target)
{
    target.draw(this->Sprite);
}

void Spaceship::animuj(const sf::Time &elapsed)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        rotate(50*elapsed.asSeconds());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        rotate(-50*elapsed.asSeconds());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        move(-50*elapsed.asSeconds(), -50*elapsed.asSeconds());
    }
}

//void Spaceship::draw(sf::RenderTarget &target, sf::RenderStates states)
//{
//    sf::RectangleShape sh;
//    sf::Transform transform;
//    transform.rotate(alpha);
//    transform.translate(r, 0);
//    states.transform.combine(transform);
//    target.draw(sh, states);
//}
