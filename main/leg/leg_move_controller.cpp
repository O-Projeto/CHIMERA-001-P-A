//
//  Create by Ale - 1/8/23
//

#include "leg/leg_move_controller.hpp"
#include "leg/ik.hpp"
#include "leg/servo_drive.hpp"
#include <array>


void leg_move_controller::move(std::array<float, 3>& position){

    const std::array<float, 3> servo_angles = ik_servo.getAngles(position, link_0_length, link_1_length);
    // drive.Move(servo_angles);

}
