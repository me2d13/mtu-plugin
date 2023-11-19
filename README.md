# mtu-plugin

This is x-plane plugin to communicate with motorized throttle unit - running dedicated firmware from repository mtu-stm32 at STM32.
When started it runs web server so log message can be checked in web browser and also some control is planned.

# building

This is Visual studio project. So fat it has 3 additional dependencies
* Xplane SDK folder to be copied to root directory (mtu-plugin/SDK)
* [plog](https://github.com/SergiusTheBest/plog) include folder to be copied to include directory (mtu-plugin/include/plog...)
* [json.hpp](https://github.com/nlohmann/json) to be copied directly into include folder (mtu-plugin/include/json.hpp)
