#include "guy.h"

void guy::setBounds(int l_bound, int r_bound, int t_bound, int b_bound)
{
    bounds.top = t_bound;
    bounds.bottom = b_bound;
    bounds.left = l_bound;
    bounds.right = r_bound;
}

void guy::bounce(sf::FloatRect borders)
{
    
    sf::FloatRect guy_bounds = getGlobalBounds();
    
        //GORA
    if(guy_bounds.top <= borders.top)
    {
        setPosition(getPosition().x, getPosition().y-1 );
    }

    //DOL
   if(guy_bounds.top + guy_bounds.height >= borders.top+borders.height)
    {
        setPosition(getPosition().x, getPosition().y+1);
    }

    
// warunek na klawiaturę został wprowadzony, ponieważ ściany sa wąskie i oba warunki mogły być spełniane jednocześnie
    if(guy_bounds.left + guy_bounds.width >= borders.left  && sf::Keyboard::isKeyPressed(sf::Keyboard::Right ))
    {
//        std::cout<<" lewa: " << guy_bounds.left + guy_bounds.width << std::endl;
//        std::cout<<" >= " << borders.left << std:: endl;
        // to służyło do "debugowania" w konsoli
        
        setPosition(getPosition().x-1, getPosition().y);
       
    }
    
    if(guy_bounds.left <= borders.left+borders.width && sf::Keyboard::isKeyPressed(sf::Keyboard::Left) )
    {
//        std::cout<<" prawa; " << guy_bounds.left << std::endl;
//        std::cout<<" <= " << borders.left+borders.width << std:: endl;
         // to służyło do "debugowania" w konsoli
        velocity_x_ = -velocity_x_;
        setPosition(getPosition().x+1, getPosition().y);
        
    }
}

guy::guy(sf::Texture &textures)
{
    setTexture(textures);
}

void guy::animate(const sf::Time &elapsed)
{
    //bounce(sf::FloatRect(0,0,800,600));
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
