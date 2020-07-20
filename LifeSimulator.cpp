#include "LifeSimulator.hpp"

LifeSimulator::LifeSimulator(std::uint8_t sizeX, std::uint8_t sizeY) :
    m_sizeX(sizeX),
    m_sizeY(sizeY)
{
    initCells();
}

void LifeSimulator::insertPattern(const Pattern& pattern, std::uint8_t startX, std::uint8_t startY)
{

    // check for invalid startX and Y positions
    if (startX > m_sizeX - 1 || startY > m_sizeY - 1)
    {
        return;
    }

    // check for shape inserted at an invalid location
    if ((pattern.getSizeX() + startX > m_sizeX) || (pattern.getSizeY() + startY > m_sizeY))
    {
        return;
    }

    //    startX = static_cast<std::size_t>(startX);
    //    startY = static_cast<std::size_t>(startY);

    for (std::size_t row = 0; row < pattern.getSizeY(); row++)
    {
        for (std::size_t col = 0; col < pattern.getSizeX(); col++)
        {
            // insert based on x/y coordinates (x being cols, y being rows)

            m_patternBoard[startY + row][startX + col] = pattern.getCell(static_cast<std::uint8_t>(col), static_cast<std::uint8_t>(row));
        }
    }
}

void LifeSimulator::update()
{
    std::vector<std::vector<bool>> newBoard = m_patternBoard;
    for (std::uint8_t row = 0; row < m_sizeY; row++)
    {
        for (std::uint8_t col = 0; col < m_sizeX; col++)
        {
            // tries each rule, continuing on if that rule was applicable
            if (executeRuleOne(row, col, newBoard))
            {
                continue;
            }
            else if (executeRuleTwo(row, col, newBoard))
            {
                continue;
            }
            else if (executeRuleThree(row, col, newBoard))
            {
                continue;
            }
            else if (executeRuleFour(row, col, newBoard))
            {
                continue;
            }
        }
    }

    m_patternBoard = newBoard;
}

void LifeSimulator::initCells()
{
    for (std::size_t row = 0; row < m_sizeY; row++)
    {
        std::vector<bool> tmpVec;
        for (std::size_t column = 0; column < m_sizeX; column++)
        {
            tmpVec.push_back(false);
        }
        m_patternBoard.push_back(tmpVec);
    }
}

bool LifeSimulator::getCell(std::uint8_t x, std::uint8_t y) const
{
    // check if out of bounds
    if (x > m_sizeX - 1 || y > m_sizeY - 1)
    {
        return false;
    }

    return m_patternBoard[y][x];
}

// 1 - Any live cell with fewer than two live neighbours dies, as if by underpopulation.
// returns true if rule was applied
bool LifeSimulator::executeRuleOne(std::uint8_t x, std::uint8_t y, std::vector<std::vector<bool>>& newBoard)
{
    x = static_cast<int>(x);
    y = static_cast<int>(y);

    if (getNumNeighbors(x, y) < 2 && getCell(x, y))
    {
        newBoard[y][x] = false;
        return true;
    }
    return false;
}

// 2 - Any live cell with two or three live neighbours lives on to the next generation.
// returns true if rule was applied
bool LifeSimulator::executeRuleTwo(std::uint8_t x, std::uint8_t y, std::vector<std::vector<bool>>& newBoard)
{

    x = static_cast<int>(x);
    y = static_cast<int>(y);

    std::size_t liveNeighbors = getNumNeighbors(x, y);
    if ((liveNeighbors == 2 || liveNeighbors == 3) && getCell(x, y))
    {
        newBoard[y][x] = true;
        return true;
    }
    return false;
}

// 3 - Any live cell with more than three live neighbours dies, as if by overpopulation.
// returns true if rule was applied
bool LifeSimulator::executeRuleThree(std::uint8_t x, std::uint8_t y, std::vector<std::vector<bool>>& newBoard)
{

    x = static_cast<int>(x);
    y = static_cast<int>(y);

    std::size_t liveNeighbors = getNumNeighbors(x, y);
    if (liveNeighbors > 3 && getCell(x, y))
    {
        newBoard[y][x] = false;
        return true;
    }
    return false;
}

// 4 - Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
// returns true if rule was applied
bool LifeSimulator::executeRuleFour(std::uint8_t x, std::uint8_t y, std::vector<std::vector<bool>>& newBoard)
{

    x = static_cast<int>(x);
    y = static_cast<int>(y);

    std::size_t liveNeighbors = getNumNeighbors(x, y);
    if (liveNeighbors == 3 && !getCell(x, y))
    {
        newBoard[y][x] = true;
        return true;
    }
    return false;
}

std::size_t LifeSimulator::getNumNeighbors(int x, int y)
{
    std::size_t liveNeighbors = 0;
    for (int row = x - 1; row < x + 2; row++)
    {
        for (int col = y - 1; col < y + 2; col++)
        {
            // if neighbor is alive,

            if (getCell(static_cast<std::uint8_t>(row), static_cast<std::uint8_t>(col)) && !(row == x && col == y))
            {
                liveNeighbors++;
            }
        }
    }

    return liveNeighbors;
}