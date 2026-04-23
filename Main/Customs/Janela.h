extern HWND (WINAPI* pCreateWindowExA)(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
extern LONG (WINAPI* pChangeDisplaySettingsA)(DEVMODEA*, DWORD);

HWND WINAPI dtCreateWindowExA(DWORD ExStyle, LPCSTR ClassName, LPCSTR WindowName, DWORD Style, int X, int Y, int Width, int Height, HWND Parent, HMENU Menu, HINSTANCE Instance, LPVOID Parameter);
LONG WINAPI dtChangeDisplaySettingsA(DEVMODEA* DevMode, DWORD Flag);