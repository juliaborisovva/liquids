#include <gtest/gtest.h>

#include "libliquids.hpp"

// конструкторы жидкости
TEST(Liquid_constr, CreateLiquidWithoutArgs) { EXPECT_NO_THROW(liquids::Liquid()); }

TEST(Liquid_constr, CreateLiquidWithArgs) { EXPECT_NO_THROW(liquids::Liquid(233, 550, 0.1)); }

TEST(Liquid_constr, CreateLiquidWithArgsInvalidP)
{
    EXPECT_THROW(liquids::Liquid(233, 0, 0.1), std::invalid_argument);
    EXPECT_THROW(liquids::Liquid(233, -5, 0.1), std::invalid_argument);
}

TEST(Liquid_constr, CreateLiquidWithArgsInvalidV)
{
    EXPECT_THROW(liquids::Liquid(233, 550, 0), std::invalid_argument);
    EXPECT_THROW(liquids::Liquid(233, 550, -5), std::invalid_argument);
}

// проверка мутаторов в жидкости
TEST(Liquid_mutator, SetDensityWithValidP)
{
    liquids::Liquid example;
    EXPECT_EQ(example.SetDensity(550), liquids::ErrorCode::kSuccess);
}

TEST(Liquid_mutator, SetDensityWithInvalidP)
{
    liquids::Liquid example;
    EXPECT_EQ(example.SetDensity(0), liquids::ErrorCode::kInvalidP);
    EXPECT_EQ(example.SetDensity(-5), liquids::ErrorCode::kInvalidP);
}

TEST(Liquid_mutator, SetVolumeWithValidV)
{
    liquids::Liquid example;
    EXPECT_EQ(example.SetVolume(0.1), liquids::ErrorCode::kSuccess);
}

TEST(Liquid_mutator, SetVolumeWithInvalidV)
{
    liquids::Liquid example;
    EXPECT_EQ(example.SetVolume(0), liquids::ErrorCode::kInvalidV);
    EXPECT_EQ(example.SetVolume(-5), liquids::ErrorCode::kInvalidV);
}

// операторы сравнения == !=
TEST(Liquid_operator, OperatorEq)
{
    liquids::Liquid example;
    liquids::Liquid example2;
    liquids::Liquid example3(255, 100, 0.1);

    EXPECT_EQ(example == example2, true);
    EXPECT_EQ(example == example3, false);
}

TEST(Liquid_operator, OperatorNotEq)
{
    liquids::Liquid example;
    liquids::Liquid example2;
    liquids::Liquid example3(255, 100, 0.1);

    EXPECT_EQ(example != example2, false);
    EXPECT_EQ(example != example3, true);
}

// конструктор бутылки
TEST(Bottle_constr, CreateBottleWithoutArgs) { EXPECT_NO_THROW(liquids::Bottle()); }

// Mutator: Add
TEST(Bottle_mutator, AddLiquidSuccess)
{
    liquids::Bottle b;
    EXPECT_EQ(b.AddLiquid(255, 500, 0.1), liquids::ErrorCode::kSuccess);
}

TEST(Bottle_mutator, AddLiquidInvalidP)
{
    liquids::Bottle b;
    EXPECT_EQ(b.AddLiquid(255, -5, 0.1), liquids::ErrorCode::kInvalidP);
}

TEST(Bottle_mutator, AddLiquidInvalidV)
{
    liquids::Bottle b;
    EXPECT_EQ(b.AddLiquid(255, 500, -5), liquids::ErrorCode::kInvalidV);
}

TEST(Bottle_mutator, AddLiquidTooMuchV)
{
    liquids::Bottle b;
    EXPECT_EQ(b.AddLiquid(255, 500, 2.5), liquids::ErrorCode::kTooMuchV);
}

// Add with object reference
TEST(Bottle_mutator, AddLiquidRefSuccess)
{
    liquids::Bottle b;
    liquids::Liquid liq(255, 500, 0.1);
    EXPECT_EQ(b.AddLiquid(liq), liquids::ErrorCode::kSuccess);
}

TEST(Bottle_mutator, AddLiquidRefTooMuchV)
{
    liquids::Bottle b;
    liquids::Liquid liq(255, 500, 2.5);
    EXPECT_EQ(b.AddLiquid(liq), liquids::ErrorCode::kTooMuchV);
}

// Add ref + v
TEST(Bottle_mutator, AddLiquidRefVSuccess)
{
    liquids::Bottle b;
    liquids::Liquid liq(255, 500, 3);
    EXPECT_EQ(b.AddLiquid(liq, 0.1), liquids::ErrorCode::kSuccess);
}

TEST(Bottle_mutator, AddLiquidRefVTooMuchV)
{
    liquids::Bottle b;
    liquids::Liquid liq(255, 500, 0.1);
    EXPECT_EQ(b.AddLiquid(liq, 2.5), liquids::ErrorCode::kTooMuchV);
}

TEST(Bottle_mutator, AddLiquidRefVInvalidV)
{
    liquids::Bottle b;
    liquids::Liquid liq(255, 500, 0.1);
    EXPECT_EQ(b.AddLiquid(liq, -5), liquids::ErrorCode::kInvalidV);
}

// Mutator: Remove
// ErrorCode RemoveLiquid(uint8_t color = 255, float p = 100.0, float v = 0.1);
// норм, инвалид р <= 0, инвалид v <= 0,
// bottle_v - v < 0 - tooMuchV/VLTZERO невозможно вылить больше, чем в бутылке есть
// нет такой жидкости kNotFoundLiquid

// TEST(Bottle_mutator, RemoveLiquidSuccess) {
//    liquids::Bottle b;
//    b.AddLiquid(255, 500, 0.2);
//    EXPECT_EQ(b.RemoveLiquid(255, 500, 0.2), liquids::ErrorCode::kSuccess);
//}

// Rem with ref
// ErrorCode RemoveLiquid(const Liquid& liq);
// норм, bottle_v - v < 0 - tooMuchV/VLTZERO невозможно вылить больше, чем в бутылке есть
// нет такой жидкости kNotFoundLiquid

// Rem with ref + v
// ErrorCode RemoveLiquid(const Liquid& liq, float v);
// норм, инвалид v <= 0, bottle_v - v < 0 - tooMuchV/VLTZERO невозможно вылить больше,
// чем в бутылке есть, нет такой жидкости kNotFoundLiquid

// Accessor: v бутылки
TEST(Bottle_Accessor, GetBottleV)
{
    liquids::Bottle b;
    EXPECT_FLOAT_EQ(b.GetBottleV(), 0.0f);
}

TEST(Bottle_Accessor, GetBottleVAdd)
{
    liquids::Bottle b;
    b.AddLiquid(255, 500, 0.2);

    EXPECT_FLOAT_EQ(b.GetBottleV(), 0.2);
}

// Accessor: m бутылки (жидкостей в ней)
TEST(Bottle_Accessor, GetMass)
{
    liquids::Bottle b;
    EXPECT_FLOAT_EQ(b.GetMass(), 0.0f);
}

TEST(Bottle_Accessor, GetMassAdd)
{
    liquids::Bottle b;
    b.AddLiquid(255, 500, 0.2);

    EXPECT_FLOAT_EQ(b.GetMass(), 0.2f / 1000.0f * 500.0f);
}

// Accessor: Инфо о жидкостях в бутылке
// void GetLiquidsInfo();
// TEST(Bottle_Accessor, GetLiquidsInfo) {}
