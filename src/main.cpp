#include<iostream>

#include"process/watertank.hpp"
#include"controller/controller.hpp"

int main() {

    controller_pi controller(10.0f, 10.0f, 0.6f);
    
    watertank tank(1, 1, 0.1f);
    tank.set_water_level(0.3f);

    std::cout << tank.get_level() << std::endl;  

    for (int i = 0; i < 100; i++){
        tank.outflow();
        controller.add_sensor_signal(tank.get_level() / tank.get_height());
        tank.pump_water(controller.get_control_signal());
        std::cout << tank.get_level() << std::endl;    }
    return 0;
}