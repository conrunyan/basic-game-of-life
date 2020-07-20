#include "PatternGlider.hpp"

PatternGlider::PatternGlider() :
    m_sizeX(BLOCK_SIZE_X),
    m_sizeY(BLOCK_SIZE_Y)
{
    initCells();
}

void PatternGlider::initCells()
{
    std::vector<bool> rowOne = {true, false, false};
    std::vector<bool> rowTwo = {false, true, true};
    std::vector<bool> rowThree = {true, true, false};

    m_patternBoard.push_back(rowOne);
    m_patternBoard.push_back(rowTwo);
    m_patternBoard.push_back(rowThree);
}

bool PatternGlider::getCell(std::uint8_t x, std::uint8_t y) const
{
    // check if out of bounds
    if (x > m_sizeX - 1 || y > m_sizeY - 1)
    {
        return false;
    }

    return m_patternBoard[y][x];
}