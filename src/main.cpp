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

    return 0;
}
