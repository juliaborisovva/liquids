#include <gtest/gtest.h>

#include "libliquids.hpp"

// конструкторы жидкости
TEST(Liquid_constr, CreateLiquidWithoutArgs)
{
    EXPECT_NO_THROW(liquids::Liquid());
}

TEST(Liquid_constr, CreateLiquidWithArgs)
{
    EXPECT_NO_THROW(liquids::Liquid(233, 550, 0.1));
}

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
