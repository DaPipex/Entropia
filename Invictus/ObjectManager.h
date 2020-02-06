#pragma once
#include "Modules.h"
#include "Object.h"

class CObjectManager {
public:
	union {
		DEFINE_MEMBER_0(void* base, 0x0);
		DEFINE_MEMBER_N(CObject** Objects, 0x0 + 0x8);
		DEFINE_MEMBER_N(int pMaxObjects, 0x4 + 0x8);
		DEFINE_MEMBER_N(int size, 0x8 + 0x8);
		DEFINE_MEMBER_N(int pHighestIndex, 0xC + 0x8);
	};
};
extern CObjectManager* ObjectManager;