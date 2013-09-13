#include "gtest/gtest.h"
#include "calliform.hpp"

TEST(Dummy, test_this) {
    EXPECT_EQ(10, test_this(5, 2));
}

TEST(Dummy, Truthiness) {
    EXPECT_TRUE(true);
}
