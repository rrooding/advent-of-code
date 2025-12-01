#include <gtest/gtest.h>

#include "Safe.hpp"

class Y2025D01SafeTest : public ::testing::Test {
protected:
    Safe safe;
};

TEST_F(Y2025D01SafeTest, InitialState) {
    EXPECT_EQ(safe.dialPosition(), 50);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 0);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 0);
}

TEST_F(Y2025D01SafeTest, TurnRightSmall) {
    safe.turnRight(10);
    EXPECT_EQ(safe.dialPosition(), 60);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 0);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 0);
}

TEST_F(Y2025D01SafeTest, TurnLeftSmall) {
    safe.turnLeft(10);
    EXPECT_EQ(safe.dialPosition(), 40);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 0);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 0);
}

TEST_F(Y2025D01SafeTest, TurnRightToZero) {
    safe.turnRight(50);
    EXPECT_EQ(safe.dialPosition(), 0);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 1);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 1);
}

TEST_F(Y2025D01SafeTest, TurnRightPastZero) {
    safe.turnRight(51);
    EXPECT_EQ(safe.dialPosition(), 1);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 0);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 1);
}

TEST_F(Y2025D01SafeTest, TurnLeftToZero) {
    safe.turnLeft(50);
    EXPECT_EQ(safe.dialPosition(), 0);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 1);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 1);
}

TEST_F(Y2025D01SafeTest, TurnLeftPastZero) {
    safe.turnLeft(51);
    EXPECT_EQ(safe.dialPosition(), 99);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 0);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 1);
}

TEST_F(Y2025D01SafeTest, TurnRightWrapAround) {
    safe.turnRight(150);
    EXPECT_EQ(safe.dialPosition(), 0);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 1);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 2);
}

TEST_F(Y2025D01SafeTest, TurnLeftWrapAround) {
    safe.turnLeft(150);
    EXPECT_EQ(safe.dialPosition(), 0);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 1);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 2);
}

TEST_F(Y2025D01SafeTest, MultipleZeroLandings) {
    safe.turnRight(50);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 1);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 1);

    safe.turnLeft(100);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 2);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 2);

    safe.turnRight(200);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 3);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 4);

    safe.turnLeft(300);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 4);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 7);
}

TEST_F(Y2025D01SafeTest, LargeTicks) {
    safe.turnRight(950);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 1);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 10);
}

TEST_F(Y2025D01SafeTest, LargeTicksLeft) {
    safe.turnLeft(850);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 1);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 9);
}

TEST_F(Y2025D01SafeTest, ExactMultipleOf100) {
    safe.turnRight(500);
    EXPECT_EQ(safe.dialPosition(), 50);
    EXPECT_EQ(safe.getNumberOfZeroLandings(), 0);
    EXPECT_EQ(safe.getNumberOfZeroPasses(), 5);
}