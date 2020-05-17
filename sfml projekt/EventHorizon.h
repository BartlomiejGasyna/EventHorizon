//
//  EventHorizon.h
//  sfml projekt
//
//  Created by Bartłomiej Gasyna on 17/05/2020.
//  Copyright © 2020 Bartłomiej Gasyna. All rights reserved.
//

#ifndef EventHorizon_h
#define EventHorizon_h

#include <stdio.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>

struct Bounds
{
    int bottom = 0;
    int right = 0;
};

class Spaceship
{
private:
    float velocity_x;
    float velocity_y;
    float angular_velocity;
    int health;
    const sf::Vector2f Origin; //zmieniamy punkt origin na środek sceny, wtedy metoda .rotate(); będzie imitować ruch po okręgu;
    void spaceship_collision(); //sprawdza, czy nie nastąpiło zderzenie z asteroidą, lub laserem przeciwnkia
    
    
    sf::Texture SpaceshipTexture;
public:
    
    Spaceship();
    ~Spaceship();
    void turn(); // umożliwia ruch statku wokół centrum sceny
    void flight(); //umożliwia ruch statku w kierunku od i do centrum (zmiana odległości do centrum)
    
};

class Laser
{
private:
    int position_x_;
    int position_y_;
    float velocity_x_;
    float velocity_y_;
    
public:
    Laser(sf::Vector2f size, int position_x_, int position_y_);
    void collision();//sprawdza czy obiekt został trafiony
};

class Asteroids
{
private:
    float velocity_x;
    float velocity_y;
    float angular_velocity;
    sf::Vector2f asteroid_position; //TO ZAWSZE BEDZIE CENTRUM PLANSZY
    void set_bounds(int bottom, int right);//ustawia wielkosc planszy aby ustawic pozycje asteroid
public:
    Asteroids();
    virtual ~Asteroids() = 0;
    bool is_destroyed(); // stan asteroidy (zniszczona/ nie zniszczona)
};

class Small_Asteroid :public Asteroids
{
private:
    sf::Texture SpaceshipTexture;
public:
    Small_Asteroid();
};

class Medium_Asteroid :public Asteroids
{
private:
    sf::Texture SpaceshipTexture;
public:
    Medium_Asteroid();
};

class Huge_Asteroid :public Asteroids
{
private:
    sf::Texture SpaceshipTexture;
public:
    Huge_Asteroid();
};

class Bonuses
{
private:
    float position_x_;
    float position_y_;
public:
    void Heal();
    void Reduce_speed();
    void Increase_Speed();
};

/*     w naszej grze występuje kilka różnych teł o odmiennym wyglądzie, z różnymi przezroczystościami.
 Poprzez nałożenie kilku warstw na siebie oraz odpowiednie ich rozmieszczenie i obrót na planszy gry
 chcemy uzyskać efekt mieniącego się nieba, poruszających się w różnych kierunkach gwiazd i planet
 */
class Background
{
public:
    Background(); // domyślnie wyświetli czarne tło
    Background(sf::Texture texture, sf::Vector2f background_position, float bg_angular_speed);
};
class Game_Representation
{
public:
    double Player1_points;
    double Player2_points;
    sf::Vector2f Player1_position;
    sf::Vector2f Player2_position;
    
    sf::Time Elapsed;
};

//Nie wiemy jak powinny wyglądać klasy do gry sieciowej


#endif /* EventHorizon_h */
