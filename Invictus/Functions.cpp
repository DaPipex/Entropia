#include "stdafx.h"
#include "Object.h"
#include "GameFunctions.h"

// internal function calling


bool CObject::IsHero() {
	return Functions.IsHero(this);
}





bool CObject::IsTargetable() {
	return Functions.IsTargetable(this);
}

bool CObject::IsMinion()
{
	return Functions.IsMinion(this);
}

bool CObject::IsDragon()
{
	return Functions.IsDragon(this);
}

bool CObject::IsInhibitor()
{
	return Functions.IsInhib(this);
}

bool CObject::IsNexus()
{
	return Functions.IsNexus(this);
}

bool CObject::IsMissile()
{
	return Functions.IsMissile(this);
}

bool CObject::IsBaron()
{
	return Functions.IsBaron(this);
}

bool CObject::IsTroyEnt()
{
	return Functions.IsTroyEnt(this);
}

bool CObject::IsTurret()
{
	return Functions.IsTurret(this);
}