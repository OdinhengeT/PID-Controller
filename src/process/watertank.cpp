#include <math.h>
#include <chrono>
#include <thread>
#include <iostream>

#include "watertank.hpp"

// Pump

Pump::Pump(float max_inflow):
    max_inflow{max_inflow}, operating_point{0.0f} {
}

void Pump::set_operating_point(float control_signal) {
    if (control_signal > 1.0f) {
        this->operating_point = 1.0f;
    } else if (control_signal > 0.0f) {
         this->operating_point = control_signal;
    } else {
        this->operating_point = 0.0f;
    }
}

float Pump::get_pumped_volume(float dt) {
    return dt * this->max_inflow * this->operating_point;
}

// Watertank

Watertank::Watertank(float height, float base_area, float outflow_area, Pump& pump):
    water_level{0.0f}, 
    height{height}, 
    base_area{base_area}, 
    outflow_area{outflow_area}, 
    pump{pump} {
}

void Watertank::set_water_level(float level) {
    if (level > 0 && level < height) water_level = level;
}

float Watertank::get_water_level() {
    return water_level;
}

float Watertank::get_height() {
    return height;
}

void Watertank::start(unsigned int tick_rate) {
    this->active = true;
    while (this->active) {
        auto t = std::chrono::steady_clock::now() + std::chrono::milliseconds(tick_rate);

        // Water outflow in accordance to Torricelli's Law
        water_level -= tick_rate / 1000.0f * outflow_area * sqrt(19.64f * water_level);
        if (water_level < 0.0f) water_level = 0.0f;

        // Pumping in new water
        water_level += this->pump.get_pumped_volume(tick_rate / 1000.0f) / base_area;
        if (water_level > height) water_level = height; // Overflowing!!

        std::this_thread::sleep_until(t);
    }
}

void Watertank::stop() {
    this->active = false;
}

// Sensor_Watertank

Sensor_Watertank::Sensor_Watertank(Watertank& tank):
    tank{tank} {
}

float Sensor_Watertank::measure() {
    std::cout << tank.get_water_level() / tank.get_height() << std::endl; 
    return tank.get_water_level() / tank.get_height();
}