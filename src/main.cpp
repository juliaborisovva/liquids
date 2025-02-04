#include <iostream>

#include "libliquids.hpp"

int main()
{
    try {
        liquids::Liquid red_liq(233, 550, 0.2);  // Все ок
        liquids::Liquid bl_liq(233, 550, 0.2);
        liquids::Liquid wh_liq(233, 65, 0.2);
        std::cout << "Нет ошибок при создании, все верно." << std::endl;
        if (red_liq == bl_liq) {
            std::cout << "Оператор ==" << std::endl;
        }
        if (red_liq != wh_liq) {
            std::cout << "Оператор !=" << std::endl;
        }

    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
