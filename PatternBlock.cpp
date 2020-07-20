#include "PatternBlock.hpp"

PatternBlock::PatternBlock() :
    m_sizeX(BLOCK_SIZE),
    m_sizeY(BLOCK_SIZE)
{
    initCells();
}

void PatternBlock::initCells()
{
    for (std::size_t row = 0; row < m_sizeY; row++)
    {
        std::vector<bool> tmpVec;
        for (std::size_t column = 0; column < m_sizeX; column++)
        {
            tmpVec.push_back(true);
        }
        m_patternBoard.push_back(tmpVec);
    }
}

bool PatternBlock::getCell(std::uint8_t x, std::uint8_t y) const
{
    // check if out of bounds
    if (x > m_sizeX - 1 || y > m_sizeY - 1)
    {
        return false;
    }

    return m_patternBoard[y][x];
}