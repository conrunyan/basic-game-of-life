#pragma once

#include <cstdint>
#include <vector>

//-------------------------------
//
// Abstract class that all pattern
// types will inherit from.
//
//-------------------------------
class Pattern
{
  public:
    virtual std::uint8_t getSizeX() const = 0;
    virtual std::uint8_t getSizeY() const = 0;
    virtual bool getCell(std::uint8_t x, std::uint8_t y) const = 0;

  private:
    virtual void initCells() = 0;
};