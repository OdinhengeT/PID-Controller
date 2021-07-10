#include <math.h>
#include <chrono>
#include <thread>

#include <iostream>

#include "watertank.hpp"

watertank::watertank(float height, float base_area, float outflow_area):
    current_level{0.0f}, 
    height{height}, 
    base_area{base_area}, 
    outflow_area{outflow_area}, 
    control_signal{0.0f} {
}

void watertank::set_water_level(float level) {
    if (level > 0 && level < height) current_level = level;
}

void watertank::set_control_signal(float control_signal) {
    this->control_signal = control_signal;
}

float watertank::get_level() {
    return current_level;
}

float watertank::get_height() {
    return height;
}

void watertank::active(unsigned int run_time, unsigned int tick_rate) {
    float tick_length = tick_rate / 1000.0f;

    auto time_stop = std::chrono::steady_clock::now() + std::chrono::milliseconds(run_time);
    while (std::chrono::steady_clock::now() < time_stop) {

        auto t = std::chrono::steady_clock::now() + std::chrono::milliseconds(tick_rate);

        // Water outflow in accordance to Torricelli's Law
        current_level -= tick_length * outflow_area * sqrt(19.64f * current_level);
        if (current_level < 0.0f) current_level = 0.0f;

        // Pumping in new water based on current control_signal
        if (control_signal > 1.0f) {
            current_level += tick_length * 1.0f * max_inflow / base_area;
        } else if (control_signal > 0) {
            current_level += tick_length * control_signal * max_inflow / base_area;
        }

        if (current_level > height) current_level = height; // Overflowing!!

        std::this_thread::sleep_until(t);

    }
}