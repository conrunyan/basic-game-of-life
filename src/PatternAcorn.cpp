#include "PatternAcorn.hpp"

PatternAcorn::PatternAcorn() :
    m_sizeX(BLOCK_SIZE_X),
    m_sizeY(BLOCK_SIZE_Y)
{
    initCells();
}

void PatternAcorn::initCells()
{
    std::vector<bool> rowOne = {false, true, false, false, false, false, false};
    std::vector<bool> rowTwo = {false, false, false, true, false, false, false};
    std::vector<bool> rowThree = {true, true, false, false, true, true, true};

    m_patternBoard.push_back(rowOne);
    m_patternBoard.push_back(rowTwo);
    m_patternBoard.push_back(rowThree);
}

bool PatternAcorn::getCell(std::uint8_t x, std::uint8_t y) const
{
    // check if out of bounds
    if (x > m_sizeX - 1 || y > m_sizeY - 1)
    {
        return false;
    }

    return m_patternBoard[y][x];
}