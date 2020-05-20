


#include "EventHorizon.h"

sf::Time elapsed;
float velocity_x0 = 0;
float velocity_x1 = 70;
float velocity_x2 = 90;

float velocity_y1 = 70;
float velocity_y2 = 90;
float velocity_y0 = 0;
sf::RenderWindow window(sf::VideoMode(1000, 1000), "My window");

//void flight (sf::CircleShape obs)
//{
//    obs.move(velocity_x0*elapsed.asSeconds(), velocity_y2*elapsed.asSeconds());
//    window.draw(obs);
//}
//
//class AnimatedSprite : public sf::Sprite {
//public:
//    AnimatedSprite() : sf::Sprite()
//    {
//    }
//    void add_animation_frame(const sf::IntRect &frame);
//    void step(const sf::Time &elapsed);
//
//private:
//    std::vector<sf::IntRect> frames_;
//    std::vector<sf::IntRect>::iterator current_frame_ = frames_.begin();
////    size_t current_frame_ = 0;
//    float elapsed_accumulator_ = 0;
//    float fps = 10;
//};
//
//void AnimatedSprite::add_animation_frame(const sf::IntRect &frame) {
//    frames_.emplace_back(frame);
//    current_frame_ = frames_.begin();
//}
//
//void AnimatedSprite::step(const sf::Time &elapsed) {
//    elapsed_accumulator_ += elapsed.asSeconds();
//    while (elapsed_accumulator_ >= 1.0/fps) {
//        elapsed_accumulator_ -= 1.0/fps;
//        if (!frames_.empty()) {
////                setTextureRect(frames_[current_frame_]);
////                current_frame_ = (current_frame_ + 1) % frames_.size();
//            setTextureRect(*current_frame_);
//            current_frame_++;
//            if(current_frame_ == frames_.end())
//            {
//                current_frame_ = frames_.begin();
//            }
//        }
//    }
//}



