#include "StdAfx.h"

extern "C" _declspec(dllexport) void FireTeam()
{
	DWORD OldProtect;
	if (VirtualProtect((LPVOID)0x401000, 3543191, PAGE_EXECUTE_READWRITE, &OldProtect))
	{
		_beginthread(&Functions::Thread, 0, NULL);
		_beginthread(&cPotion::Thread1, 0, NULL);
		_beginthread(&cPotion::Thread2, 0, NULL);

		Manager.Initialize();
		Optimize.Load();
		Maps.Load();
		Func.Hook((DWORD)&Functions::ReadCommonEx, 0x4027DE);
		Func.Hook((DWORD)&ProtocolCoreEx, 0x401D5C);
		Func.Hook((DWORD)&Functions::PChatProcEx, 0x414499);
		*(BYTE*)(0x41C70C) = MAX_SHOP;
		Func.Hook((DWORD)&Functions::CGTalkRequestRecv, 0x402AC7);
		Func.Hook((DWORD)&Functions::CGBuyRequestRecv, 0x4026B2);
		Func.Hook((DWORD)&Functions::ShopDataLoad, 0x401B5E);
		Func.Hook((DWORD)&Functions::gObjSetMonsterEx, 0x402AE0);
		Func.Hook((DWORD)&cFlood::Connect, 0x4013E8);
		Func.Hook((DWORD)&Functions::gObjAttackEx, 0x4026F3);
		Func.Hook((DWORD)&Functions::gObjLifeCheckEx, 0x402996);
		Func.Hook((DWORD)&Functions::gObjPlayerKillerEx, 0x402B71);
		Func.Hook((DWORD)&Functions::gObjInterfaceTimeCheckEx, 0x402A72);
		Func.Hook((DWORD)&Functions::gObjSecondProcEx, 0x401F46);
		Func.Hook((DWORD)&Functions::gObjCalCharacterEx, 0x4015AF);
		Func.Hook((DWORD)&Functions::gObjCloseSetEx, 0x401A28);
		Func.Hook((DWORD)&Functions::gObjDelEx, 0x401FFF);
		Func.Hook((DWORD)&Functions::gObjUserDieEx, 0x4019FB);
		Func.Hook((DWORD)&Functions::gObjInventoryMoveItemEx, 0x402095);
		Func.Hook((DWORD)&Functions::gObjLevelUpEx, 0x401771);
		Func.Hook((DWORD)&cDisplay::ViewPaint, 0x4027CA);
		Func.Hook((DWORD)&cDisplay::LogTextPaintProcEx, 0x4024AF);
		Func.Hook((DWORD)&cDisplay::LogTextAddEx, 0x4029AA);
		Func.Hook((DWORD)&Functions::GCWarePassSend, 0x4029C3);
		Func.Hook((DWORD)&Functions::gObjSetCharacterEx, 0x4026CB);
		Func.Hook((DWORD)&Functions::gObjMoveGateEx, 0x402810);
		//Func.Hook((DWORD)&Functions::GCDamageSend, 0x4025A4);
		Func.Hook((DWORD)&Functions::GCRefillSend, 0x401389);
		Func.Hook((DWORD)&Functions::GCManaSend, 0x4013B6);
		Func.Hook((DWORD)&BloodEvent::DropChaosGem, 0x401E06);
		Func.Hook((DWORD)&cDropping::gObjDrop, 0x401AC8);
		Func.Hook((DWORD)&Functions::CSPJoinIdPassRequestEx, 0x402865);
		Func.Hook((DWORD)&Functions::ItemGetDurabilityEx, 0x4019BF);
		Func.Hook((DWORD)&Functions::ItemSerialCreateRecvEx, 0x4017C6);
		Func.Hook((DWORD)&Functions::CGItemDropRequestEx, 0x4010FF);
		Func.Hook((DWORD)&Functions::GCItemDurSendEx, 0x401FA0);
		Func.Hook((DWORD)&Functions::CGUseItemRecvEx, 0x4012BC);
		Func.Hook((DWORD)&cSpeed::PMoveProcEx, 0x401DE3);
		Func.Hook((DWORD)&Functions::CGGuildRequestRecvEx, 0x402B17);
		Func.Hook((DWORD)&cParty::CGPartyRequestRecvEx, 0x40152D);
		Func.Hook((DWORD)&cExperience::ExperienceSend, 0x401CEE);
		Func.Hook((DWORD)&Functions::gObjTeleportMagicUseEx, 0x401C7B);
		Func.Hook((DWORD)&Functions::gObjViewportListCreateEx, 0x4020CC);
		Func.Hook((DWORD)&Functions::CGWarehouseUseEndEx, 0x401E60);
		Func.Hook((DWORD)&cPet::gObjMonsterCallKillEx, 0x4016E5);
		Func.SetNop(0x43291A + 5, 3);
		Func.HookJump(0x43291A, cDevilEvent::SendRanking);
		Func.Hook((DWORD)&Functions::CGSellRequestRecvEx, 0x401C35);
		Func.Hook((DWORD)&Functions::CGLiveClient, 0x4023F1);
		Func.Hook((DWORD)&Functions::CGPCharDelEx, 0x401802);
		//Func.Hook((DWORD)&cLicense::WinMainEx, 0x4023DD);
	}
	else
	{
		MessageBox(NULL, "Impossível iniciar o projeto!", "[ CMzone Plugin Edit ] - Fatal Erro", MB_OK | MB_ICONERROR);
	}
}