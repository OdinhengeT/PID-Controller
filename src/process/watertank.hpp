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
        float control_signal;
    public:
        watertank(float height, float base_area, float outflow_area);
        ~watertank()=default;
        void set_water_level(float level);
        void set_control_signal(float control_signal);
        float get_level();
        float get_height();
        void active(unsigned int run_time, unsigned int tick_rate);
};

#endif