#include <Windows.h>
#include <iostream>
#include <math.h>
#include <Psapi.h>
#include <string.h>
#include <time.h>
#include <fstream>

#pragma comment(lib, "psapi.lib")
#pragma comment(lib, "detours.lib")
#define FONT_SMALL_DEV    "fonts/smallDevFont"
#define FONT_BIG_DEV    "fonts/bigDevFont"
#define FONT_CONSOLE    "fonts/consoleFont"
#define FONT_BIG        "fonts/bigFont"
#define FONT_SMALL        "fonts/smallFont"
#define FONT_BOLD        "fonts/boldFont"
#define FONT_NORMAL        "fonts/normalFont"
#define FONT_EXTRA_BIG    "fonts/extraBigFont"
#define FONT_OBJECTIVE    "fonts/objectiveFont"
#define FONT_HUD_SMALL "fonts/hudsmallfont"
#define FONT_HUD_BIG "fonts/hudBigfont"

#define ANGLE2SHORT(x)((int)((x)*65536/360) & 65535)

#include "Structs.h"

#include "Math.h"
#include "cEngine.h"
#include "Scanner.h"
#include "cOffsets.h"
#include "cHook.h"
#include "cMenu.h"
#include "Drawing.h"
#include "ESP.h"
#include "Aimbot.h"
#include "Misc.h"
#include "cReader.h"