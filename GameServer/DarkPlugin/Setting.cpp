#include "StdAfx.h"

bool cSetting::Load()
{
	*(unsigned int*)(0x48A098 + 1) = GetPrivateProfileInt("SERVER", "Porta UDP", 60006, "./Data/Settings.txt");

	*(unsigned int*)(0x459BA2 + 3) = GetPrivateProfileInt("SERVER", "Level máximo", 1000, "./Data/Settings.txt");
	*(unsigned int*)(0x462A33 + 2) = GetPrivateProfileInt("SERVER", "Level máximo", 1000, "./Data/Settings.txt");
	*(unsigned int*)(0x496D93 + 1) = GetPrivateProfileInt("SERVER", "Level máximo", 1000, "./Data/Settings.txt");
	*(unsigned int*)(0x48A2A7 + 3) = GetPrivateProfileInt("SERVER", "Level máximo", 1000, "./Data/Settings.txt");

	*(float*)(0x5090A0) = GetPrivateProfileInt("SERVER", "Zen Divisor", 0, "./Data/Settings.txt");

	*(unsigned int*)(0x5133E8) = GetPrivateProfileInt("SERVER", "Máximo de jogadores", 100, "./Data/Settings.txt");

	*(unsigned int*)(0x446C81 + 1) = GetPrivateProfileInt("SERVER", "Duração dos itens no chão", 120, "./Data/Settings.txt") * 1000;
	*(unsigned int*)(0x446DCA + 1) = GetPrivateProfileInt("SERVER", "Duração dos itens no chão", 120, "./Data/Settings.txt") * 1000;
	*(unsigned int*)(0x446F4F + 1) = GetPrivateProfileInt("SERVER", "Duração dos itens no chão", 120, "./Data/Settings.txt") * 1000;
	*(unsigned int*)(0x447148 + 1) = GetPrivateProfileInt("SERVER", "Duração dos itens no chão", 120, "./Data/Settings.txt") * 1000;

	*(unsigned long*)(0x422DA1 + 3) = GetPrivateProfileInt("SERVER", "Máximo de zen no baú", 2000000000, "./Data/Settings.txt");
	*(unsigned long*)(0x422E97 + 3) = GetPrivateProfileInt("SERVER", "Máximo de zen no baú", 2000000000, "./Data/Settings.txt");
	*(unsigned long*)(0x422DCD + 2) = GetPrivateProfileInt("SERVER", "Máximo de zen no baú", 2000000000, "./Data/Settings.txt");

	*(unsigned char*)(0x462B0E) = GetPrivateProfileInt("SERVER", "Pontos por level BK, SM, ELF", 5, "./Data/Settings.txt");
	*(unsigned char*)(0x462AF7) = GetPrivateProfileInt("SERVER", "Pontos por level MG", 7, "./Data/Settings.txt");

	*(unsigned char*)(0x47A069 + 3) = GetPrivateProfileInt("JÓIAS RATES", "Chance de sucesso da jewel of soul em itens sem luck", 75, "./Data/Settings.txt");
	*(unsigned char*)(0x479F8A + 3) = GetPrivateProfileInt("JÓIAS RATES", "Chance de sucesso da jewel of soul em itens com luck", 100, "./Data/Settings.txt");
	*(unsigned char*)(0x47A678 + 3) = GetPrivateProfileInt("JÓIAS RATES", "Chance de sucesso da jewel of life em itens", 75, "./Data/Settings.txt");

	*(unsigned char*)(0x44926D) = GetPrivateProfileInt("CHAOS MACHINE MIXES", "Chance de sucesso ao upar o item para + 10", 100, "./Data/Settings.txt");
	*(unsigned char*)(0x44927C) = GetPrivateProfileInt("CHAOS MACHINE MIXES", "Chance de sucesso ao upar o item para + 11", 100, "./Data/Settings.txt");
	*(unsigned char*)(0x44A27A) = GetPrivateProfileInt("CHAOS MACHINE MIXES", "Porcentagem ao criar asa level 1", 100, "./Data/Settings.txt");
	*(unsigned char*)(0x44A286) = GetPrivateProfileInt("CHAOS MACHINE MIXES", "Porcentagem ao criar asa level 2", 100, "./Data/Settings.txt");

	*(unsigned int*)(0x4583B0 + 1) = GetPrivateProfileInt("GREAT FORTITUDE", "Poder de vitalidade", 80, "./Data/Settings.txt");
	*(unsigned int*)(0x4583C4 + 1) = GetPrivateProfileInt("GREAT FORTITUDE", "Poder de energia", 50, "./Data/Settings.txt");
	*(unsigned int*)(0x4583E2 + 1) = GetPrivateProfileInt("GREAT FORTITUDE", "Duração", 200, "./Data/Settings.txt");

	*(unsigned char*)(0x458794 + 3) = GetPrivateProfileInt("MANA SHIELD", "Start", 6800, "./Data/Settings.txt");
	*(unsigned int*)(0x458779 + 1) = GetPrivateProfileInt("MANA SHIELD", "Poder de agilidade", 6800, "./Data/Settings.txt");
	*(unsigned int*)(0x45878D + 1) = GetPrivateProfileInt("MANA SHIELD", "Poder de energia", 6800, "./Data/Settings.txt");
	*(unsigned int*)(0x4587AC + 1) = GetPrivateProfileInt("MANA SHIELD", "Poder de energia", 6800, "./Data/Settings.txt");
	*(unsigned char*)(0x4587B3 + 2) = GetPrivateProfileInt("MANA SHIELD", "Duração", 30, "./Data/Settings.txt");

	*(unsigned int*)(0x480021) = GetPrivateProfileInt("PREÇO DAS JOIAS", "Bless", 9000000, "./Data/Settings.txt");
	*(unsigned int*)(0x480056) = GetPrivateProfileInt("PREÇO DAS JOIAS", "Chaos", 810000, "./Data/Settings.txt");
	*(unsigned int*)(0x48008B) = GetPrivateProfileInt("PREÇO DAS JOIAS", "Creation", 36000000, "./Data/Settings.txt");
	*(unsigned int*)(0x480071) = GetPrivateProfileInt("PREÇO DAS JOIAS", "Life", 45000000, "./Data/Settings.txt");
	*(unsigned int*)(0x48003B) = GetPrivateProfileInt("PREÇO DAS JOIAS", "Soul", 6000000, "./Data/Settings.txt");

	*(unsigned long*)(0x41ECCD) = GetPrivateProfileInt("EXPERIENCIA EM PARTY", "Diferença", 0, "./Data/Settings.txt");
	*(unsigned long*)(0x41EDB0) = GetPrivateProfileInt("EXPERIENCIA EM PARTY", "Diferença", 0, "./Data/Settings.txt");
	*(unsigned long*)(0x41EED8) = GetPrivateProfileInt("EXPERIENCIA EM PARTY", "Diferença", 0, "./Data/Settings.txt");

	*(unsigned long*)(0x467E3F) = GetPrivateProfileInt("EXPERIENCIA EM PARTY", "Rate com 2 jogadores", 0, "./Data/Settings.txt");
	*(unsigned long*)(0x467E06) = GetPrivateProfileInt("EXPERIENCIA EM PARTY", "Rate com 2 jogadores", 0, "./Data/Settings.txt") + 40;

	*(unsigned long*)(0x467E18) = GetPrivateProfileInt("EXPERIENCIA EM PARTY", "Rate com 3 jogadores", 0, "./Data/Settings.txt");
	*(unsigned long*)(0x467DE2) = GetPrivateProfileInt("EXPERIENCIA EM PARTY", "Rate com 3 jogadores", 0, "./Data/Settings.txt") + 50;

	*(unsigned long*)(0x467E27) = GetPrivateProfileInt("EXPERIENCIA EM PARTY", "Rate com 4 jogadores", 0, "./Data/Settings.txt");
	*(unsigned long*)(0x467DF1) = GetPrivateProfileInt("EXPERIENCIA EM PARTY", "Rate com 4 jogadores", 0, "./Data/Settings.txt") + 60;

	*(unsigned long*)(0x467E36) = GetPrivateProfileInt("EXPERIENCIA EM PARTY", "Rate com 5 jogadores", 0, "./Data/Settings.txt");
	*(unsigned long*)(0x467E00) = GetPrivateProfileInt("EXPERIENCIA EM PARTY", "Rate com 5 jogadores", 0, "./Data/Settings.txt") + 70;

	*(unsigned char*)(0x427E35 + 2) = GetPrivateProfileInt("POTIONS HP", "Porcentagem de recuperação para apple", 0, "./Data/Settings.txt");
	*(unsigned char*)(0x427E5E + 2) = GetPrivateProfileInt("POTIONS HP", "Porcentagem de recuperação para small", 0, "./Data/Settings.txt");
	*(unsigned char*)(0x427E87 + 2) = GetPrivateProfileInt("POTIONS HP", "Porcentagem de recuperação para medium", 0, "./Data/Settings.txt");
	*(unsigned char*)(0x427EB0 + 2) = GetPrivateProfileInt("POTIONS HP", "Porcentagem de recuperação para large", 0, "./Data/Settings.txt");

	*(unsigned char*)(0x428006 + 2) = GetPrivateProfileInt("POTIONS MANA", "Porcentagem de recuperação para small", 0, "./Data/Settings.txt");
	*(unsigned char*)(0x428045 + 2) = GetPrivateProfileInt("POTIONS MANA", "Porcentagem de recuperação para medium", 0, "./Data/Settings.txt");
	*(unsigned char*)(0x428084 + 2) = GetPrivateProfileInt("POTIONS MANA", "Porcentagem de recuperação para large", 0, "./Data/Settings.txt");

	*(unsigned int*)(0x458C98 + 3) = GetPrivateProfileInt("RINGS", "Dragon", 2, "./Data/Settings.txt");
	*(unsigned int*)(0x458CA1 + 3) = GetPrivateProfileInt("RINGS", "Death Cow", 7, "./Data/Settings.txt");
	*(unsigned int*)(0x458CAA + 3) = GetPrivateProfileInt("RINGS", "Giant", 14, "./Data/Settings.txt");
	*(unsigned int*)(0x458CB3 + 3) = GetPrivateProfileInt("RINGS", "Poison Bull", 8, "./Data/Settings.txt");
	*(unsigned int*)(0x458CBC + 3) = GetPrivateProfileInt("RINGS", "Skeleton", 9, "./Data/Settings.txt");
	*(unsigned int*)(0x458CC5 + 3) = GetPrivateProfileInt("RINGS", "Thunder Lich", 41, "./Data/Settings.txt");

	this->_Type = GetPrivateProfileInt("SERVER", "Type", 0, "./Data/Settings.txt");
	this->_MaxReset = GetPrivateProfileInt("SERVER", "Máximo de resets", 0, "./Data/Settings.txt");
	this->_PvP = GetPrivateProfileInt("SERVER", "Non-PK", 0, "./Data/Settings.txt");
	this->_CheckSum = GetPrivateProfileInt("SERVER", "Checksum", 0, "./Data/Settings.txt");
	this->_Personal = GetPrivateProfileInt("SERVER", "Personal", 0, "./Data/Settings.txt");
	this->_Reflect = GetPrivateProfileInt("SERVER", "Reflect", 0, "./Data/Settings.txt");
	this->_Mapas = GetPrivateProfileInt("SERVER", "Mapas", 0, "./Data/Settings.txt");
	this->_Announce[0] = GetPrivateProfileInt("SERVER", "Anúncio de jogadores", 0, "./Data/Settings.txt");
	this->_Announce[1] = GetPrivateProfileInt("SERVER", "Anúncio de staffs", 0, "./Data/Settings.txt");

	return true;
}

cSetting Setting;