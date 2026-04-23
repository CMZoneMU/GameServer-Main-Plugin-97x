#pragma once

#define WIN32_LEAN_AND_MEAN

#include <set>
#include <string>
#include <vector>
#include <Windows.h>
#include "WindowsX.h"
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <sstream>
#include <fstream>
#include <direct.h>
#include <time.h>
#include <tlhelp32.h>
#include <process.h>
#include <WinSock2.h>
#include <ShellAPI.h>
#include <unordered_map>
#include <gl\gl.h>
#include <gl\glu.h>
#include <utility>
#include <iostream>
#include <tchar.h>
#include <cstdlib>
#include <cstdio>

#pragma comment(lib,"user32.lib")
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"Detours.lib")


#include "Optimize.h"
#include "Principal.h"
#include "detours.h"
#include "Functions.h"
#include "Janela.h"
#include "Monster.h"
#include "Offsets.h"
#include "Packets.h"
#include "Protocol.h"
#include "Visual.h"
#include "Texture.h"
#include "Description.h"
#include "Title.h"
#include "Camera.h"
#include "Resolution.h"
#include "Jewel.h"
#include "Tokenizer.h"
#include "Math.h"
#include "Effect.h"
#include "Font.h" // [ Novo ]: Alteração no antigo sistema de fontes para um mais otimizado e flexível
#include "HPBar.h"
#include "Right.h"
#include "Patent.h"
#include "Guild.h"
#include "Message.h"
#include "Protect.h" // [ Novo ]: Proteção contra injeção de DLLs
#include "CCRC32.h" // [ Novo ]: CRC32 para verificação de arquivos
#include "Interface.h"