#pragma once
#include "stdafx.h"
#include "Vector.h"
#include "OffsetsManager.h"
#include "Object.h"
#include "GameFunctions.h"
#include "ObjectManager.h"
#include "Modules.h"
#include "Orbwalk.h"
#include "ChampionList.h"
#include "Xerath.h"
#include "d3dx9math.h"

#define me Engine::GetLocalObject();

class Engine {
public:


	static CObjectManager* GetObjectManager()
	{
		return (CObjectManager*)(*(DWORD*)(baseAddr + oObjManager));
	}
	

	static Vector GetMouseWorldPosition() {
		DWORD MousePtr = (DWORD)GetModuleHandle(NULL) + oHudInstance;
		auto aux1 = *(DWORD*)MousePtr;
		aux1 += 0x14;
		auto aux2 = *(DWORD*)aux1;
		aux2 += 0x1C;

		float X = *(float*)(aux2 + 0x0);
		float Y = *(float*)(aux2 + 0x4);
		float Z = *(float*)(aux2 + 0x8);

		return Vector{ X, Y, Z };
	}

	static bool IsInObjManager(CObject* objectToCheck)
	{
		for (size_t i = 0; i < ObjectManager->pMaxObjects; i++)
		{
			CObject* object = GetObjectByID(i);
			if (objectToCheck == object && objectToCheck!=nullptr)
			{
				return true;
			}
		}
	}
	
	


	static void PushNexus()
	{
		for (size_t i = 0; i < ObjectManager->pMaxObjects; i++)
		{
			if (ObjectManager->Objects[i]->IsNexus() && ObjectManager->Objects[i]->IsAlive())
			{
				m_stOrbwalk.NexusList.push_back(ObjectManager->Objects[i]);
			}
		}
	}

	static bool GameHasEnded()
	{
		return !m_stOrbwalk.NexusList[0]->IsAlive() || !m_stOrbwalk.NexusList[1]->IsAlive();
	}

	static CObject* GetLocalObject() {
		auto retaddr = *(DWORD*)((DWORD)GetModuleHandle(NULL) + oLocalPlayer);
		if (retaddr == NULL)
			return NULL;

		return (CObject*)retaddr;
	}

	static float GetGameTime() {
		return *(float*)(baseAddr + oGameTime);
	}

	static int GetPing() {
		static DWORD Base = (DWORD)GetModuleHandle(NULL);
		return Functions.GetPing(*(void**)(Base + oNetClient));
	}

	static bool CanMove(float extraWindup)
	{
		//return Engine::GetGGameTIckCount() + Engine::GetPing() / 100 >= LastAATick + Functions.GetAttackCastDelay(Engine::GetLocalObject()) * 1000 + extraWindup;
		return Engine::GetGameTimeTickCount() + Engine::GetPing() / 100 >= m_stOrbwalk.LastAATick + Functions.GetAttackCastDelay(Engine::GetLocalObject()) * 1000 + extraWindup;
	}

	//CanAttack() gibt true zurück, wenn mein Auto Attack NICHT auf "Cooldown" ist, und ich attacken kann/darf
	static bool CanAttack()
	{
		//return Engine::GetGGameTIckCount() + Engine::GetPing() / 100 >= LastAATick + Functions.GetAttackDelay(Engine::GetLocalObject()) * 1000;
		return Engine::GetGameTimeTickCount() + Engine::GetPing() /100>= m_stOrbwalk.LastAATick + Functions.GetAttackDelay(Engine::GetLocalObject()) *1000 ;
	}

	static int GetGameTimeTickCount()
	{
		return (int)(Engine::GetGameTime() * 1000);
	}

