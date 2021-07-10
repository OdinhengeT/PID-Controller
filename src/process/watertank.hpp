#ifndef WATERTANK_H
#define WATERTANK_H

struct watertank {
    private:
        float current_level;
        const float tick_length = 0.01f;
        //Dímensions
        const float height;
        const float base_area;
        // Pump and Outflow
        const float outflow_area;
        const float max_inflow = 1.0f;
    public:
        watertank(float height, float base_area, float outflow_area);
        ~watertank()=default;
        void set_water_level(float level);
        void pump_water(float control_signal);
        void outflow();
        float get_level();
        float get_height();
};

#endif