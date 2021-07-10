#include <iostream>
#include <thread>
#include <chrono>

#include "process/watertank.hpp"
#include "controller/controller.hpp"

int main() {

    controller_pi controller(10.0f, 5.0f, 0.6f);
    
    watertank tank(1, 1, 0.05f);
    tank.set_water_level(0.2f);
    std::cout << tank.get_level() << std::endl;  

    std::thread t1(&watertank::active, &tank, 10000, 10);

    auto time_stop = std::chrono::steady_clock::now() + std::chrono::milliseconds(10000);
    while (std::chrono::steady_clock::now() < time_stop) {
        controller.add_sensor_signal(tank.get_level() / tank.get_height());
        tank.set_control_signal(controller.get_control_signal());
        std::cout << tank.get_level() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(19));
    }

    t1.join();
    return 0;
}