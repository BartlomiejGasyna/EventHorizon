#include "background.h"

Background::Background(float x, float y, sf::RenderWindow &window)
{


    if(!background1_texture_.loadFromFile("background base.png")) { std::cout<<"error";
    }

    if(!background2_texture_.loadFromFile("background base2.png")) { std::cout<<"error";
    }

    background1_texture_.setRepeated(true);
    this->background1_sprite_.setTexture(background1_texture_);
    this->background1_sprite_.setTextureRect(sf::IntRect(x, y, window.getSize().x, window.getSize().y));
    this->background1_sprite_.setScale(window.getSize().x/background1_texture_.getSize().x, window.getSize().y/background1_texture_.getSize().y);
    this->background1_sprite_.setOrigin(background1_sprite_.getLocalBounds().width/2, background1_sprite_.getLocalBounds().height/2);
    this->background1_sprite_.setPosition(window.getSize().x/2, window.getSize().y/2);

    this->background2_texture_.setRepeated(true);
    this->background2_sprite_.setTexture(background2_texture_);
    this->background2_sprite_.setTextureRect(sf::IntRect(x, y, window.getSize().x, window.getSize().y));
    this->background2_sprite_.setScale(window.getSize().x/background2_texture_.getSize().x, window.getSize().y/background2_texture_.getSize().y);
    this->background2_sprite_.setOrigin(background2_sprite_.getLocalBounds().width/2, background2_sprite_.getLocalBounds().height/2);
    this->background2_sprite_.setPosition(window.getSize().x/2, window.getSize().y/2);
}

void Background::render(sf::RenderTarget &target)
{
    target.draw(this->background1_sprite_);
    target.draw(this->background2_sprite_);
}

void Background::animuj(const sf::Time &elapsed)
{
    this->background1_sprite_.rotate(1.05*elapsed.asSeconds());
    this->background2_sprite_.rotate(-1.05*elapsed.asSeconds());
}
