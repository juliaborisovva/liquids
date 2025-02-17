#include "libliquids.hpp"

namespace liquids {

constexpr float kCubicMeterToLiters = 1000.0f;

Bottle::Bottle() : bottle_v_(0), liquids_m_(0) {}

Bottle::~Bottle() {}

float CalcLiquidM(float p, float v) { return v / kCubicMeterToLiters * p; }

ErrorCode Bottle::AddLiquid(uint8_t color, float p, float v)
{
    ErrorCode err = ErrorCode::kSuccess;
    // check conditions
    if (v <= 0) {
        // нельзя добавить объем жидкости <= 0
        err = ErrorCode::kInvalidV;
    } else if (this->bottle_v_ + v > max_bottle_v_) {
        // перельется через край
        // макс объем жидкости, который можем добавить max_bottle_v_ - this->bottle_v_
        err = ErrorCode::kTooMuchV;
    } else if (p <= 0) {
        // check p > 0
        // ошибка, плотность жидкости должна быть > 0
        err = ErrorCode::kInvalidP;
    } else {
        // add liquid into vector
        this->liquid_.push_back(Liquid(color, p, v));
        // Liquid* liq = new Liquid(color, p, v);
        // this->liquid_.push_back(*liq);
        // add liquid v to bottle_v
        this->bottle_v_ += v;
        // calc liquid_m, change liquids_m_
        this->liquids_m_ += CalcLiquidM(p, v);
    }
    return err;
}

ErrorCode Bottle::AddLiquid(const Liquid& liq)
{
    return this->AddLiquid(liq.GetColor(), liq.GetDensity(), liq.GetVolume());
}

ErrorCode Bottle::AddLiquid(const Liquid& liq, float v)
{
    return this->AddLiquid(liq.GetColor(), liq.GetDensity(), v);
}

/*
ErrorCode Bottle::RemoveLiquid(uint8_t color, float p, float v)
{
    ErrorCode err = ErrorCode::kSuccess;
    // check conditions
    // calc liquid_m, change liquids_m_
    this->liquids_m_ -= CalcLiquidM(p, v);
    return err;
}

ErrorCode Bottle::RemoveLiquid(const Liquid& liq) { return RemoveLiquid(liq.color_, liq.p_, liq.v_);
}

ErrorCode Bottle::RemoveLiquid(const Liquid& liq, float v) {
    return RemoveLiquid(liq.color_, liq.p_, v);
}*/

float Bottle::GetMaxBottleV() const { return this->max_bottle_v_; }

float Bottle::GetBottleV() const { return this->bottle_v_; }

float Bottle::GetMass() const { return this->liquids_m_; }

/*void Bottle::GetLiquidsInfo() const {}*/

bool Bottle::operator==(const Bottle& b) const
{
    return this->bottle_v_ == b.bottle_v_ && this->liquids_m_ == b.liquids_m_ &&
           this->liquid_ == b.liquid_;
}

bool Bottle::operator!=(const Bottle& b) const { return !(*this == b); }

}  // namespace liquids
