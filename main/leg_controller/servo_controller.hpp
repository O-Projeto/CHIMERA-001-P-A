//
//  Create by Ale - 1/8/23
//

#ifndef SERVO_CONTROLLER_HPP
#define SERVO_CONTROLLER_HPP



#include <iostream>
#include <array>
#include "leg_controller/ik.hpp"
#include "leg_controller/servo_drive.hpp"


class servo_controller
{
private:

    ik ik_servo;
    servo_drive drive;



    
public:

    servo_controller(const int32_t gpio_servo);
    void move(std::array<float, 3>& position);
   
};

#endif