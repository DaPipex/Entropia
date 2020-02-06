#pragma once
#include "pch.h"
#include <Windows.h>
#include "stdafx.h"
#include "DebugConsole.h"
#include "Engine.h"
#include "ObjectManager.h"


Engine engine;
CFunctions Functions;
DWORD BaseAddress;
CObject* LocalPlayer;
CObjectManager* ObjectManager;

std::vector<CObject*> EnemiesInRange; // all enemies in range
std::vector<CObject*> TurretList;

bool OrbCanAttack;
bool OrbCanMove;

float LastAATick;







//CanMove() gibt true zurück, wenn mein Auto Attack auf "Cooldown" ist und ich laufen kann bzw muss.
bool CanMove(float extraWindup)
{

	if (GetTickCount() + Engine::GetPing() /2 >= LastAATick + Functions.GetAttackCastDelay(Engine::GetLocalObject()) * 1000 + extraWindup)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//CanAttack() gibt true zurück, wenn mein Auto Attack NICHT auf "Cooldown" ist, und ich attacken kann/darf
bool CanAttack()
{
	if (GetTickCount() + Engine::GetPing() /2 +25 >= LastAATick + Functions.GetAttackDelay(Engine::GetLocalObject()) * 1000)
	{
		return true;
	}
	return false;
}


void pushStaticObjects()
{
	ObjectManager = Engine::GetObjectManager(); //ObjectManager deklarieren

	for (size_t i = 0; i < ObjectManager->pMaxObjects; i++)
	{
		if (ObjectManager->Objects[i]->IsTurret() && ObjectManager->Objects[i]->IsTargetable() && ObjectManager->Objects[i]->IsEnemyTo(LocalPlayer) )
		{
			TurretList.push_back(ObjectManager->Objects[i]); //push all Turrets in TurretList Vector
		}
	}
}





void Orbwalk()
{
	

	

	CObject* bestTarget = nullptr;
	CObject* minionToLasthit = nullptr;


	Vector w2sPosCHAMPION;
	Vector w2sPosMINION;
	POINT w2sMousePos;
	int w2sMousePosX;
	int w2sMousePosY;



	while (true)
	{
		
		
		EnemiesInRange.clear();



		//ORBWALER: WAVECLAER
		/*
		if (GetAsyncKeyState(0x56))
		{
			for (size_t i = 0; i < TurretList.size(); i++)
			{
				if (TurretList[i]->GetDistToMe(LocalPlayer) < LocalPlayer->GetTrueAttackRange())
				{
					bestTarget = TurretList[i]; //<	setze Turret[i] als aktuelles orbwalker target
					break;
				}
				
			}

			if(!bestTarget->IsTurret()) //wenn kein turret gefunden wurde..



				bestTarget = nullptr; //setze bei jedem durchgang bestTarget zurück

				for (size_t i = 0; i < ObjectManager->pMaxObjects; i++)
				{

					if (ObjectManager->Objects[i]->IsMinion() && ObjectManager->Objects[i]->IsEnemyTo(LocalPlayer) && ObjectManager->Objects[i]->IsAlive() && ObjectManager->Objects[i]->IsTargetable() && ObjectManager->Objects[i]->GetDistToMe(LocalPlayer) < LocalPlayer->GetTrueAttackRange())
					{
						LasthitableMinion.push_back(ObjectManager->Objects[i]);

					}
				}

				if (LasthitableMinion.size() > 0) //wenn nur ein objekt gefunden wird, ist bestTarget das 0. Objekt
				{
					if (bestTarget == nullptr)
					{
						bestTarget = LasthitableMinion[0];
					}
				}


				if (LasthitableMinion.size() > 1)
				{
					for (size_t i = 0; i < LasthitableMinion.size(); i++)
					{

						if (LasthitableMinion[i]->GetCurrentHealth() <= LocalPlayer->GetTotalAD() && LasthitableMinion[i]->GetCurrentHealth() > 0.f) // Wenn minion lasthitbar, attacke minion...
						{
							bestTarget = LasthitableMinion[i];
						}
						else if (LasthitableMinion.size() > 1 && LasthitableMinion[i]->GetCurrentHealth() < bestTarget->GetCurrentHealth() && LasthitableMinion[0]->GetCurrentHealth() > 0.f) //wenn nicht, schaue ob minion[i] weniger leben hat als aktuelles Target
						{
							bestTarget = LasthitableMinion[i];
						}
						else if (1 == LasthitableMinion.size() && LasthitableMinion[0]->GetCurrentHealth() > 0.f) //wenn nicht, attacke objekt 0
						{
							bestTarget = LasthitableMinion[0];
						}
					}
				}

			


			// ORBWALKING
			if (CanAttack() && bestTarget != nullptr)
			{
				if (bestTarget->GetDistToMe(LocalPlayer) < LocalPlayer->GetTrueAttackRange()  && bestTarget->GetCurrentHealth() > 0.f  )	// Wenn Object innerhalb meiner Auto Attack Reichweite...
				{


					Functions.WorldToScreen(&bestTarget->GetPos(), &w2sPos); //target pos in W2S Konvertiert		

					GetCursorPos(&w2sMousePos);
					w2sMousePosX = w2sMousePos.x;
					w2sMousePosY = w2sMousePos.y;

					SetCursorPos(w2sPos.X, w2sPos.Y); // move mouse zum gegner

					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					Sleep(3);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

					LastAATick = GetTickCount() + Engine::GetPing() / 2;

					Sleep(5);
					SetCursorPos(w2sMousePosX, w2sMousePosY);


				}

			}


			if (CanMove(90))
			{

				int delay = rand() % 80 + 120;

				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
				Sleep(3);
				mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
				Sleep(delay);
			}


		}
		*/
	
	if (GetAsyncKeyState(0x58))
	{
		
		for (size_t i = 0; i < ObjectManager->pMaxObjects; i++)
		{
		

			if (ObjectManager->Objects[i]->IsMinion() && ObjectManager->Objects[i]->IsEnemyTo(LocalPlayer) && ObjectManager->Objects[i]->GetDistToMe(LocalPlayer) < LocalPlayer->GetTrueAttackRange() && ObjectManager->Objects[i]->GetCurrentHealth() > 0.f)
				if (ObjectManager->Objects[i]->GetCurrentHealth() <= LocalPlayer->GetTotalAD())
				{
					minionToLasthit = ObjectManager->Objects[i];
				}
		
				
		}


		if (CanAttack() && minionToLasthit != nullptr)
		{
			if (minionToLasthit->GetCurrentHealth() > 0.f && minionToLasthit->IsMinion() && minionToLasthit->IsAlive())	// Wenn Object innerhalb meiner Auto Attack Reichweite...
			{


				Functions.WorldToScreen(&minionToLasthit->GetPos(), &w2sPosMINION); //target pos in W2S Konvertiert		

				GetCursorPos(&w2sMousePos);
				w2sMousePosX = w2sMousePos.x;
				w2sMousePosY = w2sMousePos.y;

				SetCursorPos(w2sPosMINION.X, w2sPosMINION.Y); // move mouse zum gegner

				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				Sleep(3);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

				LastAATick = GetTickCount() + Engine::GetPing() / 2;

				Sleep(5);
				SetCursorPos(w2sMousePosX, w2sMousePosY);


			}

		}


		if (CanMove(90))
		{

			int delay = rand() % 80 + 120;

			mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
			Sleep(3);
			mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
			Sleep(delay);
		}


	}




		
		//ORBWALKER: JUNGLE CLEAR
		/*
		if (GetAsyncKeyState(0x59))
		{
			bestTarget = nullptr; //setze bei jedem durchgang bestTarget zurück

			for (size_t i = 0; i < ObjectManager->pMaxObjects; i++)
			{

				if (ObjectManager->Objects[i]->IsTroyEnt() && ObjectManager->Objects[i]->IsEnemyTo(LocalPlayer) && ObjectManager->Objects[i]->IsAlive() && ObjectManager->Objects[i]->IsTargetable() && ObjectManager->Objects[i]->GetDistToMe(LocalPlayer) < LocalPlayer->GetTrueAttackRange())
				{
					jungleClearList.push_back(ObjectManager->Objects[i]);

				}
			}

			if (jungleClearList.size() > 0) //wenn nur ein objekt gefunden wird, ist bestTarget das 0. Objekt
			{
				if (bestTarget == nullptr)
				{
					bestTarget = jungleClearList[0];
				}
			}


			if (jungleClearList.size() > 1)
			{
				for (size_t i = 0; i < jungleClearList.size(); i++)
				{

					if (jungleClearList[i]->GetCurrentHealth() <= LocalPlayer->GetTotalAD() && LasthitableMinion[i]->GetCurrentHealth() > 0.f) // Wenn minion lasthitbar, attacke minion...
					{
						bestTarget = jungleClearList[i];
					}
					else if (jungleClearList.size() > 1 && jungleClearList[i]->GetCurrentHealth() < bestTarget->GetCurrentHealth() && jungleClearList[0]->GetCurrentHealth() > 0.f) //wenn nicht, schaue ob minion[i] weniger leben hat als aktuelles Target
					{
						bestTarget = jungleClearList[i];
					}
					else if (1 == jungleClearList.size() && jungleClearList[0]->GetCurrentHealth() > 0.f) //wenn nicht, attacke objekt 0
					{
						bestTarget = jungleClearList[0];
					}
				}
			}




			// ORBWALKING
			if (CanAttack() && bestTarget != nullptr)
			{
				if (bestTarget->GetDistToMe(LocalPlayer) < LocalPlayer->GetTrueAttackRange() && bestTarget->IsTroyEnt() && bestTarget->GetCurrentHealth() > 0.f )	// Wenn Object innerhalb meiner Auto Attack Reichweite...
				{


					Functions.WorldToScreen(&bestTarget->GetPos(), &w2sPos); //target pos in W2S Konvertiert		

					GetCursorPos(&w2sMousePos);
					w2sMousePosX = w2sMousePos.x;
					w2sMousePosY = w2sMousePos.y;

					SetCursorPos(w2sPos.X, w2sPos.Y); // move mouse zum gegner

					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					Sleep(3);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

					LastAATick = GetTickCount() + Engine::GetPing() / 2;

					Sleep(5);
					SetCursorPos(w2sMousePosX, w2sMousePosY);


				}

			}


			if (CanMove(90))
			{

				int delay = rand() % 80 + 120;

				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
				Sleep(3);
				mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
				Sleep(delay);
			}


		}
		*/

		//ORBWALKING : CHAMPIONS
		if (GetAsyncKeyState(VK_SPACE))
		{
			

			for (size_t i = 0; i < ObjectManager->pMaxObjects; i++)
			{
				if (ObjectManager->Objects[i]->IsHero() && ObjectManager->Objects[i]->IsEnemyTo(LocalPlayer) && ObjectManager->Objects[i]->GetDistToMe(LocalPlayer) < LocalPlayer->GetTrueAttackRange() && ObjectManager->Objects[i]->IsAlive() && ObjectManager->Objects[i]->IsTargetable())
				{
					EnemiesInRange.push_back(ObjectManager->Objects[i]);
				}

			}

			if (EnemiesInRange.size() > 1)
			{
				for (size_t i = 1; i < EnemiesInRange.size(); i++)
				{
					if (EnemiesInRange[i]->GetCurrentHealth() < bestTarget->GetCurrentHealth() && EnemiesInRange[i]->IsHero() && EnemiesInRange[i]->GetCurrentHealth() > 0.f && EnemiesInRange[i]->IsAlive())
						
					{
						bestTarget = EnemiesInRange[i];
					}
				}


			}
			else if (EnemiesInRange.size() == 1 && EnemiesInRange[0]->GetCurrentHealth() > 0.f && EnemiesInRange[0]->IsHero() && EnemiesInRange[0]->IsAlive())
			{
				bestTarget = EnemiesInRange[0];
			}



			if (CanAttack() && bestTarget != nullptr)
			{
				if (bestTarget->GetDistToMe(LocalPlayer) < LocalPlayer->GetTrueAttackRange() && bestTarget->IsHero() && bestTarget->GetCurrentHealth() > 0.f )	// Wenn Object innerhalb meiner Auto Attack Reichweite...
				{


					Functions.WorldToScreen(&bestTarget->GetPos(), &w2sPosCHAMPION); //target pos in W2S Konvertiert		

					GetCursorPos(&w2sMousePos);
					w2sMousePosX = w2sMousePos.x;
					w2sMousePosY = w2sMousePos.y;

					SetCursorPos(w2sPosCHAMPION.X, w2sPosCHAMPION.Y); // move mouse zum gegner

					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					Sleep(3);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

					LastAATick = GetTickCount() + Engine::GetPing() / 2;

					Sleep(5);
					SetCursorPos(w2sMousePosX, w2sMousePosY);


				}

			}


			if (CanMove(90))
			{

				int delay = rand() % 80 + 120;

				mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
				Sleep(3);
				mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);//TEST
				Sleep(delay);
			}

		}


		}
		

		

	
}





		
		
		






	





	

	
	






