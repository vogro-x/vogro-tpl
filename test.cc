//
// Created by xvvx on 18-9-2.
//

#include "template_engine.h"

#include <string>
#include <vector>

#include <gtest/gtest.h>


TEST(VstringTest, StringSplit) {
    std::string test_str1 = "hello,world,!";
    auto result1 = std::vector<std::string>{"hello", "world", "!"};
    ASSERT_EQ(vstring::split(test_str1, ","), result1);

    std::string test_str2 = "hello world !  ";
    auto result2 = std::vector<std::string>{"hello", "world", "!"};
    ASSERT_EQ(vstring::split(test_str2), result2);
}

TEST(VstringTest, StringStrip) {

}

TEST(VstringTest, StringLstrip) {

}

TEST(VstringTest, StringRstrip) {

}

TEST(VstringTest, StringJoin) {

}

TEST(VstringTest, StringStartWith) {

}

TEST(VstringTest, StringEndWith) {

}

TEST(StringToolTEST, StringUpper) {
    
}

TEST(VstringTest, StringLower) {
    
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

