//
//  Create by Ale - 1/8/23
//

#include "leg_controller/servo_controller.hpp"
#include "leg_controller/ik.hpp"
#include "leg_controller/servo_drive.hpp"
#include <array>


void servo_controller::move(std::array<float, 3>& position){

    const std::array<float, 3> servo_angles = ik_servo.getAngles(position, link_0_length, link_1_length);
    // drive.Move(servo_angles);

}
