#include "pch.h"
#include "../logger_class/logger.cpp"
#include "../logger_class/logger.h"

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