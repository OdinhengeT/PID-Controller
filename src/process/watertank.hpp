#ifndef WATERTANK_H
#define WATERTANK_H

#include "../controller/interface_controller.hpp"

struct Pump : public controller::Controllable {
    private: 
        const float max_inflow;
        float operating_point;
    public:
        Pump(float max_inflow);
        ~Pump() = default;
        void set_operating_point(float control_signal);
        float get_pumped_volume(float dt);
};

struct Watertank {
    private:
        bool active{false};
        float water_level;
        //Dímensions
        const float height;
        const float base_area;
        // Outflow
        const float outflow_area;

        Pump& pump;
    public:
        Watertank(float height, float base_area, float outflow_area, Pump& pump);
        ~Watertank()=default;

        float get_water_level();
        float get_height();

        void set_water_level(float level);

        void start(unsigned int tick_rate_ms);
        void stop();
};

struct Sensor_Watertank : public controller::Sensor {
    private:
        Watertank& tank;
    public:
        Sensor_Watertank(Watertank& tank);
        ~Sensor_Watertank() = default;
        float measure();
};

#endif