#include "LifeSimulator.hpp"
#include "PatternAcorn.hpp"
#include "PatternBlinker.hpp"
#include "PatternBlock.hpp"
#include "PatternGlider.hpp"
#include "PatternGosperGliderGun.hpp"

#include "gtest/gtest.h"
#include <algorithm>
#include <iostream>

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(PatternBlock_getCell, FailsOnOutOfBounds)
{
    PatternBlock patBlock;

    ASSERT_FALSE(patBlock.getCell(-1, -1));
    ASSERT_FALSE(patBlock.getCell(1, -1));
    ASSERT_FALSE(patBlock.getCell(-1, 1));
    ASSERT_FALSE(patBlock.getCell(200, 200));
    ASSERT_FALSE(patBlock.getCell(200, 0));
    ASSERT_FALSE(patBlock.getCell(0, 200));
}

TEST(PatternBlock_getCell, LiveCellInPattern)
{
    PatternBlock patBlock;

    ASSERT_TRUE(patBlock.getCell(0, 0));
    ASSERT_TRUE(patBlock.getCell(1, 0));
    ASSERT_TRUE(patBlock.getCell(0, 1));
    ASSERT_TRUE(patBlock.getCell(1, 1));
}

TEST(PatternAcorn_getCell, ValidatePattern)
{
    PatternAcorn patAcorn;

    // row one
    ASSERT_FALSE(patAcorn.getCell(0, 0));
    ASSERT_TRUE(patAcorn.getCell(1, 0));
    ASSERT_FALSE(patAcorn.getCell(2, 0));
    ASSERT_FALSE(patAcorn.getCell(3, 0));
    ASSERT_FALSE(patAcorn.getCell(4, 0));
    ASSERT_FALSE(patAcorn.getCell(5, 0));
    ASSERT_FALSE(patAcorn.getCell(6, 0));

    // row two
    ASSERT_FALSE(patAcorn.getCell(0, 1));
    ASSERT_FALSE(patAcorn.getCell(1, 1));
    ASSERT_FALSE(patAcorn.getCell(2, 1));
    ASSERT_TRUE(patAcorn.getCell(3, 1));
    ASSERT_FALSE(patAcorn.getCell(4, 1));
    ASSERT_FALSE(patAcorn.getCell(5, 1));
    ASSERT_FALSE(patAcorn.getCell(6, 1));

    // row three
    ASSERT_TRUE(patAcorn.getCell(0, 2));
    ASSERT_TRUE(patAcorn.getCell(1, 2));
    ASSERT_FALSE(patAcorn.getCell(2, 2));
    ASSERT_FALSE(patAcorn.getCell(3, 2));
    ASSERT_TRUE(patAcorn.getCell(4, 2));
    ASSERT_TRUE(patAcorn.getCell(5, 2));
    ASSERT_TRUE(patAcorn.getCell(6, 2));
}

TEST(PatternAcorn_getCell, FailsOnOutOfBounds)
{
    PatternAcorn patAcorn;

    ASSERT_FALSE(patAcorn.getCell(-1, -1));
    ASSERT_FALSE(patAcorn.getCell(1, -1));
    ASSERT_FALSE(patAcorn.getCell(-1, 1));
    ASSERT_FALSE(patAcorn.getCell(200, 200));
    ASSERT_FALSE(patAcorn.getCell(200, 0));
    ASSERT_FALSE(patAcorn.getCell(0, 200));
}

TEST(PatternBlinker_getCell, LiveCellInPattern)
{
    PatternBlinker patBlink;

    ASSERT_TRUE(patBlink.getCell(0, 0));
    ASSERT_TRUE(patBlink.getCell(0, 1));
    ASSERT_TRUE(patBlink.getCell(0, 2));
}

TEST(PatternBlinker_getCell, FailsOnOutOfBounds)
{
    PatternBlinker patBlink;

    ASSERT_FALSE(patBlink.getCell(-1, -1));
    ASSERT_FALSE(patBlink.getCell(1, -1));
    ASSERT_FALSE(patBlink.getCell(-1, 1));
    ASSERT_FALSE(patBlink.getCell(200, 200));
    ASSERT_FALSE(patBlink.getCell(200, 0));
    ASSERT_FALSE(patBlink.getCell(0, 200));
}

