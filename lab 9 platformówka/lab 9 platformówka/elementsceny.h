#ifndef ELEMENTSCENY_H
#define ELEMENTSCENY_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

struct Edge
{
    int top = 0;
    int bottom = 0;
    int left = 0;
    int right = 0;
};

class ElementSceny : public sf::Sprite
{
private:
    Edge edge;
    float velocity_x_;
    float velocity_y_;
    void bounce(bool flag);
    bool flag;

public:
    bool onGround;
    ElementSceny();
    void reflection(sf::FloatRect borders);
    void animate(const sf::Time &elapsed);
    void setBounds(int l_bound, int r_bound, int t_bound, int b_bound);
    sf::Texture loadTexture(std::string filename_with_path);
};

#endif // ELEMENTSCENY_H
