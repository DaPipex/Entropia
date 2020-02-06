#define retnAddress 0x16CE2F //  0x16B67F // 0x1694EF // 													 C3 8B 4C 24 10 B0


#define oNetClient 0x33DF260 // 0x33D3BC0 // 0x339CB34																							//

#define oChatClientPtr 0x2788FC8 /// 0x1B2EB70 // 0x1AF7C7C				MAY BE WRONG					 8B 35 ? ? ? ? 52 
#define oObjManager		0x2788EEC // 0x277D96C // 10.1 10.2????												 8B 0D ? ? ? ? E8 ? ? ? ? FF 77						//
#define oZoomClass 0x33D6FC4 // 0x33CBA4C// 0x339496C													 A3 ? ? ? ? 83 FA 10 72 32							//
#define oGameTime 0x33D7014 // 0x33CBA9C// 0x3394BF4													 F3 0F 11 05 ? ? ? ? 8B 49							//
#define oGameInfo  0x33D86F8 // 0x33CD130// 0x339A240													 A1 ? ? ? ? 83 78 08 02 0F 94 C0
#define oLocalPlayer 0x33DE098 // 0x33D2A90 // 0x339BC30												 A1 ?? ?? ?? ?? 85 C0 74 07 05 ?? ?? ?? ?? EB 02 33 C0 56  //
#define oHudInstance 0x1B3C858 // 0x1B312D8 // 0x1AFA418												 8B 0D ? ? ? ? 6A 00 8B 49 34 E8 ? ? ? ? B0         //
#define oRenderer 0x33FA288 //  0x33EE818 // 0x33B70B8													 8B 15 ? ? ? ? 83 EC 08 F3
#define oUnderMouseObject 0x2788F0C // 0x2DE6ACC // 0x2746ACC											 8B 0D ? ? ? ? 89 0D 
#define oD3DRenderer 0x33FC78C // 0x33F0D1C // 0x33B95C4												 A1 ? ? ? ? 33 D2 56 57 8B 7C 24 14					//
#define oGameVersion 0x4A9970 // 0x49D050 // 0x443184													 8B 44 24 04 BA ? ? ? ? 2B D0						//
// FUNCTIONS
#define oGetSpellSlotPtr 0x3FCCB0 // 10.1 10.2????????????????											 ????? 
#define oCastSpell 0x4F0A40 // 0x459860 //May be wrong //0x430C80										 83 EC 38 56 8B 74									//
#define oDrawCircle 0x473F60 // 0x468940 // 0x43FB20 //	MAY BE WRONG NO USE FOR ME 						 E8 ? ? ? ? 83 C4 1C 5F 5E 83 C4 20					//
#define oGetBasicAttack	0x1C1940 // 0x1BF9D0  // 0x1BCC60												 53 8B D9 B8 ? ? ? ? 8B 93							//
#define oObjAttackCastDelay 0x299BD0 // 0x2B0660 //0x2A9F00												 83 EC 0C 53 8B 5C 24 14 8B CB 56 57 8B 03 FF 90	// 
#define oObjAttackDelay 0x299CC0 // 0x2B0750 //0x2A9FF0													 8B 44 24 04 51 F3									//
#define oGetPing 0x319E50 // 0x312DA0	//0x309DA0														 E8 ? ? ? ? 8B E8 3B 6B								//
#define oGetSpellState 0x45AE10 // 0x44F6B0// 0x428290													 83 EC 14 8B 44 24 1C 55							//	
#define oIsTargetable 0x1D3A60 // 0x1D1DE0 // 0x1CF020													 56 8B F1 E8 ? ? ? ? 84 C0 74 2E					//
#define oIsAlive 0x195060 // 0x192B50   //0x190AC0 														 56 8B F1 8B 06 8B 80 ? ? ? ? FF D0 84 C0 74 19		//
#define oIsBaron  0x16E450 // 0x16CBB0  // 	0x16AA10													 56 E8 ? ? ? ? 68 ? ? ? ? 8B 30						//	
#define oIsTurret 0x1D9600 // 0x1D7A00//0x1D5AC0  														 E8 ? ? ? ? 83 C4 04 84 C0 74 09 5F					//
#define oIsInhib 0x1D9290 // 0x1D7690 //0x1D5750														 E8 ? ? ? ? 83 C4 04 84 C0 74 38					//
#define oIsHero 0x1D9410 // 0x1D7810   //0x1D58D0														 E8 ? ? ? ? 83 C4 04 84 C0 75 22 8B 8D				//
#define oIsMinion 0x1D9450 // 0x1D7850 //0x1D5910													 	 E8 ? ? ? ? 83 C4 04 84 C0 74 4A 8B 45				//
#define oIsDragon 0x16CDC0 // 0x16B610  // 0x169480 													 83 EC 10 A1 ? ? ? ? 33 C4 89 44 24 0C 56 E8		//
#define oIsMissile 0x1D9470 // 0x1D7870 //0x1D5930												   		 E8 ? ? ? ? 83 C4 04 84 C0 74 1C FF					//
#define oIsNexus 0x1D9390 // 0x1D7790	//0x1D5850														 E8 ? ? ? ? 83 C4 04 84 C0 75 05 5F					//
#define oIsNotWall 0x804270 // 0x7FB280 //0x7C70F0														 E8 ? ? ? ? 33 C9 83 C4 0C 84						//
#define oIsTroy 0x1D7B30     // 10.1// 10.2???????
#define oIssueOrder 0x16E500 //0x16CC60 //0x16AAC0 												   	     81 EC ? ? ? ? 56 57 8B F9 C7						//
#define oPrintChat 0x4D6E00 //0x4C9E90  // 0x49FD40													     83 EC 44 A1 ? ? ? ? 33 C4 89 44 24 40 53 8B 5C 24 50 56 
#define oWorldToScreen 0x8842F0 //0x87B040 //0x846F10 												     83 EC 10 56 E8 ? ? ? ? 8B 08						//

