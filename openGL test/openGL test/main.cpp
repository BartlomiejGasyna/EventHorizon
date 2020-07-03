//
//  main.cpp
//  openGL test
//
//  Created by Bartłomiej Gasyna on 01/06/2020.
//  Copyright © 2020 Bartłomiej Gasyna. All rights reserved.
//

#include "main.hpp"
//
//  main.cpp
//  sfml_opengl
//
//  Created by Jakub Tomczyński on 27/02/2019.
//  Copyright © 2019 Jakub Tomczyński. All rights reserved.
//

#define GL_SILENCE_DEPRECATION

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

#ifdef __APPLE__
#include <OpenGL/glu.h> // macOS
#else
//#include <GL/glu.h> // Windows/Linux
#endif

void draw_cube(double size) {
    double half_cube_size = size / 2.0;
    
    // bottom
    glBegin(GL_POLYGON);
    glVertex3d(-half_cube_size, half_cube_size, -half_cube_size);
    glVertex3d(half_cube_size, half_cube_size, -half_cube_size);
    glVertex3d(half_cube_size, -half_cube_size, -half_cube_size);
    glVertex3d(-half_cube_size, -half_cube_size, -half_cube_size);
    glEnd();
    
    // top
    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3d(-half_cube_size, half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, -half_cube_size, half_cube_size);
    glVertex3d(-half_cube_size, -half_cube_size, half_cube_size);
    glEnd();
    
    // left
    glColor3d(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3d(-half_cube_size, -half_cube_size, half_cube_size);
    glVertex3d(-half_cube_size, half_cube_size, half_cube_size);
    glVertex3d(-half_cube_size, half_cube_size, -half_cube_size);
    glVertex3d(-half_cube_size, -half_cube_size, -half_cube_size);
    glEnd();
    
    // right
    glColor3d(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3d(half_cube_size, -half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, half_cube_size, -half_cube_size);
    glVertex3d(half_cube_size, -half_cube_size, -half_cube_size);
    glEnd();
    
    // front
    glColor3d(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3d(-half_cube_size, -half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, -half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, -half_cube_size, -half_cube_size);
    glVertex3d(-half_cube_size, -half_cube_size, -half_cube_size);
    glEnd();
    
    // back
    glColor3d(0.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3d(-half_cube_size, half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, half_cube_size, half_cube_size);
    glVertex3d(half_cube_size, half_cube_size, -half_cube_size);
    glVertex3d(-half_cube_size, half_cube_size, -half_cube_size);
    glEnd();
}

void set_viewport(int width, int height) {
    const float ar = (float)width / (float)height;
    
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    gluLookAt(0, -5, 3, 0, 0, 0, 0, 0, 1);
    
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
}

int main() {
    // create the window
    sf::Window window(sf::VideoMode(1024, 768), "SFML OpenGL Template", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);
    
    // activate the window
    window.setActive(true);
    
    // set viewport according to current window size
    set_viewport(window.getSize().x, window.getSize().y);
    
    glClearColor(0, 0, 0, 1);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SMOOTH);
    glShadeModel(GL_SMOOTH);
    
    // setup lights
    
    GLfloat light_position[] = { 2.0, 0.0, 2.0, 1.0 };
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };
    
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    
    GLfloat global_ambient[] = {0.3, 0.3, 0.3, 0.1};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    
    glEnable(GL_NORMALIZE) ;
    
    // load resources, initialize the OpenGL states, ...
    
    // run the main loop
    bool running = true;
    
    sf::Clock clk;
    
    while (running) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // end the program
                running = false;
            } else if (event.type == sf::Event::Resized) {
                // adjust the viewport when the window is resized
                set_viewport(event.size.width, event.size.height);
            }
        }
        
        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ;
        glEnable (GL_COLOR_MATERIAL);
        
        // draw stuff
        
        glPushMatrix();
        
        float rot = clk.getElapsedTime().asSeconds() * 90;
        
        // TODO
        // test functions below (glTranslated, glRotated, glColor3d)
        // what happens when you change their arguments?
        // does their order change the result?
        
        glTranslated(0.0, 0.0, 0.0);
        glRotated(0, 1.0, 0.0, 0.0);
        glRotated(0, 0.0, 1.0, 0.0);
        glRotated(rot, 0.0, 0.0, 1.0);
        
        glScaled(1.0, 2.0, 0.5);
        
        draw_cube(2.0);
        
        glPopMatrix();
        
        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }
    
    return 0;
}