TEST(PatternGlider_getCell, LiveCellInPattern)
{
    PatternGlider patGlid;

    // row one
    ASSERT_TRUE(patGlid.getCell(0, 0));
    ASSERT_FALSE(patGlid.getCell(1, 0));
    ASSERT_FALSE(patGlid.getCell(2, 0));

    // row two
    ASSERT_FALSE(patGlid.getCell(0, 1));
    ASSERT_TRUE(patGlid.getCell(1, 1));
    ASSERT_TRUE(patGlid.getCell(2, 1));

    // row three
    ASSERT_TRUE(patGlid.getCell(0, 2));
    ASSERT_TRUE(patGlid.getCell(1, 2));
    ASSERT_FALSE(patGlid.getCell(2, 2));
}

TEST(PatternGlider_getCell, FailsOnOutOfBounds)
{
    PatternGlider patGlid;

    ASSERT_FALSE(patGlid.getCell(-1, -1));
    ASSERT_FALSE(patGlid.getCell(1, -1));
    ASSERT_FALSE(patGlid.getCell(-1, 1));
    ASSERT_FALSE(patGlid.getCell(200, 200));
    ASSERT_FALSE(patGlid.getCell(200, 0));
    ASSERT_FALSE(patGlid.getCell(0, 200));
}

TEST(PatternGosperGliderGun_getCell, FailsOnOutOfBounds)
{
    PatternGosperGliderGun glidGun;

    ASSERT_FALSE(glidGun.getCell(-1, -1));
    ASSERT_FALSE(glidGun.getCell(1, -1));
    ASSERT_FALSE(glidGun.getCell(-1, 1));
    ASSERT_FALSE(glidGun.getCell(200, 200));
    ASSERT_FALSE(glidGun.getCell(200, 0));
    ASSERT_FALSE(glidGun.getCell(0, 200));
}

TEST(LifeSimulator_getSizes, ValidateSizes)
{
    LifeSimulator sim(40, 30);

    ASSERT_EQ(40, sim.getSizeX());
    ASSERT_EQ(30, sim.getSizeY());
}

TEST(LifeSimulator_insertPattern, InsertBlockAtStart)
{
    LifeSimulator sim(40, 30);
    PatternBlock block;

    sim.insertPattern(block, 0, 0);

    ASSERT_TRUE(sim.getCell(0, 0));
    ASSERT_TRUE(sim.getCell(0, 1));
    ASSERT_TRUE(sim.getCell(1, 0));
    ASSERT_TRUE(sim.getCell(1, 1));
}

TEST(LifeSimulator_insertPattern, InsertBlockPartiallyOutOfBounds)
{
    LifeSimulator sim(1, 1);
    PatternBlock block;

    sim.insertPattern(block, 0, 0);

    ASSERT_FALSE(sim.getCell(0, 0));
    ASSERT_FALSE(sim.getCell(0, 1));
    ASSERT_FALSE(sim.getCell(1, 0));
    ASSERT_FALSE(sim.getCell(1, 1));
}

TEST(LifeSimulator_update, BlinkerActuallyBlinks)
{
    LifeSimulator sim(4, 4);
    PatternBlinker blink;

    sim.insertPattern(blink, 1, 1);

    ASSERT_TRUE(sim.getCell(1, 1));
    ASSERT_TRUE(sim.getCell(1, 2));
    ASSERT_TRUE(sim.getCell(1, 3));

    sim.update();

    ASSERT_TRUE(sim.getCell(0, 2));
    ASSERT_TRUE(sim.getCell(1, 2));
    ASSERT_TRUE(sim.getCell(2, 2));
}

/* Can't run this test unless getNumNeighbors is public

TEST(LifeSimulator_countNumNeighbors, CountNumberOfLiveNeighbors)
{
    LifeSimulator sim(40, 30);
    PatternBlock block;

    sim.insertPattern(block, 0, 0);

    ASSERT_EQ(3, sim.getNumNeighbors(0, 0));
}
*/