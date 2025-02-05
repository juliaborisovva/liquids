#ifndef LIBLIQUIDS_HPP
#define LIBLIQUIDS_HPP

#include <cstdint>

namespace liquids {

enum class ErrorCode {
    kSuccess = 0,
    kInvalidP = -2,
    kInvalidV = -3,
    kTooMuchV = -4,
    kNotFoundLiquid = -5
};

class Liquid
{
   private:
    // временно значение цвета в виде uint8_t
    uint8_t color_;
    float p_;
    float v_;

   public:
    Liquid(uint8_t color = 255, float p = 550.0, float v = 0.1);
    ~Liquid();

    void SetColor(uint8_t color);
    uint8_t GetColor() const;

    ErrorCode SetDensity(float p);
    float GetDensity() const;

    ErrorCode SetVolume(float v);
    float GetVolume() const;

    // операторы сравнения
    bool operator==(const Liquid& liq) const;
    bool operator!=(const Liquid& liq) const;
};

}  // namespace liquids

#endif  // LIBLIQUIDS_HPP
