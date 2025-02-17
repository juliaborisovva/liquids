#ifndef LIBLIQUIDS_HPP
#define LIBLIQUIDS_HPP

#include <cstdint>
#include <vector>

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

class Bottle
{
   private:
    static constexpr float max_bottle_v_ = 2.0f;
    float bottle_v_;
    float liquids_m_;
    std::vector<Liquid> liquid_;

   public:
    Bottle();
    ~Bottle();

    ErrorCode AddLiquid(uint8_t color = 255, float p = 100.0, float v = 0.1);
    ErrorCode AddLiquid(const Liquid& liq);
    ErrorCode AddLiquid(const Liquid& liq, float v);

    /*ErrorCode RemoveLiquid(uint8_t color = 255, float p = 100.0, float v = 0.1);
    ErrorCode RemoveLiquid(const Liquid& liq);
    ErrorCode RemoveLiquid(const Liquid& liq, float v);*/

    float GetMaxBottleV() const;
    float GetBottleV() const;
    float GetMass() const;
    /*void GetLiquidsInfo() const;*/

    // операторы сравнения
    bool operator==(const Bottle& b) const;
    bool operator!=(const Bottle& b) const;
};

}  // namespace liquids

#endif  // LIBLIQUIDS_HPP
