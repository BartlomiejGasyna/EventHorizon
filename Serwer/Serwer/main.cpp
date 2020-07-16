
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


struct SingleFrame
{
    float rotation;
    bool is_laser;
    int points;
    int client_ID;
    // to trzeba bedzie dodac
    //std::vector<std::pair<int, int>>asteroids_speed;
    
};

sf::Packet& operator << (sf::Packet& packet, SingleFrame &frame)
{
    return packet << frame.rotation << frame.is_laser << frame.points <<frame.client_ID;
}
    
sf::Packet& operator >> (sf::Packet& packet, SingleFrame &frame)
{
    return packet >> frame.rotation >> frame.is_laser >> frame.points >>frame.client_ID;
}
    

SingleFrame client1;
int main(int, char const**)
{
    
    
    // Create the main window
    sf::TcpSocket socket;
    socket.connect("127.0.0.1", 2000);
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    
    
    sf::TcpListener listener;
    listener.listen(2000);
    
    if (listener.listen(2000) == sf::Socket::Done) {
        std::cout<<"serwer nawiązał połączenie"<<std::endl;
    }
    

    for(;;)
    {

        
        sf::Packet packet, response;
        SingleFrame client, temp_response, Frame_client1, Frame_client2;

        listener.accept(socket);

        if (socket.receive(packet) == sf::Socket::Status::Done) {
            std::cout<<"udalo sie odebrac strukture"<<std::endl;
            if (packet >> client ) {
                std::cout<<"rotacja: "<<client.rotation<<std::endl;
                std::cout<< "punkty: "<<client.points<<std::endl;
                std::cout<<"czy laser: " <<client.is_laser<<std::endl;
                std::cout<<"ID: " <<client.client_ID <<std::endl;
                std::cout<<std::endl<<std::endl;
                
                temp_response.rotation = client.rotation;
                temp_response.points = client.points;
                temp_response.is_laser = client.is_laser;
                temp_response.client_ID = client.client_ID;
                if (client.client_ID == 1) {
                    Frame_client1 = temp_response;
                    response << Frame_client2;
                    if(socket.send(response) == sf::Socket::Done)
                    {
                        std::cout<<"przesłano dane gracza nr: "<< client.client_ID<<std::endl<<std::endl;
                    }
                }
                else if (client.client_ID == 2)
                {
                    Frame_client2 = temp_response;
                    response << Frame_client1;
                    if(socket.send(response) == sf::Socket::Done)
                    {
                        std::cout<<"przesłano dane gracza nr: "<< client.client_ID<<std::endl<<std::endl;
                    }
                }
                
            }
            
        
        else
            std::cout<<"BŁĄD!"<<std::endl;
            //response = packet;
            
//        if(socket.send(response) == sf::Socket::Done)
//        {
//            std::cout<<"przesłano dane gracza nr: "<< client.client_ID<<std::endl<<std::endl;
//        }
            
//        sf::sleep(sf::milliseconds(10));
    }
    }
   
    

    return EXIT_SUCCESS;
}
