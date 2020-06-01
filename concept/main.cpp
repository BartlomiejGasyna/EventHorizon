#define GL_SILENCE_DEPRECATION

#include "object.h"

void set_viewport(int width, int height) {
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    gluLookAt(0, -5, 3, 0, 0, 0, 0, 0, 1);
}

int main()
{
    sf::Window window(sf::VideoMode(1024, 768), "Lab10 Uklad Sloneczny", sf::Style::Default, sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);
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

    std::vector<object> objects;


    std::fstream solar_system_file("C:\\Users\\ASUS_PEPE\\Desktop\\STUDIA AiR\\Programowanie strukturalne i obiektowe\\solar_system.txt");
    //std::fstream solar_system_file("solar_system.txt");
    if (!solar_system_file.is_open()) {
        std::cout << "Could not open file" << std::endl;
    }
    std::string line;
    while (std::getline(solar_system_file, line)) {
        if (!line.empty() && line[0] != '#') {
            std::stringstream line_str(line);

            std::string name;
            double distance;
            double diameter;
            double spin_period;
            double orbit_period;
            double gravity;
            int number_of_moons;
            double r;
            double g;
            double b;
            line_str >> name >> distance >> diameter >> spin_period >> orbit_period >> gravity >> number_of_moons >> r >> g >> b;
            std::cout << name << " " << diameter << std::endl;

            objects.push_back(object(diameter, distance, spin_period, orbit_period));
            objects.back().set_color(r/255.0, g/255.0, b/255.0);
        }
    }

    // run the main loop
    bool running = true;
    sf::Clock clk;
    float scale = 1.0;
    float move_x = 1.0;
    float move_y = 1.0;
    while (running) {
        double delta_t = clk.getElapsedTime().asSeconds();
        clk.restart();

        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // end the program
                running = false;
            } else if (event.type == sf::Event::Resized) {
                // adjust the viewport when the window is resized
                set_viewport(event.size.width, event.size.height);
            } else if (event.type == sf::Event::MouseWheelScrolled) {
                std::cout << event.mouseWheelScroll.delta <<std::endl;
                if(event.mouseWheelScroll.delta<0) scale *= 0.9;
                if(event.mouseWheelScroll.delta>0) scale *= 1.1;
            }
            else if (event.type == sf::Event::KeyPressed) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) glTranslated(0, -move_y, 0);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) glTranslated(move_x, 0, 0);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) glTranslated(0, move_y, 0);
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) glTranslated(-move_x, 0, 0);

            }
        }

        // clear the buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE) ;
        glEnable (GL_COLOR_MATERIAL);

        // draw stuff

        glPushMatrix();

        glScaled(1.0/1500, 1.0/1500, 1.0/1500);

        glScaled(scale, scale, scale);

        for (auto &p : objects) {
            p.animate(delta_t);
            p.draw();
        }

        glPopMatrix();

        // end the current frame (internally swaps the front and back buffers)
        window.display();
    }
    return 0;
}
