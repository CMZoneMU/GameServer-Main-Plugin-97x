#include "StdAfx.h"

void cPatent::LoadImagesEx()
{
	Patent.Image(1, "Custom\\Patent\\Rank01.tga", 183);
	Patent.Image(1, "Custom\\Patent\\Rank02.tga", 184);
	Patent.Image(1, "Custom\\Patent\\Rank03.tga", 185);
	Patent.Image(1, "Custom\\Patent\\Rank04.tga", 186);
	Patent.Image(1, "Custom\\Patent\\Rank05.tga", 187);
	Patent.Image(1, "Custom\\Patent\\Rank06.tga", 188);
	Patent.Image(1, "Custom\\Patent\\Rank07.tga", 189);
	Patent.Image(1, "Custom\\Patent\\Rank08.tga", 190);
	Patent.Image(1, "Custom\\Patent\\Rank09.tga", 191);
	Patent.Image(1, "Custom\\Patent\\Rank10.tga", 192);
	Patent.Image(1, "Custom\\Patent\\Rank11.tga", 193);
	Patent.Image(1, "Custom\\Patent\\Rank12.tga", 194);
	Patent.Image(1, "Custom\\Patent\\Rank13.tga", 195);
	Patent.Image(1, "Custom\\Patent\\Rank14.tga", 196);
	Patent.Image(1, "Custom\\Patent\\Rank15.tga", 197);
	Patent.Image(1, "Custom\\Patent\\Rank16.tga", 198);
	Patent.Image(1, "Custom\\Patent\\Rank17.tga", 199);
	Patent.Image(1, "Custom\\Patent\\Rank18.tga", 200);
	Patent.Image(1, "Custom\\Patent\\Rank19.tga", 201);
	Patent.Image(1, "Custom\\Patent\\Rank20.tga", 202);
	Patent.Image(1, "Custom\\Patent\\Rank21.tga", 203);
	Patent.Image(1, "Custom\\Patent\\Rank22.tga", 204);
	Patent.Image(1, "Custom\\Patent\\Rank23.tga", 205);
	Patent.Image(1, "Custom\\Patent\\Rank24.tga", 206);
	Patent.Image(1, "Custom\\Patent\\Rank25.tga", 207);
	Patent.Image(1, "Custom\\Patent\\Rank26.tga", 208);
	Patent.Image(1, "Custom\\Patent\\Rank27.tga", 209);
	Patent.Image(1, "Custom\\Patent\\Rank28.tga", 210);
	Patent.Image(1, "Custom\\Patent\\Rank29.tga", 211);
	Patent.Image(1, "Custom\\Patent\\Rank30.tga", 212);
	Patent.Image(1, "Custom\\Patent\\Rank31.tga", 213);
	Patent.Image(1, "Custom\\Patent\\GameMaster.tga", 214);
	Patent.Image(1, "Custom\\Patent\\Rei.tga", 215);

	LoadImages();
}

void cPatent::Image(int Type, char * Folder, int Id)
{
	switch (Type)
	{
	case 0:
	{
		pLoadImage(Folder, Id, 9728, 10496, 0, 1);  //JPG
	}
	break;
	case 1:
	{
		pLoadImageTga(Folder, Id, 9729, 10496, 0, 1); //TGA
	}
	break;
	}
}

void cPatent::GCReqRankLevelUser(PMSG_CUSTOM_RANKUSER * aRecv)
{
	if (aRecv == NULL)
	{
		return;
	}

	this->RankStruct[aRecv->Index].ResetCount = aRecv->ResetCount;
	this->RankStruct[aRecv->Index].Rank = aRecv->Rank;
	this->RankStruct[aRecv->Index].Type = aRecv->Type;
}

void cPatent::Run()
{
	int X, Y;
	VAngle Angle;

	for (int i = 0; i < 390; i++)
	{
		DWORD ViewPort = *(DWORD*)(0x08033C38) + (i * 916);

		if ((*(BYTE*)ViewPort != 0x0) && (*(BYTE*)(ViewPort + 132) == 1))
		{
			int index = *(WORD*)(ViewPort + 476);

			if (m_Patent[0] == true)
			{
				continue;
			}

			Angle.X = *(float*)(ViewPort + 16);

			Angle.Y = *(float*)(ViewPort + 20);

			Angle.Z = *(float*)(ViewPort + 300) + *(float*)(ViewPort + 24) + 100.0f;

			GetPosFromAngle(&Angle, &X, &Y);

			X -= 42;

			glColor3f(1.0f, 1.0f, 1.0f);

			SetBlend(true);

			if (this->RankStruct[index].Rank >= 0 && this->RankStruct[index].Type == 1)
			{
				RenderBitmap(183 + this->RankStruct[index].Rank, (float)X + 26, (float)Y - 50, 35, 55, 0.0, 0.0, 0.62, 1.0, true, true);
			}
			else if (this->RankStruct[index].Rank == -1 && this->RankStruct[index].Type == 2)
			{
				RenderBitmap(214, (float)X + 26, (float)Y - 50, 35, 55, 0.0, 0.0, 0.62, 1.0, true, true);
			}
			else if (this->RankStruct[index].Rank == -1 && this->RankStruct[index].Type == 3)
			{
				RenderBitmap(215, (float)X + 26, (float)Y - 50, 35, 55, 0.0, 0.0, 0.62, 1.0, true, true);
			}

			GLSwitch();
		}

		GLSwitch();

		glColor3f(1.0f, 1.0f, 1.0f);
	}
}

cPatent Patent;