void __stdcall Start() {
	
	

	//Base Addres + LocalPlayer
	BaseAddress = (DWORD)GetModuleHandle(NULL);
	LocalPlayer = Engine::GetLocalObject();
	
	//League functions deklaration
	Functions.IsHero = (Typedefs::fnIsHero) (BaseAddress + oIsHero);
	Functions.IsMinion = (Typedefs::fnIsMinion)(BaseAddress + oIsMinion);
	Functions.IsTroyEnt = (Typedefs::fnIsTroyEnt)(BaseAddress + oIsTroy);
	Functions.IsAlive = (Typedefs::fnIsAlive)(BaseAddress + oIsAlive);
	Functions.IsTurret = (Typedefs::fnIsTurret)(BaseAddress + oIsTurret);
	Functions.IsTargetable = (Typedefs::fnIsTargetable) (BaseAddress + oIsTargetable);

	Functions.GetAttackCastDelay = (Typedefs::fnGetAttackCastDelay)(BaseAddress + oObjAttackCastDelay);
	Functions.GetAttackDelay = (Typedefs::fnGetAttackDelay)(BaseAddress + oObjAttackDelay);
	Functions.WorldToScreen = (Typedefs::fnWorldToScreen)(BaseAddress + oWorldToScreen);
	Functions.GetPing = (Typedefs::fnGetPing) (BaseAddress + oGetPing);

	//start der methoden
	pushStaticObjects();
	Orbwalk();
	


}




BOOL APIENTRY DllMain(HMODULE Module, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Start, 0, 0, 0);
		return TRUE;

	}

	else if (ul_reason_for_call == DLL_PROCESS_DETACH) {
		return TRUE;
	}
	return FALSE;
}