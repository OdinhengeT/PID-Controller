#include <iostream>
#include <thread>
#include <chrono>

#include "process/watertank.hpp"
#include "controller/pid.hpp"

int main() {
    Pump pump(1.0f);
    Watertank tank(1.0f, 1.0f, 0.01f, pump);
    Sensor_Watertank sensor(tank);
    tank.set_water_level(0.2f);

    controller::PID controller(sensor, pump, 10.0f, 10.0f, 10.0f);
    controller.set_target(0.6f);

    std::cout << tank.get_water_level() << std::endl;  

    tank.start(10);
    controller.start(15);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    
    controller.stop();
    tank.stop();
    return 0;
}