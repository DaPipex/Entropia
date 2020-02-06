#include "stdafx.h"
#include "Object.h"
#include "GameFunctions.h"
#include "Engine.h"




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


bool CObject::IsAlive()
{
	return Functions.IsAlive(this);
}

bool CObject::IsTroyEnt()
{
	return Functions.IsTroyEnt(this);
}

bool CObject::IsTurret()
{
	return Functions.IsTurret(this);
}