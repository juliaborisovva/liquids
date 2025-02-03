#include <iostream>

#include "libliquids.hpp"

int main()
{
    try {
        liquids::Liquid red_liq(233, 550, 0.2);  // Все ок
        std::cout << "Нет ошибок, все верно." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        liquids::Liquid red_liq(233, 0, 0.2);  // err density <= 0
        std::cout << "Нет ошибок, все верно." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        liquids::Liquid red_liq(233, 550, -9);  // err volume <= 0
        std::cout << "Нет ошибок, все верно." << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
