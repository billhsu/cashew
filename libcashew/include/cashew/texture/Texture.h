#pragma once
#include <stdint.h>
#include <string>

namespace cashew
{
class Texture
{
public:
    virtual uint32_t loadTexture(std::string fileName);
};
};
