// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include "header.hpp"
TEST(SharedPtr, value )
{
    int*a = new int;
    a[0] = 10;
    int*b = new int;
    b[0] = 20;
    SharedPtr<int> test(a);
    EXPECT_EQ(static_cast<int>(test.get()[0]), 10);
//    SharedPtr<int> test2(test);
//    EXPECT_EQ(static_cast<int>(test2.get()[0]), 10);
    SharedPtr<int> test3(b);
    test.swap(test3);
    EXPECT_EQ(static_cast<int>(test.get()[0]), 20);
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
