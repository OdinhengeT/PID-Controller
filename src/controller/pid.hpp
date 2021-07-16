#ifndef CONTROLLER_PID_H
#define CONTROLLER_PID_H

#include "interface_controller.hpp"

namespace controller {
    
    class P: public OnOff {
    protected:
        float K;
    public: 
        P(Sensor& sensor, Controllable& controllable, float K);
        ~P() = default;

        virtual float get_control_signal() override;

        void set_K(float K);
    };

    class PI: public P {
    protected:
        float Ti;
        float integral_value{0.0f};
    public: 
        PI(Sensor& sensor, Controllable& controllable, float K, float Ti);
        ~PI() = default;

        float get_control_signal() override;

        void set_Ti(float Ti);
        
        void make_measurement(unsigned int tick_rate) override;

        virtual void reset() override;
    };

    class PID: public PI {
    protected:
        float Td;
        float derivate_value{0.0f};
    public:
        PID(Sensor& sensor, Controllable& controllable, float K, float Ti, float Td);
        ~PID() = default;

        float get_control_signal() override;

        void set_Td(float Td);

        void make_measurement(unsigned int tick_rate) override;

        void reset() override;
    };

}

#endif