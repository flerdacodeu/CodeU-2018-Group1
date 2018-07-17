#pragma once

#include <array>
#include <vector>
#include <set>

template<size_t Rows, size_t Columns>
size_t count_islands(const std::array<std::array<bool, Columns>, Rows>& map)
{
    // After the following loops each element of the `island_ptr` 
    // will hold a pointer to a element's corresponding island index.
    // Elements that corresponds to an `ocean` tile will hold nullptr
    std::array<std::array<size_t*, Columns>, Rows> island_ptr{};
    // `islands` hold all island-index pointers that will be allocated
    std::vector<size_t*> islands;

    // The main idea of the algorithm is that for each tile 
    // we look at it's neighboring tile's and pick current tile's island according to surrounding.
    // Each iteration of a loops will check only two `tile's` neighbors (a left and a top one),
    // this way, all neighboring pairs of tiles will be examined.
    for (size_t i = 0; i < Rows; ++i)
    {
        for (size_t j = 0; j < Columns; ++j)
        {
            if (!map[i][j])
                continue;

            // Get top and left tile's island-index pointers
            // and assume that non-existent tiles holds nullptr.
            // (for first line and first column)
            size_t* top = i ? island_ptr[i - 1][j] : nullptr;
            size_t* left = j ? island_ptr[i][j - 1] : nullptr;

            if (top) // if a top tile is a land
            {
                if (left) // and a left one is a land
                {
                    // ensure that both of them have the exact same island index.
                    // Note that different pointers can hold the same value.
                    *top = *left; 
                    island_ptr[i][j] = left;
                }
                else // and a left one is an ocean
                {
                    island_ptr[i][j] = top;
                }
            }
            else // if a top tile is an ocean
            {
                if (left) // and a left one is a land
                {
                    island_ptr[i][j] = left;
                }
                else // and a left one is an ocean
                {
                    // The only thing that we can do is to assume that this is a top-left tile of a new unexamined island
                    islands.push_back(new size_t(islands.size()));
                    island_ptr[i][j] = islands.back();
                }
            }
        }
    }

    // Now all we have to do is count the number of different island indices and free up resources
    std::set<size_t> unique;
    for (const auto& row : island_ptr)
        for (const auto& ptr : row)
            if (ptr)
                unique.insert(*ptr);

    for (size_t* island : islands)
        delete island;

    return unique.size();
}