//CObject


#define oObjIndex 0x20 //NOT VERIFIED
#define oObjTeam 0x4C //NOT VERIFIED
#define oObjName 0x6C // 10.2 no change
#define oObjNetworkID 0xCC //NOT VERIFIED
#define oObjPos 0x1D8// 10.2 
#define oObjVisibility 0x450 //NOT VERIFIED
#define oObjHealth 0xF90  // 10.2 no change
#define oObjMaxHealth 0xFA0 // 10.2 no change
#define oObjLethality 0x137C //NOT VERIFIED
#define oObjBonusAtk 0x1410  //NOT VERIFIED
#define oObjBaseAtk 0x1438 // 10.2 no change
#define oObjArmor 0x1460 // 10.2 no change
#define oObjBonusArmor 0x1464 // 10.2 no change
#define oObjMagicRes 0x1468 // 10.2 no change
#define oObjBonusMagicRes 0x146C // 10.2 no change
#define oObjMoveSpeed 0x1A50  // 10.2
#define oObjAttackRange 0x1480  // 10.2 no change
#define oObjBuffMgr 0x2300 //NOT VERIFIED
#define oObjSpellBook 0x2AB0 //  10.2 no change
#define oObjChampionName 0x3544 // 10.2
#define oObjLevel 0x4D5C // 10.2

#define O_AIMGR_TARGETPOS 0x10  //NOT VERIFIED
#define O_AIMGR_ISMOVING 0x198 //NOT VERIFIED
#define O_AIMGR_ISDASHING 0x1E8 //NOT VERIFIED
#define O_AIMGR_NAVBEGIN 0x1BC //NOT VERIFIED
#define O_AIMGR_NAVEND 0x1C0 //NOT VERIFIED
#define O_AIMGR_HASNAVPATH 0x19C //NOT VERIFIED
#define O_AIMGR_CURRENTPOS 0x2BC //NOT VERIFIED
#define O_AIMGR_VELOCITY 0x2C0 //NOT VERIFIED


#define missileStartPos 0x78 //10.1
#define missileEndPos 0x84 //10.1

#define oObjSourceIndex 0x290 // 10.1


#define oMissileSpellInfo 0x230 // 10.1
#define oMissileSourceIndex 0x290 //10.1
#define oMissileTargetIndex 0x2DC //10.1
#define oMissileStartPos 0x2A8 // 10.1
#define oMissileEndPos 0x2B4 // 10.1

//Buff

#define O_BUFF_START_TIME 0x0C // 10.01
#define O_BUFF_END_TIME 0x10 // 10.01
#define O_BUFFMGR_TYPE 0x4 // 10.01
#define oBuffName 0x8 // 10.01
#define oFlBuffCount 0x130 // 10.01
#define oIntBuffCount 0x74 // 10.01
#define OFFSET_BUFF_COUNT_ALT 0x24 // 10.01
#define OFFSET_BUFF_COUNT_ALT2 0x20 // 10.01