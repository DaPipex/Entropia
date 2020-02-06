#pragma once
#include "Object.h"

class CSpellData
{
public:
	float GetMissileLineWidth()
	{
		return  *(float*)((DWORD)this + 0x44C);
	}

	char* GetMissileName() {
		return GetStr((DWORD)this + 0x58);
	}

	short GetCasterIndex() {
		return *(short*)((DWORD)this + oObjSourceIndex);
	}
};
