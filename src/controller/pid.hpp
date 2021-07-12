#ifndef CONTROLLER_PID_H
#define CONTROLLER_PID_H

#include "interface_controller.hpp"

namespace controller {
    
    class P: public Controller {
    protected:
        bool active{false};
        Sensor& sensor;
        Controllable& controllable;
        float target{0.0f};
        float last_measure{0.0f};
        float K;
    public: 
        P(Sensor& sensor, Controllable& controllable, float K);
        ~P() = default;

        void connect_sensor(Sensor& sensor) override;
        void connect_controllable(Controllable& controllable) override;

        float get_control_signal() override;

        void set_target(float target) override;
        void set_K(float K);
        
        void start(unsigned int tick_rate) override;
        void stop() override;
        void reset() override;
    };

    class PI: public P {
    private:
        float Ti;
        float integral_value;
    public: 
        PI(Sensor& sensor, Controllable& controllable, float K, float Ti);
        ~PI() = default;

        float get_control_signal() override;

        void set_Ti(float Ti);
        
        void start(unsigned int tick_rate) override;
        void reset() override;
    };

}

#endif