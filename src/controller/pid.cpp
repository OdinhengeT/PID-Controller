#include <chrono>
#include <thread>
#include <iostream>

#include "pid.hpp"

// Proportional Controller
controller::P::P(controller::Sensor& sensor, Controllable& controllable, float K):
    sensor{sensor}, controllable{controllable}, K{K} {
}

void controller::P::connect_sensor(Sensor& sensor) {
    this->sensor = sensor;
}

void controller::P::connect_controllable(Controllable& controllable) {
    this->controllable = controllable;
}

float controller::P::get_control_signal() {
    return this->K * (this->target - this->last_measure);
}

void controller::P::set_target(float target) {
    this->target = target;
}

void controller::P::set_K(float K) {
    this->K = K;
}
        
void controller::P::start(unsigned int tick_rate) {
    this->active = true;
    while (this->active) {
        auto t = std::chrono::steady_clock::now() + std::chrono::milliseconds(tick_rate);
        
        this->last_measure = this->sensor.measure();

        this->controllable.set_operating_point(this->get_control_signal());

        std::this_thread::sleep_until(t);
    }
}

void controller::P::stop() {
    this->active = false;
}

void controller::P::reset() {
    this->target = 0.0f;
    this->last_measure = 0.0f;
}

// Proportional Integral Controller

controller::PI::PI(Sensor& sensor, Controllable& controllable, float K, float Ti):
    P(sensor, controllable, K), Ti{Ti} {
}

float controller::PI::get_control_signal() {
    return this->K * (this->target - this->last_measure + (this->integral_value / this->Ti));
}

void controller::PI::set_Ti(float Ti) {
    this->Ti = Ti;
}
        
void controller::PI::start(unsigned int tick_rate) {
    float tick_length = tick_rate / 1000.0f;

    this->active = true;
    while (this->active) {
        auto t = std::chrono::steady_clock::now() + std::chrono::milliseconds(tick_rate);

        this->last_measure = this->sensor.measure();
        this->integral_value += (this->target - this->last_measure) * tick_length;

        this->controllable.set_operating_point(this->get_control_signal());
        //std::cout << this->get_control_signal() << std::endl;

        std::this_thread::sleep_until(t);
    }
}

void controller::PI::reset() {
    this->target = 0.0f;
    this->integral_value = 0.0f;
    this->last_measure = 0.0f;
}