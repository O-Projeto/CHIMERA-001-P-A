//
//  Create by Ale - 1/8/23
//

#ifndef SERVO_DRIVER_HPP
#define SERVO_DRIVER_HPP

extern "C" {

#include "esp_log.h"
#include "driver/mcpwm_prelude.h"

}

class servo_drive
{
private:
    /* data */
public:

    mcpwm_timer_handle_t timer; // The time base of the final PWM signal. It also determines the event timing of other submodules
    mcpwm_timer_config_t timer_config;
    mcpwm_oper_handle_t oper; // operator: generate PWM waveform
    mcpwm_operator_config_t operator_config;
    mcpwm_cmpr_handle_t comparator; // comparator: compare base time with configured value
    mcpwm_comparator_config_t comparator_config;
    mcpwm_gen_handle_t generator; // can generate a pair of PWM waves complementary or independently 
    mcpwm_generator_config_t generator_config;

    servo_drive(int32_t gpio_servo);
    ~servo_drive();

    void Move(int angle);
};

#endif