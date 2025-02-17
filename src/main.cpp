#include <iostream>

#include "libliquids.hpp"

int main()
{
    try {
        liquids::Bottle b1;
        liquids::Bottle b2;

        std::cout << "Нет ошибок при создании, все верно." << std::endl;
        std::cout << "Bottle\n";
        if (b1 == b2) {
            std::cout << "Оператор ==" << std::endl;
        }
        if (!(b2 != b1)) {
            std::cout << "Оператор !=" << std::endl;
        }

        b1.AddLiquid(255.0f, 550.0f, 0.2f);
        b1.AddLiquid(230.0f, 550.0f, 0.3f);
        std::cout << b1.GetBottleV() << " " << b1.GetMass() << std::endl;
        std::cout << b1.GetMaxBottleV() << "max bottle v\n";
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    } catch (...) {
        std::cout << "Неизвестная ошибка" << std::endl;
        throw;
    }

    return 0;
}
