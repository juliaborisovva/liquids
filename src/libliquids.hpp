#ifndef LIBLIQUIDS_HPP
#define LIBLIQUIDS_HPP

namespace liquids {

enum class ErrorCode {
    kSuccess = 0,
//    kInvalidValue = -1,
    kInvalidP = -2,
    kInvalidV = -3,
//    kTooMuchV = -4,
//    kVLEZero = -5,
//    kNotFoundLiquid = -6
};

class Liquid
{
   private:
    // временно значение цвета в виде uint8_t
    uint8_t color_;
    float p_;
    float v_;

   public:
    Liquid(uint8_t color = 255, float p = 100.0, float v = 0.1);
    ~Liquid();

    void SetColor(uint8_t color);
    uint8_t GetColor();

    ErrorCode SetDensity(float p);
    float GetDensity();

    ErrorCode SetVolume(float v);
    float GetVolume();
};

}  // namespace liquids

#endif  // LIBLIQUIDS_HPP
