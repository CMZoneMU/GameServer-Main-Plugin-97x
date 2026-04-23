#include "stdafx.h"

cCamera::cCamera()
{
	this->m_Enable = 0;

	this->m_Default.IsLoad = 0;

	this->m_IsMove = 0;

	this->m_CursorX = 0;

	this->m_CursorY = 0;

	this->m_Zoom.MinPercent = 50.0;

	this->m_Zoom.MaxPercent = 170.0;

	this->m_Zoom.Precision = 2.0;

	this->m_Address.Zoom = (float*)0x51F7F1; 

	this->m_Address.RotX = (float*)0x88A35E0;

	this->m_Address.RotY = (float*)0x54DD4C;

	this->m_Address.PosZ = (float*)0x54D970;

	this->m_Address.ClipX[0] = (float*)0x4F4468;

	this->m_Address.ClipX[1] = (float*)0x4F447E;

	this->m_Address.ClipY[0] = (float*)0x4F448E;

	this->m_Address.ClipY[1] = (float*)0x4F449E;

	this->m_Address.ClipZ = (float*)0x54DCB0;

	this->m_Address.ClipGL = (float*)0x51F862;

	*(float*)0x561010 = 2000.0f;

	*(BYTE*)(0x50C234) = 0x10;
	*(BYTE*)(0x50C235) = 0x10;
	*(BYTE*)(0x50C236) = 0x56;
	*(BYTE*)(0x50C237) = 0x00;

	*(BYTE*)(0x50C262) = 0x10;
	*(BYTE*)(0x50C263) = 0x10;
	*(BYTE*)(0x50C264) = 0x56;
	*(BYTE*)(0x50C265) = 0x00;

	*(BYTE*)(0x50C26E) = 0x10;
	*(BYTE*)(0x50C26F) = 0x10;
	*(BYTE*)(0x50C270) = 0x56;
	*(BYTE*)(0x50C271) = 0x00;

	SetNop(0x50D14D, 6);
	HookJump(0x50D1CD, this->Rotate);
}

