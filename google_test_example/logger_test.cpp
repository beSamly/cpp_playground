#include "pch.h"
#include "../logger_class/logger.h"
#include "../logger_class/logger.cpp"

TEST(LoggerClassTest, TestCase1)
{
    Logger logger;
    logger.Info("testing");
    logger.Debug("asdfsa");

    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}

TEST(LoggerClassTest, TestCase2)
{
    EXPECT_EQ(1, 1);
    EXPECT_TRUE(true);
}