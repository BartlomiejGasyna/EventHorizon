#ifndef ABSTRACT_H
#define ABSTRACT_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

class Abstract : public sf::Sprite
{
public:
    Abstract();
    virtual ~Abstract();
    sf::Sprite Sprite;
    virtual void setTexture(sf::Texture& texture);
    virtual void setPosition(const float x, const float y);
    virtual void render(sf::RenderTarget& target) = 0;
    virtual void animuj(const sf::Time &elapsed) = 0;
    virtual void move(const float x, const float y);
};

#endif // ABSTRACT_H
