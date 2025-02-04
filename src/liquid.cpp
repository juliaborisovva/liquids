#include <stdexcept>

#include "libliquids.hpp"

/* Жидкость: цвет жидкости (ргб), пока число - чб, потом можно изменить на ргб;
 * плотность жидкости (кило-грамм на кубический метр кг/м³, > 0);
 * объем жидкости (в л > 0); геттер-сеттер информация о цвете жидкости;
 * геттер-сеттер информация о плотности; геттер-сеттер информация об объеме. */

namespace liquids {

Liquid::Liquid(uint8_t color, float p, float v) : color_(color)
{
    if (p <= 0) {
        throw std::invalid_argument("Ошибка: значение плотности P должно быть > 0.");
    }
    if (v <= 0) {
        throw std::invalid_argument("Ошибка: значение объема V должно быть > 0.");
    }

    this->color_ = color;
    this->p_ = p;
    this->v_ = v;
}

Liquid::~Liquid()
{
    // очищение
}

void Liquid::SetColor(uint8_t color) { color_ = color; }

uint8_t Liquid::GetColor() { return this->color_; }

ErrorCode Liquid::SetDensity(float p)
{
    ErrorCode err = ErrorCode::kInvalidP;
    if (p > 0) {
        err = ErrorCode::kSuccess;
        this->p_ = p;
    }
    return err;
}

float Liquid::GetDensity() { return this->p_; }

ErrorCode Liquid::SetVolume(float v)
{
    ErrorCode err = ErrorCode::kInvalidV;
    if (v > 0) {
        err = ErrorCode::kSuccess;
        this->v_ = v;
    }
    return err;
}

float Liquid::GetVolume() { return this->v_; }

bool Liquid::operator== (const Liquid& liq) const
{
    return this->color_ == liq.color_ && this->p_ == liq.p_ && this->v_ == liq.v_;
}
bool Liquid::operator!= (const Liquid& liq) const
{
    return !(*this == liq);
}

}  // namespace liquids
