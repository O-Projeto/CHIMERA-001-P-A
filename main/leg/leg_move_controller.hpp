//
//  Create by Ale - 1/8/23
//

#ifndef SERVO_CONTROLLER_HPP
#define SERVO_CONTROLLER_HPP



#include <iostream>
#include <array>
#include "leg/ik.hpp"
#include "leg/servo_drive.hpp"


class leg_move_controller
{
private:

    ik ik_servo;
    servo_drive drive;
    float link_0_length, link_1_length;


    
public:

    leg_move_controller(const int32_t gpio_servo, const float &_link_0_length, const float &_link_1_length) 
    : drive(gpio_servo)
    {

        link_0_length = _link_0_length;
        link_1_length = _link_1_length;
    }
    void move(std::array<float, 3>& position);
   
};

#endif