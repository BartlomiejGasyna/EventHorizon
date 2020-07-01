#include "spaceship.h"

Spaceship::Spaceship(float x, float y, sf::Texture* texture, int velocity_x, int velocity_y, sf::RenderTarget &target)
{
    this->setTexture(*texture);
    this->alpha = 10;
    this->r = 10;
    Sprite.setTextureRect(sf::IntRect(0, 0, 70, 72));
    Sprite.setPosition((target.getSize().x-texture->getSize().x)/2, (target.getSize().y-texture->getSize().y)/2);
    Sprite.setOrigin(x, y);
    Sprite.setScale(1.2,1.2);
}

void Spaceship::render(sf::RenderTarget &target)
{
    target.draw(this->Sprite);
}

void Spaceship::animuj(const sf::Time &elapsed)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        Sprite.rotate(50*elapsed.asSeconds());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        Sprite.rotate(-50*elapsed.asSeconds());
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        Sprite.move(-50*elapsed.asSeconds(), -50*elapsed.asSeconds());
    }
}

void Spaceship::draw(sf::RenderTarget &target, sf::RenderStates states)
{
    sf::RectangleShape sh;
    sf::Transform transform;
    transform.rotate(alpha);
    transform.translate(r, 0);
    states.transform.combine(transform);
    target.draw(sh, states);
}
