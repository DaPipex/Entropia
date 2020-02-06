#pragma once
#include "Object.h"
#include "Vector.h"
#include <vector>
#include "d3dx9math.h"
struct m_stOrbwalk //< Struktur für Orbwalker variablen
{
	CObject* championTarget;
	CObject* minionTarget;
	CObject* cforcedTarget;
	CObject* TargetToDraw;

	float LastAATick;
	bool forceTarget;

	std::vector<CObject*> jungleList;
	std::vector<CObject*> HeroList;
	std::vector<CObject*> TargetList;
	std::vector<CObject*> TurretList;
	std::vector<CObject*> NexusList;

	D3DXVECTOR2 previousMousePos;
}m_stOrbwalk;

class COrbwalker
{
public:
	static void Orbwalk();
	static void Attack(CObject* target);

	static void AttackLowestHPTarget();
	static void AttackLasthitTarget();
	static void AttackClearTarget();
	static void ForceTarget();
	static void CheckForceTargetDistance();
}COrbwalker;