	//returns true if the given 2D Vector has the same coordinates as an object in the HeroList
	static bool HasCoords(D3DXVECTOR2 W2S_buffer)
	{
		for (size_t i = 0; i < m_stOrbwalk.HeroList.size(); i++)
		{
			CObject* target = Engine::GetObjectByID(i); //get target by ID
			D3DXVECTOR2 buffer; //buffer for target pos
			Functions.WorldToScreen(&target->GetPos(), &buffer); //convert targets pos to a vector2

			if (W2S_buffer.x == buffer.x && W2S_buffer.y == buffer.y) //if an object has the same coords as my orb target, return true;
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	/*
	static void IssueAttack(CObject* target)
	{
		
		Vector targetPos = target->GetPos();
		D3DXVECTOR2 W2S_buffer;
		
		

		Functions.WorldToScreen(&targetPos, &W2S_buffer);
		Functions.WorldToScreen(&Engine::GetMouseWorldPosition(), &m_stOrbwalk.previousMousePos);
			
		if (W2S_buffer.x != 0 && W2S_buffer.y != 0)
		{
			//calc resolution to get orper coordinates
			double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
			double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
			double fx = W2S_buffer.x * (65535.0f / fScreenWidth);
			double fy = W2S_buffer.y * (65535.0f / fScreenHeight);


			//send input
			INPUT  Input = { 0 }; //input buffer
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
			Input.mi.dx = fx;
			Input.mi.dy = fy;
			SendInput(1, &Input, sizeof(INPUT));
			::ZeroMemory(&Input, sizeof(INPUT));
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
			::SendInput(1, &Input, sizeof(INPUT));
			::ZeroMemory(&Input, sizeof(INPUT));
			Input.type = INPUT_MOUSE;
			Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
			::ZeroMemory(&Input, sizeof(INPUT));
			ZeroMemory(&W2S_buffer, sizeof(D3DXVECTOR2));
			Sleep(3);
			if (m_stOrbwalk.previousMousePos.x != 0 && m_stOrbwalk.previousMousePos.y != 0)
				ResetMouse();
		}
	}
	*/

	static void ResetMouse()
	{
		//RESET MOUSE
		double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;
		double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;
		double fx = m_stOrbwalk.previousMousePos.x * (65535.0f / fScreenWidth);
		double fy = m_stOrbwalk.previousMousePos.y * (65535.0f / fScreenHeight);
		INPUT  Input = { 0 };
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_VIRTUALDESK | MOUSEEVENTF_ABSOLUTE;
		Input.mi.dx = fx;
		Input.mi.dy = fy;
		SendInput(1, &Input, sizeof(INPUT));
		::ZeroMemory(&Input, sizeof(INPUT));
		ZeroMemory(&m_stOrbwalk.previousMousePos, sizeof(D3DXVECTOR2));
	}

	/*
	static void IssueMove()
	{
		INPUT    Input = { 0 };
		// left down 
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
		::SendInput(1, &Input, sizeof(INPUT));

		// left up
		::ZeroMemory(&Input, sizeof(INPUT));
		Input.type = INPUT_MOUSE;
		Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
		::SendInput(1, &Input, sizeof(INPUT));


		//set random delay between clicks
		
		int delay = rand() % 20 + 15;
		Sleep(delay);
		
	}
	*/

	static bool what(DWORD pobject, int a2)
	{
		int v5;
		int v6;
		int v12;

		v12 = (pobject + 0x5c);
		v5 = pobject + 0x54;
		v6 = (v5);
		v12 ^= ~v6;
		return (v12 & a2) != 0;
	}

	static bool IsHero(DWORD pobject)
	{
		return pobject && what(pobject, 4096);
	}

	/*
	static void IssueAttack(CObject* target)
	{
		DWORD retInstruction = (DWORD)GetModuleHandle(NULL) + retnAddress; //retn instruction
		DWORD functionToCall = (DWORD)GetModuleHandle(NULL) + oIssueOrder;//IssueOrder
		Vector* orbTarget = &target->GetPos();
		void* This = Engine::GetLocalObject(); //this

		if (target != NULL && Engine::IsInObjManager(target))
		{
			__asm {
				push retAddress; //address of our function
				mov ecx, This; //If the function is a __thiscall don't forget to set ECX
				push 0
					push 0
					push 1
					push target
					push orbTarget
					push 3
					push retInstruction; //Set the return address to an address of a return instruction	
				jmp functionToCall; //Jump to league function
				sub retAddress, 22;
			retAddress:
			}
		}
	}
	*/

	static void AttackTo(Vector* pos, CObject* Target)
	{

		DWORD SpoofAddress = (DWORD)GetModuleHandle(NULL) + retnAddress; //retn instruction
		DWORD IssueOrderAddr = (DWORD)GetModuleHandle(NULL) + oIssueOrder;//IssueOrder
		void* LocalPlayer = Engine::GetLocalObject();
		CObject* AttackTo = Target;

		__asm
		{
			push retnHere
			mov ecx, LocalPlayer
			push 0
			push 0
			push 0
			push AttackTo
			push pos
			push 3
			push SpoofAddress
			jmp IssueOrderAddr
			sub retnHere, 22
			retnHere :
		}
	}

	
	static void IssueMove(Vector* pos)
	{
		//Functions.IssueOrder(GetLocalObject(), 2, pos, NULL, false, false, false);

		DWORD SpoofAddress = (DWORD)GetModuleHandle(NULL) + retnAddress; //retn instruction
		DWORD IssueOrderAddr = (DWORD)GetModuleHandle(NULL) + oIssueOrder;//IssueOrder
		void* LocalPlayer = Engine::GetLocalObject();

		__asm
		{
			push retnHere
			mov ecx, LocalPlayer
			push 0
			push 0
			push 0
			push 0
			push pos
			push 2
			push SpoofAddress
			jmp IssueOrderAddr
			sub retnHere, 22
			retnHere :
		}
	}

	static void SetZoom(float Value)
	{
		DWORD retInstruction = (DWORD)GetModuleHandle(NULL) + retnAddress; //retn instruction
		static DWORD Base = (DWORD)GetModuleHandle(NULL);
		static DWORD ZoomClass = *(DWORD*)(Base + oZoomClass);
		DWORD Address = *(float*)(ZoomClass + 0x24);

		__asm
		{
			push retAddress
		
			push retInstruction
			jmp ZoomClass
			retAddress:
		}
	}


	
	static short GetSelectedTargetID() {
		auto hudmgr = *(DWORD*)(baseAddr + oHudInstance);
		auto hud = *(DWORD*)(hudmgr + 0x30);
		auto retaddr = *(short*)(hud + 0x18);

		if (retaddr == NULL)
			return NULL;
		return retaddr;
	}

	static CObject* GetObjectByID(int ID)
	{
		if (ObjectManager && ID >= 0 && ID <= ObjectManager->pMaxObjects) {
			return ObjectManager->Objects[ID];
		}
		return NULL;
	}
	
	static void SetFunctions()
	{
		Functions.IsHero = (Typedefs::fnIsHero) (BaseAddress + oIsHero);
		Functions.IsMinion = (Typedefs::fnIsMinion)(BaseAddress + oIsMinion);
		Functions.IsTurret = (Typedefs::fnIsTurret)(BaseAddress + oIsTurret);
		Functions.IsBaron = (Typedefs::fnIsBaron)(BaseAddress + oIsBaron);
		Functions.IsDragon = (Typedefs::fnIsDragon)(BaseAddress + oIsDragon);
		Functions.IsInhib = (Typedefs::fnIsInhib)(BaseAddress + oIsInhib);
		Functions.IsNexus = (Typedefs::fnIsNexus)(BaseAddress + oIsNexus);
		Functions.IsTargetable = (Typedefs::fnIsTargetable) (BaseAddress + oIsTargetable);
		Functions.IsVisible = (Typedefs::fnIsVisible(BaseAddress + oObjVisibility));
		Functions.GetAttackCastDelay = (Typedefs::fnGetAttackCastDelay)(BaseAddress + oObjAttackCastDelay);
		Functions.GetAttackDelay = (Typedefs::fnGetAttackDelay)(BaseAddress + oObjAttackDelay);
		Functions.WorldToScreen = (Typedefs::fnWorldToScreen)(BaseAddress + oWorldToScreen);
		Functions.GetPing = (Typedefs::fnGetPing) (BaseAddress + oGetPing);
	}
};