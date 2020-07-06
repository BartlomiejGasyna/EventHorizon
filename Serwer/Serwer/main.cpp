
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <string>
#include <iostream>


int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
    sf::TcpSocket socket;
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    
    sf::TcpListener listener;
    listener.listen(2000);
    
    if (listener.listen(2000) == sf::Socket::Done) {
        std::cout<<"serwer nawiązał połączenie"<<std::endl;
    }
    listener.accept(socket);
    std::string text = "jestem na serwerze";
    socket.send(&text, text.size());
    //socket.receive(<#void *data#>, <#std::size_t size#>, <#std::size_t &received#>)
    socket.disconnect();
    int port = 15292;
    
    

   
    
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear();

       
        window.display();
    }

    return EXIT_SUCCESS;
}
