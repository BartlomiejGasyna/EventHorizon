#ifndef ABSTRACT_H
#define ABSTRACT_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <math.h>

struct SingleFrame
{
    float rotation;
    bool is_laser;
    int points;
    int client_ID;
    int HP;
    
};


/*!
 * \brief The Abstract class
 */
class Abstract : public sf::Sprite
{
private:

public:
    int HP_;
    sf::Sprite Sprite;
    int velocity_x_;
    int velocity_y_;
    int asteroid_ID_;
    int object_ID_;
    Abstract();
    virtual ~Abstract();
    /*!
     * \brief setTexture applies a texture to an object
     * \param texture representation of applied texture
     */
    virtual void setTexture(sf::Texture& texture);

    /*!
     * \brief setPosition sets the position of the object
     * \param x position on X-axis
     * \param y position on Y-axis
     */
    virtual void setPosition(const float x, const float y);

    /*!
     * \brief render create a object
     * \param target representing game window
     */
    virtual void render(sf::RenderTarget& target) = 0;

    /*!
     * \brief animuj animation of a object
     * \param elapsed time unit
     */
    virtual void animuj(const sf::Time &elapsed) = 0;

    /*!
     * \brief out_of_screen detects when a object exiting the screen
     * \param size size of the game window
     */
    virtual void out_of_screen(sf::Vector2u size);

    /*!
     * \brief collision detects collision between objects
     * \param object
     * \return true when there is a collision otherwise false
     */
    virtual bool collision(sf::FloatRect object);

    /*!
     * \brief to_center moves objects to center of the game window
     * \param size dimensions of the game window
     */
    virtual void to_center(sf::Vector2u size);

    /*!
     * \brief getVelocities gets velocities on X-axis and Y-axis
     * \return std::pair consisted of velocities on X-axis and Y-axis
     */
    virtual std::pair<int, int>getVelocities();

    /*!
     * \brief set_asteroid_ID assigns asteroid unique ID number
     * \param asteroid_ID ID number
     */
    virtual void set_asteroid_ID(int asteroid_ID);

    /*!
     * \brief get_asteroid_ID gets asteroid ID number
     * \return ID number
     */
    virtual int get_asteroid_ID();

    /*!
     * \brief get_object_ID gets object ID number
     * \return  ID number
     */
    virtual int get_object_ID();

    /*!
     * \brief reduce_HP decreases object HP
     * \param damage damage dealt
     */
    virtual void reduce_HP(int damage);
};



#endif // ABSTRACT_H
