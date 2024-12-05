#include "lib/ranges.h"
#include <gtest/gtest.h>

#include <random>
#include <vector>
#include <ranges>


TEST(AdapterTests, LazyFilterAdapterTest) {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
    auto result = v | filter([](int i) { return i % 2 == 1; });

    std::vector<int> expected = { 1, 3, 5 };
    std::vector<int> actual;
    for (int i : result) {
        actual.push_back(i);
    }
    EXPECT_EQ(actual, expected);
}

TEST(AdapterTests, LazyTransformAdapterTest) {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
    auto result = v | transform([](int i) { return i * i; });

    std::vector<int> expected = { 1, 4, 9, 16, 25, 36 };
    std::vector<int> actual;
    for (int i : result) {
        actual.push_back(i);
    }
    EXPECT_EQ(actual, expected);
}

TEST(AdapterTests, LazyReverseAdapterTest) {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
    auto result = v | reverse();

    std::vector<int> expected = { 6, 5, 4, 3, 2, 1 };
    std::vector<int> actual;
    for (int i : result) {
        actual.push_back(i);
    }
    EXPECT_EQ(actual, expected);
}

TEST(AdapterTests, LazyTakeAdapterTest) {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
    auto result = v | take(3);

    std::vector<int> expected = { 1, 2, 3 };
    std::vector<int> actual;
    for (int i : result) {
        actual.push_back(i);
    }
    EXPECT_EQ(actual, expected);
}

TEST(AdapterTests, LazyDropAdapterTest) {
    std::vector<int> v = { 1, 2, 3, 4, 5, 6 };
    auto result = v | drop(3);

    std::vector<int> expected = { 4, 5, 6 };
    std::vector<int> actual;
    for (int i : result) {
        actual.push_back(i);
    }
    EXPECT_EQ(actual, expected);
}

TEST(AdapterTests, LazyKeysAdapterTest) {
    std::vector<std::pair<int, std::string>> v = { {1, "one"}, {2, "two"}, {3, "three"} };
    auto result = v | keys();

    std::vector<int> expected = { 1, 2, 3 };
    std::vector<int> actual;
    for (int i : result) {
        actual.push_back(i);
    }
    EXPECT_EQ(actual, expected);
}

TEST(AdapterTests, LazyValuesAdapterTest) {
    std::vector<std::pair<int, std::string>> v = { {1, "one"}, {2, "two"}, {3, "three"} };
    auto result = v | values();

    std::vector<std::string> expected = { "one", "two", "three" };
    std::vector<std::string> actual;
    for (const auto& value : result) {
        actual.push_back(value);
    }
    EXPECT_EQ(actual, expected);
}


TEST(PipelineTest, FullPipelineTest) {
    std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 19 };

    auto result = data
        | reverse()                                   
        | filter([](int i) { return i % 2 == 0; })   
        | transform([](int i) { return i * 2; })   
        | drop(1)                                    
        | take(2);                                   

    std::vector<int> expected = { 8, 4 }; 
    std::vector<int> out;
    for (const auto& i : result) {
        out.push_back(i);
    }

    EXPECT_EQ(out, expected);
}