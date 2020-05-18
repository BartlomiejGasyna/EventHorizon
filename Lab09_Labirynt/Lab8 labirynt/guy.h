#ifndef GUY_H
#define GUY_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

struct Bounds
{
    int top = 0;
    int bottom = 0;
    int left = 0;
    int right = 0;
};

class guy : public sf::Sprite
{
private:
    float velocity_x_ = 0;
    float velocity_y_ = 0;
    float velocity_o_ = 0;
    
    
public:
    void bounce(sf::FloatRect borders);
    Bounds bounds;
    guy(sf::Texture &textures);
    void animate(const sf::Time &elapsed);
    void setBounds(int l_bound, int r_bound, int t_bound, int b_bound);
};

class object : public sf::Sprite
{
private:
    
public:
    object(sf::Texture &textures, float x, float y, const sf::IntRect &Bounds)
    {
        setTexture(textures);
        setPosition(x,y);
        setTextureRect(Bounds);
    }
    std::vector<std::unique_ptr<sf::Drawable>> create_shapes(
                                                             const std::vector<sf::Texture> &textures);
};
#endif // GUY_H
