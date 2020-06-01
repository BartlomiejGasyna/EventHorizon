#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#include <GL/glu.h>

class object {

public:
    object(double diameter = 1.0, double distance = 1.0, double spin_time = 1.0, double rotation_time = 1.0);
    void animate(double t);
    void set_color(double r, double g, double b);
    void draw();

private:
    double diameter_;
    double distance_;
    double spin_time_;
    double rotation_time_;
    double r_ = 1.0;
    double g_ = 1.0;
    double b_ = 1.0;

    double rotation_angle_ = 0.0;
    double spin_angle_ = 0.0;
};

#endif // OBJECT_H
