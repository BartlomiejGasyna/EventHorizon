#include "object.h"

object::object(double diameter, double distance, double spin_period, double rotation_period) {
    diameter_ = diameter;
    distance_ = distance;
    spin_time_ = spin_period;
    rotation_time_ = rotation_period;
}

void object::animate(double t) {
    if (rotation_time_) {
        rotation_angle_ += 360.0 * t / rotation_time_;
    }
    if (spin_time_) {
        spin_angle_ = spin_angle_ + 360.0 * t / spin_time_;
    }
}

void object::set_color(double r, double g, double b) {
    r_ = r;
    g_ = g;
    b_ = b;
}

void object::draw() {
    glPushMatrix();

    glRotated(rotation_angle_, 0.0, 0.0, 1.0);
    glTranslated(distance_, 0.0, 0.0);
    glRotated(-rotation_angle_ + spin_angle_, 0.0, 0.0, 1.0);

    double half_cube_size = diameter_ / 2.0;

    // bottom
    glColor3d(r_, g_, b_);
    glBegin(GL_POLYGON);
    glVertex3d(-half_cube_size, half_cube_size, -half_cube_size);
    glVertex3d(half_cube_size, half_cube_size, -half_cube_size);
    glVertex3d(half_cube_size, -half_cube_size, -half_cube_size);
    glVertex3d(-half_cube_size, -half_cube_size, -half_cube_size);
    glEnd();

    // top
    glBegin(GL_POLYGON);
    glVertex3d(-half_cube_size, half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, -half_cube_size, half_cube_size);
    glVertex3d(-half_cube_size, -half_cube_size, half_cube_size);
    glEnd();

    // left
    glBegin(GL_POLYGON);
    glVertex3d(-half_cube_size, -half_cube_size, half_cube_size);
    glVertex3d(-half_cube_size, half_cube_size, half_cube_size);
    glVertex3d(-half_cube_size, half_cube_size, -half_cube_size);
    glVertex3d(-half_cube_size, -half_cube_size, -half_cube_size);
    glEnd();

    // right
    glBegin(GL_POLYGON);
    glVertex3d(half_cube_size, -half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, half_cube_size, -half_cube_size);
    glVertex3d(half_cube_size, -half_cube_size, -half_cube_size);
    glEnd();

    // front
    glBegin(GL_POLYGON);
    glVertex3d(-half_cube_size, -half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, -half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, -half_cube_size, -half_cube_size);
    glVertex3d(-half_cube_size, -half_cube_size, -half_cube_size);
    glEnd();

    // back
    glBegin(GL_POLYGON);
    glVertex3d(-half_cube_size, half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, half_cube_size, -half_cube_size);
    glVertex3d(-half_cube_size, half_cube_size, -half_cube_size);
    glEnd();

    glPopMatrix();
}
