#pragma once
#include <Windows.h>
#include "OffsetsManager.h"
#include "Modules.h"
#include "Vector.h"
#include "CSpellCastInfo.h"
#include "CSpellData.h"


class CObject {
public:
	bool IsTurret();
	bool IsMinion();
	bool IsHero();
	bool IsNexus();
	bool IsMissile();
	bool IsDragon();
	bool IsBaron();

	bool IsInhibitor();
	bool IsTroyEnt();
	bool IsTargetable();

	static CObject* GetLocalObject() {
		auto retaddr = *(DWORD*)((DWORD)GetModuleHandle(NULL) + oLocalPlayer);
		if (retaddr == NULL)
			return NULL;

		return (CObject*)retaddr;
	}


	Vector GetPos() {
		return *(Vector*)((DWORD)this + oObjPos);
	}

	bool IsVisible() { //AIHeroClient
		return *(bool*)((DWORD)this + oObjVisibility);
	}

	/* Return the Distance to your player */
	float GetDistToMe(CObject* me) {
		return this->GetPos().DistTo(me->GetPos());
	}

	float GetAttackRange() {
		return *(float*)((DWORD)this + oObjAttackRange);
	}

	float GetTrueAttackRange()
	{
		return this->GetAttackRange() + this->GetBoundingRadius();
	}

	float GetBoundingRadius() { //AIHeroClient
		typedef float(__thiscall* OriginalFn)(PVOID);
		return CallVirtual<OriginalFn>(this, 36)(this);
	}

	float GetCurrentHealth() {
		return *(float*)((DWORD)this + oObjHealth);
	}

	inline float GetEffectiveHP() {
		return this->GetCurrentHealth() * (100.0f + this->GetArmor()) / 100.0f;
	}

	inline float GetTotalDamage(CObject* target)
	{
		return this->GetTotalAD() * (100 / (100 + target->GetArmor()));
	}

	float GetArmor() {
		return *(float*)((DWORD)this + oObjArmor);
	}

	bool IsEnemyTo(CObject* Obj) {
		if (Obj->GetTeam() == 100 && this->GetTeam() == 200)
			return true;

		else if (Obj->GetTeam() == 200 && this->GetTeam() == 100)
			return true;

		return false;
	}

	char* GetChampionName() {
		return GetStr((DWORD)this + oObjChampionName);
	}

	bool IsJungle()
	{
		if (this->GetTeam() == 300)
			return true;

		return false;
	}

	int GetTeam() {
		return *(int*)((DWORD)this + oObjTeam);
	}

	float GetBaseAD()
	{
		return *(float*)((DWORD)this + oObjBaseAtk);
	}

	float GetBonusAD()
	{
		return *(float*)((DWORD)this + oObjBonusAtk);
	}

	float GetTotalAD() {
		return GetBaseAD() + GetBonusAD();
	}

	bool IsAlive()
	{
		return this->GetCurrentHealth() > 0.f;
	}

	bool WaveclearCalc()
	{
		float distance = this->GetDistToMe(GetLocalObject());
		

		return this->GetCurrentHealth() <= GetLocalObject()->GetTotalAD() + distance;
	}

	bool IsLasthitable()
	{
		

		float distance = this->GetDistToMe(GetLocalObject()) /15;


		return this->GetCurrentHealth() <= GetLocalObject()->GetTotalAD() + distance; //distance added
	}

	bool IsValidTarget()
	{
		return this->IsAlive() && this->IsEnemyTo(GetLocalObject()) && this->IsInRange() && this->IsTargetable() && this->IsVisible();
	}

	bool IsObjective()
	{
		return this->IsTurret() || this->IsNexus() || this->IsInhibitor();
	}

	bool IsInRange()
	{
		return this->GetDistToMe(GetLocalObject()) < GetLocalObject()->GetTrueAttackRange();
	}

	short GetSourceIndex() {
		return *(short*)((DWORD)this + oObjSourceIndex);
	}

	DWORD GetNetworkID() {
		return *(DWORD*)((DWORD)this + oObjNetworkID);
	}

	/////////////////////////SPELL RELATED////////////////////////

	CSpellCastInfo* GetSpellCastInfo() {
		return *(CSpellCastInfo**)((DWORD)this + oMissileSpellInfo);
	}

	Vector GetSpellEndPos() {
		Vector spellEndPos = *(Vector*)((DWORD)this + oMissileEndPos);
		spellEndPos.Y += 100;
		return spellEndPos;
	}

	Vector GetSpellStartPos() {
		Vector startPos = *(Vector*)((DWORD)this + oMissileStartPos);
		startPos.Y += 100;
		return startPos;
	}

	float GetSpellSpeed() {
		return *(float*)(DWORD)this + 0x418;
	}
};