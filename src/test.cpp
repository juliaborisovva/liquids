#include <gtest/gtest.h>

#include "libliquids.hpp"

// конструкторы жидкости
TEST(Liquid, CreateLiquidWithoutArgs)
{
    EXPECT_NO_THROW(liquids::Liquid());
}

TEST(Liquid, CreateLiquidWithArgs)
{
    EXPECT_NO_THROW(liquids::Liquid(233, 550, 0.1));
}

TEST(Liquid, CreateLiquidWithArgsInvalidP)
{
    EXPECT_THROW(liquids::Liquid(233, 0, 0.1), std::invalid_argument);
    EXPECT_THROW(liquids::Liquid(233, -5, 0.1), std::invalid_argument);
}

TEST(Liquid, CreateLiquidWithArgsInvalidV)
{
    EXPECT_THROW(liquids::Liquid(233, 550, 0), std::invalid_argument);
    EXPECT_THROW(liquids::Liquid(233, 550, -5), std::invalid_argument);
}

// проверка мутаторов в жидкости
TEST(Liquid, SetDensityWithValidP)
{
    liquids::Liquid example;
    EXPECT_EQ(example.SetDensity(550), liquids::ErrorCode::kSuccess);
}

TEST(Liquid, SetDensityWithInvalidP)
{
    liquids::Liquid example;
    EXPECT_EQ(example.SetDensity(0), liquids::ErrorCode::kInvalidP);
    EXPECT_EQ(example.SetDensity(-5), liquids::ErrorCode::kInvalidP);
}

TEST(Liquid, SetVolumeWithValidV)
{
    liquids::Liquid example;
    EXPECT_EQ(example.SetVolume(0.1), liquids::ErrorCode::kSuccess);
}

TEST(Liquid, SetVolumeWithInvalidV)
{
    liquids::Liquid example;
    EXPECT_EQ(example.SetVolume(0), liquids::ErrorCode::kInvalidV);
    EXPECT_EQ(example.SetVolume(-5), liquids::ErrorCode::kInvalidV);
}
