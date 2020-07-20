#pragma once

#include "Renderer.hpp"
#include "rlutil.h"

class RendererConsole : public Renderer
{
  public:
    virtual void render(const LifeSimulator& simulation) override;
};