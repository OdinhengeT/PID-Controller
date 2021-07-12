#ifndef INTERFACE_CONTROLLER_H
#define INTERFACE_CONTROLLER_H

namespace controller {

    struct Sensor {
    public: 
        virtual ~Sensor() = default;
        virtual float measure() = 0;
    };

    struct Controllable {
    public:
        virtual ~Controllable() = default;
        virtual void set_operating_point(float control_signal) = 0;
    };

    struct Controller {
    public:
        virtual ~Controller() = default;

        virtual void connect_sensor(Sensor& sensor) = 0;
        virtual void connect_controllable(Controllable& controllable) = 0;

        virtual float get_control_signal() = 0;

        virtual void set_target(float target) = 0;
        
        virtual void start(unsigned int tick_rate) = 0;
        virtual void stop() = 0;
        virtual void reset() = 0;
    };

}

#endif