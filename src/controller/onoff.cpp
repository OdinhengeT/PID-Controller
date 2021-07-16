#include <thread>
#include <chrono>

#include "interface_controller.hpp"

using namespace controller;

OnOff::OnOff(Sensor& sensor, Controllable& controllable):
    sensor{sensor}, controllable{controllable}, last_measurements{0.0f} {
}

void OnOff::connect_sensor(Sensor& sensor) {
    this->sensor = sensor;
}

void OnOff::connect_controllable(Controllable& controllable) {
    this->controllable = controllable;
}

float OnOff::get_control_signal() {
    if (this->target > this->last_measurements[0]) return 1.0f;
    else return 0.0f;
}

void OnOff::set_target(float target) {
    this->target = target;
}

void OnOff::make_measurement(unsigned int tick_rate) {
    this->last_measurements[0] = this->sensor.measure();
}

void OnOff::start(unsigned int tick_rate) {
    this->active = true;
    this->internal_thread = std::thread([this, tick_rate]() {
        while (this->active) {
            auto t = std::chrono::steady_clock::now() + std::chrono::milliseconds(tick_rate);

            this->make_measurement(tick_rate);
            this->controllable.set_operating_point(this->get_control_signal());

            std::this_thread::sleep_until(t);
        }
    });
}

void OnOff::stop() {
    this->active = false;
    if (internal_thread.joinable()) {
        this->internal_thread.join();
    }
}

void OnOff::reset() {
    this->target = 0.0f;
    this->last_measurements[0] = 0.0f;
}