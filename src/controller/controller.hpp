#include <queue>

#ifndef CONTROLLER_H
#define CONTROLLER_H

class controller {
    protected:
        float target;
    public:
        virtual ~controller() = default;
        void set_target(float target);
        virtual float get_control_signal();
        virtual void add_sensor_signal(float sensor_signal);
};

class controller_p: public virtual controller {
    private:
        float proportional_constant;
        float last_sensor_signal;
    public: 
        controller_p(float proportional_constant, float target);
        ~controller_p() = default;
        float get_control_signal();
        void add_sensor_signal(float sensor_signal);
};

class controller_pi: public virtual controller {
    private:
        float proportional_constant;
        float integral_constant;
        float integral_value;
        std::queue<float> last_sensor_signals;
    public: 
        controller_pi(float proportional_constant, float integral_constant, float target);
        ~controller_pi() = default;
        float get_control_signal();
        void add_sensor_signal(float sensor_signal);
};

#endif