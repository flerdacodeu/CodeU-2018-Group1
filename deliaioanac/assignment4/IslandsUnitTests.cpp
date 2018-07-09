#include "Islands.cpp"
#include <gtest/gtest.h>

std::vector<std::vector<bool> > map;

TEST(CountingIslandsTest, EmptyMap) {
    EXPECT_EQ(0, countingIslands(map));
}

TEST(CountingIslandsTest, ExampleMap1) {
    map = {{false, true, false, true},
           {true, true, false, false},
           {false, false, true, false},
           {false, false, true, false}};

    EXPECT_EQ(3, countingIslands(map));
}

TEST(CountingIslandsTest, ExampleMap2) {
    map = {{false, true, false, true},
           {true, true, true, false},
           {false, false, true, false},
           {true, false, true, false}};

    EXPECT_EQ(3, countingIslands(map));
}

TEST(CountingIslandsTest, ExampleMap3) {
    map = {{true, true, false, true},
           {false, false, false, false},
           {false, false, false, false},
           {true, false, false, true}};

    EXPECT_EQ(4, countingIslands(map));
}

TEST(CountingIslandsTest, NoIslands) {
    map = {{false, false, false, false},
           {false, false, false, false},
           {false, false, false, false},
           {false, false, false, false}};

    EXPECT_EQ(0, countingIslands(map));
}

TEST(CountingIslandsTest, NoWaterFullIsland) {
    map = {{true, true},
           {true, true}};

    EXPECT_EQ(1, countingIslands(map));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
