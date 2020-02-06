#pragma once
#include "Object.h"
#include "StaticEnums.h"
#include <math.h>
#include "d3dx9math.h"

class Typedefs
{
public:
	typedef float(__cdecl* fnGetAttackCastDelay)(CObject* pObj);
	typedef float(__cdecl* fnGetAttackDelay)(CObject* pObj);
	typedef int(__thiscall* fnGetPing)(void* thisptr);
	typedef bool(__cdecl* fnWorldToScreen)(Vector* in, D3DXVECTOR2* out);

	typedef bool(__cdecl* fnIsHero)(CObject* pObj);
	typedef bool(__cdecl* fnIsMinion)(CObject* pObj);
	typedef bool(__cdecl* fnIsTroyEnt)(CObject* pObj);
	typedef bool(__cdecl* fnIsDragon)(CObject* pObj);
	typedef bool(__cdecl* fnIsBaron)(CObject* pObj);
	typedef bool(__cdecl* fnIsInhib)(CObject* pObj);
	typedef bool(__cdecl* fnIsNexus)(CObject* pObj);
	typedef bool(__cdecl* fnIsTurret)(CObject* pObj);
	typedef bool(__cdecl* fnIsMissile)(CObject* pObj);
	typedef bool(__cdecl* fnIsVisible)(CObject* pObj);
	typedef void(__cdecl* fnDrawCircle)(Vector* position, float range, int* color, int a4, float a5, int a6, float alpha);
	typedef bool(__thiscall* fnIsAlive)(CObject* pObj);
	typedef bool(__thiscall* fnIsTargetable)(CObject* pObj);
};

class CFunctions
{
public:

	Typedefs::fnIsMinion IsMinion;
	Typedefs::fnIsHero IsHero;
	Typedefs::fnIsTargetable IsTargetable;
	Typedefs::fnIsAlive IsAlive;
	Typedefs::fnIsDragon IsDragon;
	Typedefs::fnIsTroyEnt IsTroyEnt;
	Typedefs::fnIsTurret IsTurret;
	Typedefs::fnIsInhib IsInhib;
	Typedefs::fnIsBaron IsBaron;
	Typedefs::fnIsNexus IsNexus;
	Typedefs::fnIsVisible IsVisible;
	Typedefs::fnDrawCircle DrawCircle;
	Typedefs::fnGetAttackCastDelay GetAttackCastDelay;
	Typedefs::fnGetAttackDelay GetAttackDelay;
	Typedefs::fnGetPing GetPing;
	Typedefs::fnWorldToScreen WorldToScreen;
	Typedefs::fnIsMissile IsMissile;
};

extern CFunctions Functions;
