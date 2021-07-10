#include "controller.hpp"

// Controller 
void controller::set_target(float target) {
    this->target = target;
}

// Porportional Controller
controller_p::controller_p(float proportional_constant, float target): 
    proportional_constant{proportional_constant} {
    this->target = target;
}

void controller_p::add_sensor_signal(float sensor_signal) {
    this->last_sensor_signal = sensor_signal;
}

float controller_p::get_control_signal() {
    return proportional_constant * (target - last_sensor_signal);
}

// Proportional Integral Controller
controller_pi::controller_pi(float proportional_constant, float integral_constant, float target):
    proportional_constant{proportional_constant}, integral_constant{integral_constant} {
    this->target = target;
}

float controller_pi::get_control_signal() {
    return proportional_constant * (last_sensor_signals.back()) + integral_value / integral_constant;
}
        
void controller_pi::add_sensor_signal(float sensor_signal) {
    last_sensor_signals.push(target - sensor_signal);
    integral_value += target - sensor_signal;
    if (last_sensor_signals.size() > 100) {
        integral_value -= last_sensor_signals.front();
        last_sensor_signals.pop();
    }
}