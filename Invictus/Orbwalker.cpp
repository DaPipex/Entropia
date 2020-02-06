#pragma once
#include "pch.h"
#include <Windows.h>
#include "stdafx.h"
#include "Engine.h"
#include "ObjectManager.h"
#include "Orbwalk.h"
#include "d3dx9math.h"

CFunctions Functions;
DWORD BaseAddress;
CObject* LocalPlayer;
CObjectManager* ObjectManager;

//attacked das target das am wenigsten HP hat
/*
void COrbwalker::AttackLowestHPTarget()
{
	
		for (size_t i = 0; i < m_stOrbwalk.HeroList.size(); i++)
		{
			if (m_stOrbwalk.HeroList[i]->IsValidTarget() && Engine::IsInObjManager(m_stOrbwalk.HeroList[i]))
			{
				m_stOrbwalk.TargetList.push_back(m_stOrbwalk.HeroList[i]);
			}
		}
	

	if (m_stOrbwalk.TargetList.size() > 0 && Engine::CanAttack()) //Wenn mindestens 1 target in range..
	{
		
		CObject* temp = m_stOrbwalk.TargetList[0];
		for (size_t i = 0; i < m_stOrbwalk.TargetList.size(); i++)
		{
			if (Engine::IsInObjManager(temp) && Engine::IsInObjManager(m_stOrbwalk.TargetList[i]))
			{
				if (m_stOrbwalk.TargetList[i]->GetCurrentHealth() < temp->GetCurrentHealth())
				{
					temp = m_stOrbwalk.TargetList[i];
				}
			}
			
		}
		if (m_stOrbwalk.forceTarget == true && m_stOrbwalk.forceTarget != NULL && Engine::IsInObjManager(m_stOrbwalk.cforcedTarget))
			temp = m_stOrbwalk.cforcedTarget;

			if (Engine::IsInObjManager(temp) && temp!=nullptr && temp->IsValidTarget());
			Engine::IssueAttack(temp);
			m_stOrbwalk.LastAATick = Engine::GetGameTimeTickCount() - Engine::GetPing() / 100 ;
	}
	else if(Engine::CanMove(100.f))
	{
		Engine::IssueMove(&Engine::GetMouseWorldPosition());
	}
	m_stOrbwalk.TargetList.clear();
}
*/


void COrbwalker::AttackLowestHPTarget()
{
	 CObject* target = NULL;


	if (m_stOrbwalk.forceTarget == true)
		target = m_stOrbwalk.cforcedTarget;

	if(m_stOrbwalk.forceTarget == false)
	for (size_t i = 0; i < m_stOrbwalk.HeroList.size(); i++)
	{
		if (Engine::IsInObjManager(ObjectManager->Objects[i]))
		{
			if (m_stOrbwalk.HeroList[i]->IsValidTarget())
			{
				if (target == NULL)
					target = m_stOrbwalk.HeroList[i];

				if (m_stOrbwalk.HeroList[i]->GetCurrentHealth() < target->GetCurrentHealth())
				{
					target = m_stOrbwalk.HeroList[i];
				}
			}
		}
	
	}


	if (Engine::CanAttack() && target!= NULL)
	{
		Engine::AttackTo(&target->GetPos(), target);
		m_stOrbwalk.LastAATick = Engine::GetGameTimeTickCount() - Engine::GetPing() / 100;
	}
	else if (Engine::CanMove(90.0f))
	{
		Engine::IssueMove(&Engine::GetMouseWorldPosition());
	}


}



//lasthit
void COrbwalker::AttackLasthitTarget()
{
	CObject* lasthitTarget = NULL;
	for (size_t i = 0; i < ObjectManager->pMaxObjects; i++)
	{

				if (ObjectManager->Objects[i]->IsMinion())
				{
					if (ObjectManager->Objects[i]->IsValidTarget())
					{
						if (ObjectManager->Objects[i]->IsLasthitable())  //checks if lasthitable, calculates also the missileDMG | missileDMG is 0, if target is NULL
						{
							if (lasthitTarget == NULL)
								lasthitTarget = ObjectManager->Objects[i];

							
							if (ObjectManager->Objects[i]->GetCurrentHealth() < lasthitTarget->GetCurrentHealth())
								lasthitTarget = ObjectManager->Objects[i];
						}
					}
					
				}	
	}

	if (Engine::CanAttack() && lasthitTarget != NULL)
	{
		Engine::AttackTo(&lasthitTarget->GetPos(), lasthitTarget);
		m_stOrbwalk.LastAATick = Engine::GetGameTimeTickCount() - Engine::GetPing() / 100;
	}
	else if (Engine::CanMove(90.0f))
	{
		Engine::IssueMove(&Engine::GetMouseWorldPosition());
	}
}


//forced das angeklickte object als target
void COrbwalker::ForceTarget()
{
		short id = Engine::GetSelectedTargetID(); // hole ID von angeklickten ziel
		CObject* forcedTarget = NULL;
		if (id) //wenn ID nicht NULL ist
		{
			forcedTarget = Engine::GetObjectByID(id);
		}

		if (forcedTarget && forcedTarget->IsHero()) //wenn forcedTarget != NULL
		{
			m_stOrbwalk.forceTarget = true;
			m_stOrbwalk.cforcedTarget = forcedTarget;
		}
		else
		{
			m_stOrbwalk.forceTarget = false;
			m_stOrbwalk.cforcedTarget = NULL;
		}
}

//reseted das forced target wenn es außerhalb der AA range ist oder invalid ist
void COrbwalker::CheckForceTargetDistance()
{
	if (m_stOrbwalk.cforcedTarget != NULL)
	{
		if (m_stOrbwalk.cforcedTarget->GetDistToMe(LocalPlayer) > LocalPlayer->GetTrueAttackRange() || m_stOrbwalk.cforcedTarget->GetCurrentHealth() < 0.f)
		{
			m_stOrbwalk.cforcedTarget = NULL;
			m_stOrbwalk.forceTarget = false;
		}
	}
}


