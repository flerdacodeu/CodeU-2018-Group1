#pragma once

#include <array>
#include <vector>
#include <set>
#include <iostream>

template<size_t Rows, size_t Columns>
size_t count_islands(const std::array<std::array<bool, Columns>, Rows>& map)
{
    size_t counter = -1;

    std::vector<size_t*> islands;
    std::array<std::array<size_t*, Columns>, Rows> island_ptr{};

    for (size_t i = 0; i < Rows; ++i)
    {
        for (size_t j = 0; j < Columns; ++j)
        {
            if (!map[i][j])
                continue;

            size_t* top = i ? island_ptr[i - 1][j] : nullptr;
            size_t* left = j ? island_ptr[i][j - 1] : nullptr;

            if (top)
            {
                if (left)
                {
                    *top = *left;
                    island_ptr[i][j] = left;
                }
                else
                {
                    island_ptr[i][j] = top;
                }
            }
            else
            {
                if (left)
                {
                    island_ptr[i][j] = left;
                }
                else
                {
                    islands.push_back(new size_t(++counter));
                    island_ptr[i][j] = islands.back();
                }
            }
        }
    }

    std::set<size_t> unique;
    for (const auto& row : island_ptr)
        for (const auto& ptr : row)
            if (ptr)
                unique.insert(*ptr);

    for (size_t* island : islands)
        delete island;

    return unique.size();
}
