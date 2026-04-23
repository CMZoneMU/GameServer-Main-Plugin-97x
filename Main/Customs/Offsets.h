#pragma once

#define MAIN_SCREEN_STATE 0x55C540
#define MAIN_FONT_SIZE 0x82773E8
#define MAIN_RESOLUTION 0x55C4E90
#define MAIN_RESOLUTION_X 0x55C4EC
#define MAIN_RESOLUTION_Y 0x55C4F0

#define ITEMGET(X,Y) ((X)* 32 + (Y))
#define ITEM(X,Y) ((X)* 32 + (Y) + 0x190)
#define RGBA(R, G, B, A) (A << 24) | (B << 16) | (G << 8) | R
#define MAKE_NUMBERW(X,Y) ((WORD)(((BYTE)((Y)&0xFF)) | ((BYTE)((X)&0xFF) << 8)))
#define Screen ".\\ScreenShot\\Screen(%02d_%02d-%02d_%02d)-%04d.jpg"
#define WndProc (WNDPROC)(0x414190)
#define GameWindow *(HWND*)0x55C5054
#define MAIN_STATE *(int*)0x55C540
#define WorldTime *(float*)0x5D9B46C
#define DeltaT *(float*)0x5547E0
#define FPS *(float*)0x5D9B45C
#define GCLevelUInfoSend ((void(*)()) 0x47C040)
#define LoadWav ((int(*)(int,char*,int,int)) 0x4048B0)
#define PlayWav ((int(*)(int,int,int)) 0x404A60)
#define LevelUpAddPoint	((void(*)(struct PMSG_LVPOINTADDRESULT*))(0x430A80))
#define LevelUpRecv ((void(*)(struct PMSG_LEVELUP*))(0x430780))
#define MainSpeedFrame1 (float*)(0x54D4BC)
#define MainSpeedFrame2 (float*)(0x54D8CC)
#define DrawBar ((double(__cdecl*)(float a1, float a2, int a3, float a4, float a5)) 0x50D200)
#define DrawTab	((int(__cdecl*)(signed int a1, signed int a2, LPCSTR lpMultiByteStr)) 0x47D590)
#define DrawInfo ((int(__cdecl*)(int a1, int a2, LPCSTR a3, int a4, char a5, int a6)) 0x47D3F0)
#define ItemText ((int(*)(int Arg1, const char * Text, ...)) 0x53D1BC)
#define TextWindow ((void(*)(char* Text)) 0x5185A0)
#define AllowStaticEffect ((void(__thiscall*)(DWORD *a1, DWORD *a2, float *a3, vec3_t *VecPos, char a5)) 0x43F9B0)                                                              
#define DynamicEffect ((int(__cdecl*)(DWORD ModelID, DWORD * Arg1, int Arg2, float * Color, int Arg4, float Arg5, int Arg6)) 0x4731A0)      
#define StaticEffect ((int(__cdecl*)(DWORD ModelID, __int16 a2, int a3, int a4, float *a5, int a6)) 0x4541E0)                               
#define DrawItemEffect ((void(__cdecl*)(int lpModel, int ItemModel, int a3, GLfloat alpha, int a5, int a6, int a7, int a8, int a9)) 0x4FFB20)
#define GLSwitchBlend ((void(__cdecl*)()) 0x50C610)
#define GLSwitch ((void(__cdecl*)()) 0x50C500)
#define SetBlend ((void(__cdecl*)(BYTE Mode)) 0x50C580)
#define GetPosFromAngle ((void(__cdecl*)(VAngle * Angle, int * PosX, int * PosY))0x50C2F0)
#define DrawBarForm ((void(__cdecl*)(float PosX, float PosY, float Width, float Height)) 0x50D3D0)
#define GetCursorWorkSize ((int(__cdecl*)(int PosX,int PosY,int Width,int Height,int Mode)) 0x40C330)
#define DrawTextOut ((int(*)(int x, int y, LPCSTR Text, int BackgroundWidth, int AlignCenter, int a6)) 0x47D3F0)
#define pLoadImage	((void(*)(char * Folder, int Id, int BlendType, int a4, int a5, int a6)) 0x524360)
#define pLoadImageTga ((void(*)(char * Folder, int Id, int BlendType, int a4, int a5, int a6)) 0x5247F0)
#define LoadImages ((void(__cdecl*)()) 0x50B220)
#define RenderBoolean ((void(__cdecl*)(int x, int y, DWORD c)) 0x47EBA0)
#define Mark ((void(__cdecl*)(int nMarkIndex, bool blend)) 0x4EBAD0)
#define RenderBitmap ((void(__cdecl*)(int Texture, float x, float y, float Width, float Height, float u, float v, float uWidth, float vHeight, bool Scale, bool StartScale)) 0x50D4B0)
#define GCMsgStringSend ((void(*)(const char * Send, const char * Text, BYTE Color)) (0x47E3C0))
#define	DrawMessage	((int(__cdecl*)(char*,int)) 0x47D880)


// New Font
#define FontHeight *(int*)0x82773E8 // Kayito 0x07D78080 ->  0x82773E8
#define g_hFont *(HFONT*)0x055C5064 // Kayito 0x055CA00C ->  0x055C5064
#define g_hFontBold *(HFONT*)0x055C5068 // Kayito 0x055CA010 -> 0x055C5068
#define g_hFontBig *(HFONT*)0x055C506C // Kayito 0x055CA014 -> 0x055C506C
#define OpenFont ((void(_cdecl*)())0x0050A590) // Kayito 0x0050F690 -> 0x0050A590

// Window
#define m_Resolution *(int*)0x055C50D4 // Kayito 0x055C9E38 -> 0x055C50D4
#define WindowWidth *(int*)0x0055C4EC // Kayito 0x0056156C -> 0x0055C4EC
#define WindowHeight *(int*)0x0055C4F0 // Kayito 0x00561570 -> 0x0055C4F0
#define g_fScreenRate_x *(float*)0x055C4BC0   // Kayito 0x55C9B70 -> 0x055C4BC0
#define g_fScreenRate_y *(float*)0x055C4BC4   // Kayito 0x55C9B74 -> 0x055C4BC4
#define m_hFontDC *(HDC*)0x055C5044 // Kayito 0x055C9FEC -> 0x055C5044
#define g_hWnd *(HWND*)0x055C5054 // Kayito 0x055C9FFC -> 0x055C5054
#define g_hDC *(HDC*)0x055C505C  // Kayito 0x055CA004 -> 0x055C505C
#define g_hRC *(HGLRC*)0x055C5060  // Kayito 0x055CA008 -> 0x055C5060

// Aminyuz
#define GCClientMsgStringSend		((void(*)(const char * szSender, const char * szText, BYTE Color))(0x0047E3C0))