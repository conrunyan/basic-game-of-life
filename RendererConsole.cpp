#include "RendererConsole.hpp"

void RendererConsole::render(const LifeSimulator& simulation)
{
    rlutil::cls();
    rlutil::hidecursor();
    rlutil::setBackgroundColor(rlutil::BLACK);

    for (int x = 0; x < simulation.getSizeX(); x++)
    {
        for (int y = 0; y < simulation.getSizeY(); y++)
        {
            // only draw cell if it is live
            if (simulation.getCell(static_cast<std::uint8_t>(x), static_cast<std::uint8_t>(y)))
            {
                rlutil::locate(x, y);
                rlutil::setColor(rlutil::GREEN);
                rlutil::setChar('x');
            }
        }
    }
    rlutil::locate(0, 0);
}