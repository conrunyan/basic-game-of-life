#include "PatternGosperGliderGun.hpp"

#include <iostream>

PatternGosperGliderGun::PatternGosperGliderGun() :
    m_sizeX(BLOCK_SIZE_X),
    m_sizeY(BLOCK_SIZE_Y)
{
    initCells();
}

void PatternGosperGliderGun::initCells()
{
    std::vector<std::tuple<std::size_t, std::size_t>> liveCells = {
        {0, 24},
        {1, 22},
        {1, 24},
        {2, 12},
        {2, 13},
        {2, 20},
        {2, 21},
        {2, 34},
        {2, 35},
        {3, 11},
        {3, 15},
        {3, 20},
        {3, 21},
        {3, 34},
        {3, 35},
        {4, 0},
        {4, 1},
        {4, 10},
        {4, 16},
        {4, 20},
        {4, 21},
        {5, 0},
        {5, 1},
        {5, 10},
        {5, 14},
        {5, 16},
        {5, 17},
        {5, 22},
        {5, 24},
        {6, 10},
        {6, 16},
        {6, 24},
        {7, 11},
        {7, 15},
        {8, 12},
        {8, 13}};

    for (std::size_t row = 0; row < m_sizeY; row++)
    {
        std::vector<bool> tmpRow;
        for (std::size_t col = 0; col < m_sizeX; col++)
        {
            if (std::find(liveCells.begin(), liveCells.end(), std::make_tuple(row, col)) != liveCells.end())
            {
                tmpRow.push_back(true);
            }
            else
            {
                tmpRow.push_back(false);
            }
        }
        m_patternBoard.push_back(tmpRow);
    }
}

bool PatternGosperGliderGun::getCell(std::uint8_t x, std::uint8_t y) const
{
    // check if out of bounds
    if (x > m_sizeX - 1 || y > m_sizeY - 1)
    {
        return false;
    }

    return m_patternBoard[y][x];
}