#include "PatternBlinker.hpp"

PatternBlinker::PatternBlinker() :
    m_sizeX(BLOCK_SIZE_X),
    m_sizeY(BLOCK_SIZE_Y)
{
    initCells();
}

void PatternBlinker::initCells()
{
    std::vector<bool> rowOne = {true};
    std::vector<bool> rowTwo = {true};
    std::vector<bool> rowThree = {true};

    m_patternBoard.push_back(rowOne);
    m_patternBoard.push_back(rowTwo);
    m_patternBoard.push_back(rowThree);
}

bool PatternBlinker::getCell(std::uint8_t x, std::uint8_t y) const
{
    // check if out of bounds
    if (x > m_sizeX - 1 || y > m_sizeY - 1)
    {
        return false;
    }

    return m_patternBoard[y][x];
}