int main() {
    // create the window

    
    // create some shape

    sf::RectangleShape rectangle(sf::Vector2f(10, 10));
    rectangle.setPosition(395.0, 0);
    rectangle.setFillColor(sf::Color(100, 50, 250));
    float rectangle_velocity_y = 150;
    
    sf::Texture texture_spaceship;
    if(!texture_spaceship.loadFromFile("Spaceship2.png")) { std::cout<<"error"; }
    
    
    sf::RectangleShape spaceship(sf::Vector2f(20,20));
    spaceship.setPosition((window.getSize().x-spaceship.getSize().x)/2,500);
    spaceship.setFillColor(sf::Color::White);
    spaceship.setOrigin(10, -350);
    float spaceship_angular_velocity = 50;

    sf::Sprite spaceship_sprite;
    //AnimatedSprite spaceship_sprite;

    spaceship_sprite.setTexture(texture_spaceship);
    spaceship_sprite.setTextureRect(sf::IntRect(0,0,70,72));
    
    spaceship_sprite.setPosition((window.getSize().x-spaceship.getSize().x)/2,500);
    spaceship_sprite.setOrigin(10, -350);
    spaceship_sprite.setScale(1.2,1.2);
    
    //ANIMACJA RUCHU
    //    spaceship_sprite.add_animation_frame(sf::IntRect(0, 0, 70, 72));
    //    spaceship_sprite.add_animation_frame(sf::IntRect(70, 0, 70, 72));
    
    
    sf::Texture texture_background;
    if(!texture_background.loadFromFile("background base.png")) { std::cout<<"error";
    }
    texture_background.setRepeated(true);
    
    sf::Sprite background1;
    background1.setTexture(texture_background);
    background1.setTextureRect(sf::IntRect(0,0, window.getSize().x, window.getSize().y));
    background1.setScale(window.getSize().x/texture_background.getSize().x, window.getSize().y/texture_background.getSize().y);
    background1.setOrigin(500,500);
    background1.setOrigin(background1.getLocalBounds().width/2,background1.getLocalBounds().height/2);
    background1.setPosition(window.getSize().x/2, window.getSize().y/2);



    sf::Texture texture_background2;
    if(!texture_background2.loadFromFile("background base2.png")) { std::cout<<"error";
    }
    texture_background2.setRepeated(true);

    sf::Sprite background2;
    background2.setTexture(texture_background2);
    background2.setTextureRect(sf::IntRect(0,0, window.getSize().x, window.getSize().y));
    background2.setScale(window.getSize().x/texture_background2.getSize().x, window.getSize().y/texture_background2.getSize().y);
    background2.setOrigin(background2.getLocalBounds().width/2,background2.getLocalBounds().height/2);
    background2.setPosition(window.getSize().x/2, window.getSize().y/2);


    //background2.setOrigin(500,500);
    
    

    
    

    sf::CircleShape obstacle;
    obstacle.setRadius(30);
    obstacle.setPosition((window.getSize().x-obstacle.getRadius())/2, (window.getSize().y-obstacle.getRadius())/2);
    obstacle.setFillColor(sf::Color::Red);
    
    
    sf::SoundBuffer buffer;
    if(!buffer.loadFromFile("brokenglass.wav"))
        std::cout << "ERROR" << std::endl;
    sf::Sound sound;
    sound.setBuffer(buffer);
    
    sf::Clock clock;
    
    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        window.setFramerateLimit(60);
        //EVENTS
        sf::Event event;
        static float full_time = 0;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //LOGIC
        elapsed = clock.restart();
        full_time+=elapsed.asSeconds();
        //std::cout << "Elapsed time: " << elapsed.asMicroseconds()<< std::endl;
        background1.rotate(-0.1);
        background2.rotate(0.1);
        
        
        sf::FloatRect rectangle_bounds = rectangle.getGlobalBounds();
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            spaceship_sprite.rotate(5);
            spaceship.rotate(5);

        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            spaceship_sprite.rotate(-5);
            spaceship.rotate(-5);

        }
        
        float radians = 3.1415926536 / 180 *spaceship_sprite.getRotation();
        
        std::cout<<"radians: " << radians << std::endl;
        std::cout<<"rotation: " << spaceship_sprite.getRotation()<<std::endl;
        //         std::cout<<"sin: " << sin(radians)<<std::endl;
        //        std::cout<<"cos: " << cos(radians)<<std::endl;
        //
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            //convert the angle of the object to radians
            
            //x and y
            float x = 1*sin(radians);
            float y = -1*cos(radians);
            
            //rotate accordingly
            spaceship_sprite.move(x, y);
            //            if (90<=spaceship_sprite.getRotation() || spaceship_sprite.getRotation()<=270) {
            //                spaceship_sprite.setOrigin(spaceship_sprite.getOrigin().x-x, spaceship_sprite.getOrigin().y+y);
            //            }
            //            else
            //            {
            spaceship_sprite.setOrigin(spaceship_sprite.getOrigin().x+x, spaceship_sprite.getOrigin().y-y);
            //            }
            
            
        }
        std::cout<<"origin x:" << spaceship_sprite.getOrigin().x<<std::endl;
        std::cout<<"origin y:" << spaceship_sprite.getOrigin().y<<std::endl;
        //std::cout << rectangle_bounds.top << " " << rectangle_bounds.left << " " ;
        //std::cout << rectangle_bounds.width << " " << rectangle_bounds.height << std::endl;
        
        rectangle.move(0,rectangle_velocity_y*elapsed.asSeconds() );
        if (rectangle.getPosition().y <=400) {
            rectangle.setSize(sf::Vector2f(rectangle.getSize().x+1.5, rectangle.getSize().y+1.5));
        }
        
        rectangle.setPosition((window.getSize().x/2)-rectangle.getSize().x/2, rectangle.getPosition().y+0.000001);
        
        if (rectangle.getPosition().y >400) {
            rectangle.setSize(sf::Vector2f(rectangle.getSize().x-2, rectangle.getSize().y-2));
        }
        //flight(obstacle);
        
        
        obstacle.move(velocity_x0*elapsed.asSeconds(), velocity_y2*elapsed.asSeconds());
        
        if (spaceship.getGlobalBounds().intersects(obstacle.getGlobalBounds()))
        {
            std::cout<<"Kolizja"<<std::endl;
            sound.play();
        }
        
        
        std::vector<sf::CircleShape> asteroids;
        for(int i=0; i<5; i++)
        {

            asteroids.push_back(sf::CircleShape(10));
            asteroids.back().setFillColor(sf::Color::White);
            asteroids.back().setPosition((window.getSize().x-obstacle.getRadius())/2,(window.getSize().y-obstacle.getRadius())/2);
            window.draw(asteroids.back());
        }
        
        //DRAW
        // clear the window with black color
        window.clear(sf::Color::Black);
        
        

        window.draw(rectangle);

        
        //window.draw(spaceship);
        
        window.draw(obstacle);
        window.draw(background1);
        window.draw(background2);
        window.draw(spaceship_sprite);
        
        
        window.display();
    }
    
    return 0;
}





