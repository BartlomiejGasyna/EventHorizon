#include "guy.h"

void guy::setBounds(int l_bound, int r_bound, int t_bound, int b_bound)
{
    bounds.top = t_bound;
    bounds.bottom = b_bound;
    bounds.left = l_bound;
    bounds.right = r_bound;
}

void guy::bounce()
{
    sf::FloatRect guy_bounds = getGlobalBounds();
    if(guy_bounds.top <= bounds.top)
    {
        velocity_y_ = 0;
        setPosition(getPosition().x, 0);
    }
    if(guy_bounds.top + guy_bounds.height >= bounds.bottom)
    {
        velocity_y_ = 0;
        setPosition(getPosition().x, bounds.bottom-guy_bounds.height);
    }
    if(guy_bounds.left <= bounds.left)
    {
        velocity_x_ = 0;
        setPosition(0, getPosition().y);
    }
    if(guy_bounds.left + guy_bounds.width >= bounds.right)
    {
        velocity_x_ = 0;
        setPosition(bounds.right-guy_bounds.width, getPosition().y);
    }
}

guy::guy(sf::Texture &textures)
{
    setTexture(textures);
}

void guy::animate(const sf::Time &elapsed)
{
    bounce();
    sf::FloatRect guy_bounds = getGlobalBounds();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(guy_bounds.top > bounds.top)
        {
            move(0, -400*elapsed.asSeconds());
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(guy_bounds.top+guy_bounds.height < bounds.bottom)
        {
            move(0, 400*elapsed.asSeconds());
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(guy_bounds.left > bounds.left)
        {
            move(-400*elapsed.asSeconds(), 0);
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(guy_bounds.left+guy_bounds.width < bounds.right)
        {
            move(400*elapsed.asSeconds(), 0);
        }
    }
}