void cCamera::Toggle()
{
	if (*(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_Enable = 1;

		if (((this->m_Default.IsLoad == 0) ? (this->m_Default.IsLoad++) : this->m_Default.IsLoad) == 0)
		{
			this->m_Default.Zoom = (*this->m_Address.Zoom);

			this->m_Default.RotX = (*this->m_Address.RotX);

			this->m_Default.RotY = (*this->m_Address.RotY);

			this->m_Default.PosZ = (*this->m_Address.PosZ);

			this->m_Default.ClipX[0] = (*this->m_Address.ClipX[0]);

			this->m_Default.ClipX[1] = (*this->m_Address.ClipX[1]);

			this->m_Default.ClipY[0] = (*this->m_Address.ClipY[0]);

			this->m_Default.ClipY[1] = (*this->m_Address.ClipY[1]);

			this->m_Default.ClipZ = (*this->m_Address.ClipZ);

			this->m_Default.ClipGL = (*this->m_Address.ClipGL);
		}
	}
}

void cCamera::Restore()
{
	if (this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->SetDefaultValue();
	}
}

void cCamera::SetIsMove(BOOL IsMove)
{
	if (this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_IsMove = IsMove;
	}
}

void cCamera::SetCursorX(LONG CursorX)
{
	if (this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_CursorX = CursorX;
	}
}

void cCamera::SetCursorY(LONG CursorY)
{
	if (this->m_Enable != 0 && *(DWORD*)(MAIN_SCREEN_STATE) == 5)
	{
		this->m_CursorY = CursorY;
	}
}

void cCamera::Zoom(MOUSEHOOKSTRUCTEX* lpMouse)
{
	if (this->m_Enable == 0 || this->m_IsMove != 0 || *(DWORD*)(MAIN_SCREEN_STATE) != 5)
	{
		return;
	}

	this->m_Zoom.MinLimit = (this->m_Default.Zoom / 100) * this->m_Zoom.MinPercent;

	this->m_Zoom.MaxLimit = (this->m_Default.Zoom / 100) * this->m_Zoom.MaxPercent;

	if (((int)lpMouse->mouseData) > 0)
	{
		if ((*this->m_Address.Zoom) >= this->m_Zoom.MinLimit)
		{
			SetFloat((DWORD)this->m_Address.Zoom, ((*this->m_Address.Zoom) - this->m_Zoom.Precision));
		}
	}

	if (((int)lpMouse->mouseData) < 0)
	{
		if ((*this->m_Address.Zoom) <= this->m_Zoom.MaxLimit)
		{
			SetFloat((DWORD)this->m_Address.Zoom, ((*this->m_Address.Zoom) + this->m_Zoom.Precision));
		}
	}

	this->SetCurrentValue();
}

void cCamera::Move(MOUSEHOOKSTRUCTEX* lpMouse)
{
	if (this->m_Enable == 0 || this->m_IsMove == 0 || *(DWORD*)(MAIN_SCREEN_STATE) != 5)
	{
		return;
	}

	if (this->m_CursorX < lpMouse->pt.x)
	{
		if ((*this->m_Address.RotX) > 309.0f)
		{
			SetFloat((DWORD)this->m_Address.RotX, -45.0f);
		}
		else
		{
			SetFloat((DWORD)this->m_Address.RotX, ((*this->m_Address.RotX) + 6.0f));
		}
	}

	if (this->m_CursorX > lpMouse->pt.x)
	{
		if ((*this->m_Address.RotX) < -417.0f)
		{
			SetFloat((DWORD)this->m_Address.RotX, -45.0f);
		}
		else
		{
			SetFloat((DWORD)this->m_Address.RotX, ((*this->m_Address.RotX) - 6.0f));
		}
	}

	if (this->m_CursorY < lpMouse->pt.y)
	{
		if ((*this->m_Address.RotY) > 30.0f)
		{
			SetFloat((DWORD)this->m_Address.RotY, ((*this->m_Address.RotY) - 2.420f));
			SetFloat((DWORD)this->m_Address.PosZ, ((*this->m_Address.PosZ) - 44.0f));
		}
	}

	if (this->m_CursorY > lpMouse->pt.y)
	{
		if ((*this->m_Address.RotY) < 90.0f)
		{
			SetFloat((DWORD)this->m_Address.RotY, ((*this->m_Address.RotY) + 2.420f));
			SetFloat((DWORD)this->m_Address.PosZ, ((*this->m_Address.PosZ) + 44.0f));
		}
	}

	this->m_CursorX = lpMouse->pt.x;

	this->m_CursorY = lpMouse->pt.y;

	this->SetCurrentValue();
}

void cCamera::SetCurrentValue()
{
	SetFloat((DWORD)this->m_Address.ClipX[0], (1272 + (abs(*this->m_Address.PosZ - 150) * 3) + 1000));

	SetFloat((DWORD)this->m_Address.ClipX[1], (1272 + (abs(*this->m_Address.PosZ - 150) * 3) + 1000));

	SetFloat((DWORD)this->m_Address.ClipY[0], (-672 - (abs(*this->m_Address.PosZ - 150) * 3) - 3000));

	SetFloat((DWORD)this->m_Address.ClipY[1], (-672 - (abs(*this->m_Address.PosZ - 150) * 3) - 3000));

	SetFloat((DWORD)this->m_Address.ClipZ, (1190 + (abs(*this->m_Address.PosZ - 150) * 3) + 3000));

	SetFloat((DWORD)this->m_Address.ClipGL, (4000 + (abs(*this->m_Address.PosZ - 150) * 3) + 1500));
}

void cCamera::SetDefaultValue()
{
	if (this->m_Default.IsLoad != 0)
	{
		SetFloat((DWORD)this->m_Address.Zoom, this->m_Default.Zoom);

		SetFloat((DWORD)this->m_Address.RotX, this->m_Default.RotX);

		SetFloat((DWORD)this->m_Address.RotY, this->m_Default.RotY);

		SetFloat((DWORD)this->m_Address.PosZ, this->m_Default.PosZ);

		SetFloat((DWORD)this->m_Address.ClipX[0], this->m_Default.ClipX[0]);

		SetFloat((DWORD)this->m_Address.ClipX[1], this->m_Default.ClipX[1]);

		SetFloat((DWORD)this->m_Address.ClipY[0], this->m_Default.ClipY[0]);

		SetFloat((DWORD)this->m_Address.ClipY[1], this->m_Default.ClipY[1]);

		SetFloat((DWORD)this->m_Address.ClipZ, this->m_Default.ClipZ);

		SetFloat((DWORD)this->m_Address.ClipGL, this->m_Default.ClipGL);

		this->m_Enable = 0;
	}
}

void cCamera::Correction(float& X, float& Y, float D)
{
	const float Rad = 0.01745329f;

	float sinTh = sin(Rad * (*Camera.m_Address.RotX));
	float cosTh = cos(Rad * (*Camera.m_Address.RotX));

	X += D / 0.7071067f * cosTh / 2;
	Y -= D / 0.7071067f * sinTh / 2;
}

void __declspec(naked) cCamera::Rotate()
{
	static DWORD Return = 0x50D1EB;

	_asm
	{
		ADD ESP, 0x1C;
		LEA EAX, [ESP + 0x98 - 0x84];
		LEA ECX, [ESP + 0x98 - 0x88];
		PUSH DWORD PTR [ESP + 0x98 - 0x74];
		PUSH EAX;
		PUSH ECX;
		CALL Correction;
		ADD ESP, 0xC;
		INC ESI;
		CMP ESI, EBX;
		JMP[Return];
	}
}

cCamera Camera;