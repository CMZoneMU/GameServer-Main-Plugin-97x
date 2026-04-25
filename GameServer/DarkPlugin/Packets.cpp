#include "StdAfx.h"

void PHeadSetB(LPBYTE lpBuf, BYTE head, int size)
{
	lpBuf[0] = 0xC1;
	lpBuf[1] = size;
	lpBuf[2] = head;
}

void PHeadSubSetB(LPBYTE lpBuf, BYTE head, BYTE sub, int size)
{
	lpBuf[0] = 0xC1; 
	lpBuf[1] = size;
	lpBuf[2] = head;
	lpBuf[3] = sub;
}

void PHeadSetW(LPBYTE lpBuf, BYTE head, int size)
{
	lpBuf[0] = 0xC2;
	lpBuf[1] = GET_NUMBERH(size);
	lpBuf[2] = GET_NUMBERL(size);
	lpBuf[3] = head;
}