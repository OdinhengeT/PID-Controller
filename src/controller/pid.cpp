#include <chrono>
#include <thread>
#include <iostream>

#include "pid.hpp"

using namespace controller;

// Proportional Controller
P::P(Sensor& sensor, Controllable& controllable, float K):
    controller::OnOff(sensor, controllable), K{K} {
}

float P::get_control_signal() {
    return this->K * (this->target - last_measurements[0]);
}

void P::set_K(float K) {
    this->K = K;
}

// Proportional Integral Controller

PI::PI(Sensor& sensor, Controllable& controllable, float K, float Ti):
    P(sensor, controllable, K), Ti{Ti} {
}

float PI::get_control_signal() {
    return this->K * (this->target - this->last_measurements[0] + (this->integral_value / this->Ti));
}

void PI::set_Ti(float Ti) {
    this->Ti = Ti;
}
        
void PI::make_measurement(unsigned int tick_rate) {
    this->last_measurements[0] = this->sensor.measure();
    this->integral_value += (this->target - this->last_measurements[0]) * tick_rate / 1000.0f;
}

void PI::reset() {
    this->target = 0.0f;
    this->last_measurements[0] = 0.0f;
    this->integral_value = 0.0f;
}

// Proportional Integral Derivative Controller

PID::PID(Sensor& sensor, Controllable& controllable, float K, float Ti, float Td):
    PI(sensor, controllable, K, Ti), Td{Td} {
    this->last_measurements = {0.0f, 0.0f};
}

float PID::get_control_signal() {
    return this->K * (this->target - this->last_measurements[0] + (this->integral_value / this->Ti));
}

void PID::set_Td(float Td) {
    this->Td = Td;
}

void PID::make_measurement(unsigned int tick_rate) {
    this->last_measurements.insert(this->last_measurements.begin(), this->sensor.measure());
    if (this->last_measurements.size() > 2) this->last_measurements.pop_back();

    this->integral_value += (this->target - this->last_measurements[0]) * tick_rate / 1000.0f;

    float N = 10.0f;
    this->derivate_value = (Td / (Td + N * tick_rate)) * this->derivate_value;
    this->derivate_value -= (K * Td * N / (Td + N * tick_rate)) * (this->last_measurements[0] - this->last_measurements[1]);
}

void PID::reset() {
    this->target = 0.0f;
    this->last_measurements = {0.0f, 0.0f};
    this->integral_value = 0.0f;
    this->derivate_value = 0.0f;
}