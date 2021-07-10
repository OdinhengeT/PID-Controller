#include<math.h>

#include"watertank.hpp"

watertank::watertank(float height, float base_area, float outflow_area):
    current_level{0.0f}, height{height}, base_area{base_area}, outflow_area{outflow_area} {
}

void watertank::set_water_level(float level) {
    if (level > 0 && level < height) current_level = level;
}

void watertank::pump_water(float control_signal) {
    if (control_signal > 0) {
        current_level += tick_length * control_signal * max_inflow / base_area;
        if (current_level > height) current_level = height;
    }
}

void watertank::outflow() {
    current_level -= tick_length * outflow_area * sqrt(19.64f * current_level);
    if (current_level < 0.0f) current_level = 0.0f;
}

float watertank::get_level() {
    return current_level;
}

float watertank::get_height() {
    return height;
}