#pragma once
#include <iostream>
#include <bitset>
#include <assert.h>
//#include "../Entities/Components/Components.h"	
//#include "../Entities/ComponentManager/ComponentArray.h"
//#include "../Entities/ComponentManager/ComponentManager.h"
//#include "../Entities/Systems/RenderSystem.h"

//using Entity = uint32_t;
//using ComponentType = uint8_t;

const uint32_t MAX_ENTITIES = 10;
const uint8_t MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;
