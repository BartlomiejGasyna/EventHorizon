#include "bonus.h"

Bonus::Bonus()
{
    this->velocity_x_ = (rand() % 20-10)*10;
    this->velocity_y_ = (rand() % 20-10)*10;
    if(!bonus_texture_.loadFromFile("owoc.png")) { std::cout<<"error";
    }
    this->Sprite.setTexture(bonus_texture_);
}

Bonus::~Bonus()
{

}

void Bonus::render(sf::RenderTarget &target)
{
    target.draw(this->Sprite);
}

void Bonus::animuj(const sf::Time &elapsed)
{
    this->Sprite.move(velocity_x_*elapsed.asSeconds()*3, velocity_y_*elapsed.asSeconds()*3);
}

void Bonus::to_center(sf::Vector2u size)
{
    this->setPosition(size.x/2, size.y/2);
    this->velocity_x_ = (rand() % 20-10)*10;
    this->velocity_y_ = (rand() % 20-10)*10;
}

void Bonus::out_of_screen(sf::Vector2u size)
{
    if (Sprite.getPosition().x < 0 || Sprite.getPosition().x > size.x ||
        Sprite.getPosition().y < 0 || Sprite.getPosition().y > size.y)
    {
        this->to_center(size);
    }
}
