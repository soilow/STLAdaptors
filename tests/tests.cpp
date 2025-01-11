#include "gtest/gtest.h"
#include <ITMO_Adaptors/adaptors.h>
#include <string>

using namespace Misha_and_Murad;

TEST(FilterViewTests, Test1) {
    std::vector<int> vector = {1, 2, 3, 4, 5};
    auto temp = vector | take(3);
    
    std::string expected = "1 2 3 ";
    std::string result;
    
    for (int i : temp) {
        result += std::to_string(i) + " ";
    }
    
    EXPECT_EQ(result, expected);
}

TEST(FilterViewTests, Test2) {
    std::vector<int> vector = {1, 2, 3, 4, 5};
    auto temp = vector | transform([](int x) { return x * x; });
    
    std::string expected = "1 4 9 16 25 ";
    std::string result;
    
    for (int i : temp) {
        result += std::to_string(i) + " ";
    }
    
    EXPECT_EQ(result, expected);
}

TEST(FilterViewTests, Test3) {
    std::vector<int> vector = {1, 2, 3, 4, 5};
    auto temp = vector | drop(2);
    
    std::string expected = "3 4 5 ";
    std::string result;
    
    for (int i : temp) {
        result += std::to_string(i) + " ";
    }
    
    EXPECT_EQ(result, expected);
}

TEST(FilterViewTests, Test4) {
    std::vector<int> vector = {1, 2, 3, 4, 5};
    auto temp = vector | reverse();
    
    std::string expected = "5 4 3 2 1 ";
    std::string result;
    
    for (int i : temp) {
        result += std::to_string(i) + " ";
    }
    
    EXPECT_EQ(result, expected);
}

TEST(FilterViewTests, Test5) {
    std::vector<int> vector = {1, 2, 3, 4, 5};
    auto temp = vector | filter([](int x) { return x % 2 == 0; });
    
    std::string expected = "1 2 4 ";
    std::string result;
    
    for (int i : temp) {
        result += std::to_string(i) + " ";
    }
    
    EXPECT_EQ(result, expected);
}

TEST(FilterViewTests, Test6) {
    std::vector<int> vector = {1, 2, 3, 4, 5};
    
    std::string expected = "9 16 25 ";
    std::string result;
    
    for (int i : vector | transform([](int x){return x * x; }) | drop(2)) {
        result += std::to_string(i) + " ";
    }
    
    EXPECT_EQ(result, expected);
}

TEST(FilterViewTests, Test7) {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto temp = m | keys();
    
    std::string expected = "1 2 3 ";
    std::string result;
    
    for (int i : temp) {
        result += std::to_string(i) + " ";
    }
    
    EXPECT_EQ(result, expected);
}

TEST(FilterViewTests, Test8) {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto temp = m | values();
    
    std::string expected = "one two three ";
    std::string result;
    
    for (std::string i : temp) {
        result += i + " ";
    }
    
    EXPECT_EQ(result, expected);
}

TEST(FilterViewTests, Test9) {
    std::vector<int> vector = {1, 2, 3, 4, 5, 6, 7, 8};
    
    std::string expected = "25 16 ";
    std::string result;
    
    for (int i: vector | drop(3) | take(2) | transform([](int x){ return x * x; }) | reverse()) {
        result += std::to_string(i) + " ";
    }
    
    EXPECT_EQ(result, expected);
}

TEST(FilterViewTests, Test10) {
    std::vector<int> vector = {1, 2, 3, 4, 5, 6, 7, 8};
    
    std::string expected = "36 25 16 ";
    std::string result;
    
    for (int i: vector | reverse() | take(5) | drop(2) | transform([](int x){ return x * x; })) {
        result += std::to_string(i) + " ";
    }
    
    EXPECT_EQ(result, expected);
}

TEST(FilterViewTests, Test11) {
    std::vector<int> vector = {1, 2, 3, 4};
    
    std::string expected = "4 3 2 1 ";
    std::string result;
    
    for (int i: vector | reverse()) {
        result += std::to_string(i) + " ";
    }
    
    EXPECT_EQ(result, expected);
}

TEST(FilterViewTests, Test12) {
    std::vector<int> vector = {1, 2, 3, 4, 5, 6, 7, 8};
    
    std::string expected = "8 6 4 ";
    std::string result;
    
    for (int i: vector | reverse() | take(5) | filter([](int x){return x % 2 == 0;})) {
        result += std::to_string(i) + " ";
    }
    
    EXPECT_EQ(result, expected);
}

TEST(FilterViewTests, Test13) {
    std::vector<int> vector = {1, 2, 3, 4, 5, 6, 7, 8};
    
    std::string expected = "1 3 5 ";
    std::string result;
    
    for (int i : vector | filter([](int x){return x % 2 != 0;}) | take(3)) {
        result += std::to_string(i) + " ";
    }
    
    EXPECT_EQ(result, expected);
}

TEST(FilterViewTests, Test14) {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto temp = m | keys() | take(2);
    
    std::string expected = "1 2 ";
    std::string result;
    
    for (int i : temp) {
        result += std::to_string(i) + " ";
    }
    
    EXPECT_EQ(result, expected);
}

TEST(FilterViewTests, Test15) {
    std::map<int, std::string> m = {{1, "one"}, {2, "two"}, {3, "three"}};
    auto temp = m | values() | drop(1);
    
    std::string expected = "two three ";
    std::string result;
    
    for (std::string i : temp) {
        result += i + " ";
    }
    
    EXPECT_EQ(result, expected);
}
