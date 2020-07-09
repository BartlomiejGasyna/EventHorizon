//
//  IP_proxy.hpp
//  EventHorizon
//
//  Created by Bartłomiej Gasyna on 09/07/2020.
//  Copyright © 2020 Bartłomiej Gasyna. All rights reserved.
//

#ifndef IP_proxy_hpp
#define IP_proxy_hpp
#include "abstract.h"
#include <stdio.h>
#include <SFML/Network.hpp>


class Proxy 
{
private:
size_t size_;
std::string ip_;
int port_;
SingleFrame last_response;
    
//    struct SingleFrame
//    {
//        float rotation;
//        bool is_laser;
//        int points;
//        std::vector<std::pair<int, int>> asteroids_speed;
//
//    };
public:
    Proxy(){};
    Proxy(size_t size_, std::string ip, int port = 2000){};
    
    //
    SingleFrame Update_Location (const float &rotation, bool is_laser, int points, std::vector<std::pair<int, int>> asteroid_speed)
    {
        SingleFrame temp;
        SingleFrame request, response;
        request.rotation = rotation;
        request.is_laser = is_laser;
        request.points = points;
        //request.asteroids_speed = asteroid_speed;
        
        sf::TcpSocket socket;
        sf::Socket::Status status = socket.connect(ip_, port_);
        if (status == sf::Socket::Done)
        {
            if (socket.send(&request, sizeof(request)) != sf::Socket::Done) {
                std::cout<<"Error while sending current location"<<std::endl;
            }
            else
            {
                std::size_t received;
                if (socket.receive(&response, sizeof(response), received) != sf::Socket::Done) {
                    
                    last_response = response;
                    return last_response;
                }
            }}
        else {std::cout << "Error while receinving current location" << std::endl;}
        return response;
        }
    
};

    

#endif /* IP_proxy_hpp */
