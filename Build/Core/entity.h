#pragma once

#include "meta-core.h"

//entity is going to use virtual memory to alloc space for entityID
struct entity : public virtual_memory
{
	int m_entityID;
};