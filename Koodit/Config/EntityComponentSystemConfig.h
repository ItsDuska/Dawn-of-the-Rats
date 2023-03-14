#pragma once
#include <iostream>
#include <bitset>
#include <assert.h>

using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

const Entity MAX_ENTITIES = 100;
const ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;