void COrbwalker::AttackClearTarget()
{
	for (size_t i = 0; i < ObjectManager->pMaxObjects; i++)
	{
		CObject* target = Engine::GetObjectByID(i);
		if (target->IsMinion() && Engine::IsInObjManager(target) || target->IsObjective() && Engine::IsInObjManager(target)) //wenn target minion oder objective
		{
			if (target->GetTeam() == 300 && target->GetCurrentHealth() > 1.f || target->IsEnemyTo(LocalPlayer) && Engine::IsInObjManager(target)) //wenn target neutral und leben größer als 1 ODER target ist gegnerisches team...
			{
				if (target->IsObjective() && Engine::CanAttack() && target->IsValidTarget() && Engine::IsInObjManager(target)) //wenn objective in range und nix lasthitbar ist
				{
					Engine::AttackTo(&target->GetPos(), target);
					m_stOrbwalk.LastAATick = Engine::GetGameTimeTickCount() - Engine::GetPing() / 100 + 25;
				}
				else if (target->IsAlive() && target->IsInRange() && target->IsTargetable() && target->IsVisible() && Engine::CanAttack()) //wenn kein objective in range, attacke creeps
				{
					if (Engine::IsInObjManager(target))
						Engine::AttackTo(&target->GetPos(), target);
					m_stOrbwalk.LastAATick = Engine::GetGameTimeTickCount() - Engine::GetPing() / 100 + 25;
				}
			}
		}
	}
	if (Engine::CanMove(100.f))
	{
		Engine::IssueMove(&Engine::GetMouseWorldPosition());
	}
}

void LoadCore()
{
	while (Engine::GetGameTime() < 1.0f) {
		Sleep(1);
	}
	ObjectManager = Engine::GetObjectManager(); //ObjectManager deklarieren

//Base Addres + LocalPlayer
	BaseAddress = (DWORD)GetModuleHandle(NULL);
	LocalPlayer = Engine::GetLocalObject();

	//League functions deklaration
	Engine::SetFunctions(); //deklariere functions
	//orbwalker call
	for (size_t i = 0; i < ObjectManager->pMaxObjects; i++)
	{
		if (ObjectManager->Objects[i]->IsHero())
		{
			if (ObjectManager->Objects[i]->IsEnemyTo(LocalPlayer))
				m_stOrbwalk.HeroList.push_back(ObjectManager->Objects[i]);
		}
	}

	for (size_t i = 0; i < ObjectManager->pMaxObjects; i++)
	{
		if (ObjectManager->Objects[i]->IsTurret() && ObjectManager->Objects[i]->IsEnemyTo(LocalPlayer) || ObjectManager->Objects[i]->IsNexus() && ObjectManager->Objects[i]->IsEnemyTo(LocalPlayer) || ObjectManager->Objects[i]->IsInhibitor() && ObjectManager->Objects[i]->IsEnemyTo(LocalPlayer))
		{
			m_stOrbwalk.TurretList.push_back(ObjectManager->Objects[i]);
		}
	}

	Engine::PushNexus();

	//COrbwalker::Orbwalk();
}
bool orbwalk = true;
void __fastcall Callbacks()
{
	LoadCore();

	while (true && Engine::GetLocalObject() != NULL && !Engine::GameHasEnded())
	{
		if (GetKeyState(VK_F10))
		{
			if (orbwalk == true)
			{
				orbwalk == false;
			}	
			else if (orbwalk == false)
			{
				orbwalk == true;
			}
				
		}

		

		if (GetKeyState(VK_F11) && orbwalk == true)
		{
			m_stOrbwalk.HeroList.clear();
			for (size_t i = 0; i < ObjectManager->pMaxObjects; i++)
			{
				if (ObjectManager->Objects[i]->IsHero() && ObjectManager->Objects[i]->IsEnemyTo(LocalPlayer))
				{
					m_stOrbwalk.HeroList.push_back(ObjectManager->Objects[i]);
				}
			}
		}

		if (GetKeyState(VK_LBUTTON) && orbwalk == true)
			COrbwalker::ForceTarget();

		if (GetAsyncKeyState(VK_SPACE) && orbwalk == true)
		{
			if (GetAsyncKeyState(VK_LBUTTON) && orbwalk == true) //force target
				COrbwalker::ForceTarget();

			COrbwalker::CheckForceTargetDistance(); //überprüfe ob forceTarget noch gültig
			COrbwalker::AttackLowestHPTarget();
			Sleep(50);
		}

		if (GetAsyncKeyState(0x58) && orbwalk == true)
		{
			if (GetKeyState(VK_LBUTTON) && orbwalk == true)
				COrbwalker::ForceTarget();

			COrbwalker::CheckForceTargetDistance();
			COrbwalker::AttackLasthitTarget();
			Sleep(50);
		}

		if (GetAsyncKeyState(0x56) && orbwalk == true)
		{
			if (GetKeyState(VK_LBUTTON) && orbwalk == true)
				COrbwalker::ForceTarget();

			COrbwalker::CheckForceTargetDistance();
			COrbwalker::AttackClearTarget();
			Sleep(50);
		}
		
		
	}
}

BOOL APIENTRY DllMain(HMODULE Module, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: // Gets runned when injected
		//AllocConsole(); // Enables the console
		//freopen("CONIN$", "r", stdin); // Makes it possible to output to output to console with cout.
		//freopen("CONOUT$", "w", stdout);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Callbacks, Module, 0, 0); // Creates our thread #
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}