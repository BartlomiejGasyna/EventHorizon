#ifndef GUY_H
#define GUY_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

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
    Bounds bounds;
    void bounce();
public:
    guy(sf::Texture &textures);
    void animate(const sf::Time &elapsed);
    void setBounds(int l_bound, int r_bound, int t_bound, int b_bound);
};
#endif // GUY_H
