#include "LifeSimulator.hpp"
#include "PatternAcorn.hpp"
#include "PatternBlinker.hpp"
#include "PatternBlock.hpp"
#include "PatternGlider.hpp"
#include "PatternGosperGliderGun.hpp"
#include "RendererConsole.hpp"

#include <iostream>
#include <thread>

int main()
{

    LifeSimulator sim(200, 200);
    RendererConsole renderer;

    PatternGlider glider;
    PatternAcorn acorn;
    PatternBlinker blinker;
    PatternBlock block;
    PatternGosperGliderGun gun;

    sim.insertPattern(blinker, 5, 5);
    sim.insertPattern(glider, 10, 10);
    sim.insertPattern(gun, 15, 1);
    sim.insertPattern(acorn, 100, 20);
    sim.insertPattern(block, 2, 20);

    while (true)
    {
        sim.update();
        renderer.render(sim);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}