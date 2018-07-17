#include "gtest/gtest.h"

#include "islands.h"

template<size_t Rows, size_t Columns>
size_t count_from_string(std::array<std::string, Rows> input)
{
    std::array<std::array<bool, Columns>, Rows> map;
    
    for (size_t i = 0; i < Rows; ++i)
        for (size_t j = 0; j < Columns; ++j)
            map[i][j] = input[i][j] == 'T';

    return count_islands(map);
}

TEST(count_islands_works, test_example) 
{
    auto actual = count_from_string<4, 4>({
        "FTFT",
        "TTFF",
        "FFTF",
        "FFTF"
    });

    EXPECT_EQ(3, actual);
}

TEST(count_islands_works, test_one_inside_other)
{
    auto actual = count_from_string<5, 5>({
        "TTTTT",
        "TFFFT",
        "TFTFT",
        "TFFFT",
        "TTTTT",
    });

    EXPECT_EQ(2, actual);
}

TEST(count_islands_works, test_spiral)
{
    auto actual = count_from_string<5, 5>({
        "TTTTT",
        "FFFFT",
        "TTTFT",
        "TFFFT",
        "TTTTT",
    });

    EXPECT_EQ(1, actual);
}

TEST(count_islands_works, test_empty)
{
    auto actual = count_from_string<3, 5>({
        "FFFFF",
        "FFFFF",
        "FFFFF",
    });

    EXPECT_EQ(0, actual);
}

TEST(count_islands_works, test_corners)
{
    auto actual = count_from_string<4, 4>({
        "TTFF",
        "TTFF",
        "FFTT",
        "FFTT",
    });

    EXPECT_EQ(2, actual);
}

TEST(count_islands_works, test_small)
{
    auto actual = count_from_string<1, 1>({
        "T"
    });

    EXPECT_EQ(1, actual);
}