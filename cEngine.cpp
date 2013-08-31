#include "main.h"

cEngine Engine;

cg_t* CG;
cgs_t* CGS;
refdef_t* RefDef;
viewMatrix_t* ViewMatrix;
entity_t* Entity[ENTITIESMAX];
client_t* Client[PLAYERSMAX];


void cEngine::Initialize() {
    RegisterFont_ = ( tRegisterFont ) Offsets.RegisterFont_OFFS;
    DrawEngineText_ = ( tDrawEngineText ) Offsets.EngineText_OFFS;
    RegisterShader_ = ( R_RegisterShader ) Offsets.RegisterShader_OFFS;
    GetScreenMatrix = ( tGetScreenMatrix ) Offsets.GetScreenMatrix_OFFS;
    DrawRotatedPic_ = ( tDrawRotatedPic ) Offsets.DrawRotatedPic_OFFS;
    CG_Trace_ = ( CG_Trace_t ) Offsets.CG_Trace_OFFS;
	GetTagByName = ( R_RegisterTag ) Offsets.RegisterTag_OFFS;
    WorldToScreen = ( World2Screen_ ) Offsets.WorldToScreen_OFFS;
    StrWidth_ = ( CG_StrWidth ) Offsets.StrWidth_OFFS;
	Input = (Input_t*) Offsets.Input_OFFS;//Offsets.Input_OFFS;
    CG = ( cg_t* ) Offsets.CG_OFFS;
    CGS = ( cgs_t* ) Offsets.CGS_OFFS;
    RefDef = ( refdef_t* ) Offsets.RefDef_OFFS;
    ViewMatrix = ( viewMatrix_t* ) Offsets.ViewMatrix_OFFS;
    //Entity = (entity_t*) Offsets.Entity_OFFS;
    //Client = (client_t*) Offsets.ClientInfo_OFFS;

    IsInGame = ( int* ) Offsets.IsInGame_OFFS;

    if ( GetModuleHandleA ( "steam.dll" ) )
        strcpy ( GameVersion, "Steam" );
    if ( GetModuleHandleA ( "teknomw3.dll" ) )
        strcpy ( GameVersion, "TeknoMW3" );
}

bool cEngine::GetTagPos ( entity_t* pEnt, char* szTag, float* flOut ) {
    WORD wTag = GetTagByName ( szTag );
    if ( !wTag )
        return false;

    DWORD dwCall = Offsets.GetPlayerTag_OFFS;

    __asm {
        MOV ESI, pEnt;
        MOVZX EDI, wTag;
        PUSH flOut;
        CALL dwCall;
        ADD ESP, 0x4
    }

    return true;
}

bool cEngine::CG_Trace (float* Start, float* End, entity_t* Ent, bool AutoWallOn ) {
    Trace_T trace;
    CG_Trace_ ( &trace, Start, End, CG->ClientNum, 0x803003 );
    if ( trace.fraction >= 0.97f )
        return true;
	if(!AutoWallOn)
		return false;
	return GetRemainingIndex(Start, Ent, End);
}

DWORD cEngine::GetWeaponPointer ( int iWeaponID ) {
    return * ( DWORD* ) ( Offsets.GetWeapon_OFFS + ( ( iWeaponID & 0xFF ) * 0x4 ) );
}

weapon_t* cEngine::GetWeapon ( int iWeaponID ) {
    return ( weapon_t* ) ( * ( DWORD* ) GetWeaponPointer ( iWeaponID ) );
}

char* cEngine::GetWeaponName ( int iWeaponID ) {
    static char szWeapon[32];
    szWeapon[0] = 0;
    DWORD dwWeaponName = * ( DWORD* ) ( GetWeaponPointer ( iWeaponID ) + 0x8);
    strcpy_s ( szWeapon, ( char* ) dwWeaponName );
    if ( strstr ( szWeapon, "WEAPON_" ) ) {
        char* szFixString = strrchr ( szWeapon, '_' ) + 1;
        strcpy_s ( szWeapon, szFixString );
    }
    return szWeapon;
}

char* cEngine::GetWeaponShader(DWORD dwNum)
{		
	dwNum = (*(DWORD*)(((dwNum & 0xFF) * 4) + Offsets.GetWeaponShader_OFFS));
	return (dwNum == NULL) ? NULL : (char*)(*(DWORD*)dwNum);		
}

int cEngine::AddIconToText ( int startLen, int* shader, char* text, float iconW, float iconH, BOOL flipIconHorizontal ) {
    DWORD dwFunc = Offsets.DrawShadersOnText_OFFS;
    __asm {
        push flipIconHorizontal
        push iconH
        push iconW
        mov edi, text
        mov ebx, shader
        mov eax, startLen
        call dwFunc
    }
}

char* cEngine::GetIconText ( int* shader, float iconW, float iconH, BOOL flipIconHorizontal ) {
    static char Buf[512];
    memset ( Buf, 0, 512 );

    int end = AddIconToText ( 0, shader, Buf, iconW, iconH, flipIconHorizontal );
    Buf[end] = 0;
    return Buf;
}

void cEngine::SendCommandToConsole ( char* Cmd ) {
	DWORD dwCall = Offsets.SendCommandToConsole_OFFS;
    __asm {
        push Cmd;
        push 0;
        call dwCall;
    }
}

INT GetActionIndex( CONST PCHAR Action )
{
    CONST CHAR** ActionList = ( CONST CHAR** )0x982E6C;

    for( INT i = 0; ActionList[i]; i++ )
    {
        if( _stricmp( Action, ActionList[i] ) == NULL )
        {
            return i;
        }
    }

    return -1;
}

BOOL cEngine::ExecuteAction( CONST PCHAR Action )
{
    INT aIndex = GetActionIndex( Action );

    if( aIndex == -1 )
    {
        return FALSE;
    }
    else
    {
		static DWORD dwFunc = Scan.FindPattern("\x55\x8B\x6C\x24\x0C\x56\x8B\x74\x24\x0C\x83\xFD\x4A", "xxxxxxxxxxxxx");
        __asm
        {
            push 1337 // hacky, should be keynum but doesnt matter.
            push aIndex
            push 0
            call dwFunc
            add esp, 0Ch
        }

        return TRUE;
    }
}

bool cEngine::BulletPenetrationCheck ( BulletTrace_T* MapTrace ) {
    DWORD dwCallAddr = Offsets.R_BulletPenetrationCheckOFFS;

    static bool returnC;

    __asm mov  eax, MapTrace
    __asm call dwCallAddr
    __asm mov  returnC, al

    return returnC;
}

void cEngine::BulletPenetration ( int unk1, BulletTrace_T* bulletTrace, int WeaponNum, int unk2, entity_t* cent, int unk3, float vieworg[3], int unk4 ) {
    DWORD dwCallAddr = Offsets.R_BulletPenetrationOFFS;
    __asm {
        push unk4
        push vieworg
        push unk3
        push cent
        push unk2
        push WeaponNum
        push bulletTrace
        push unk1
        call dwCallAddr
        add     esp, 0x20
    }
}

bool cEngine::GetRemainingIndex ( float vieworg[3], entity_t* TargetEnt, float origin[3] ) {
	unsigned char patch[2] = {0x90, 0x90};
	unsigned long orig1;
    VirtualProtect ( ( void* ) 0x5C420E, 10, PAGE_EXECUTE_READWRITE, &orig1 );
    memcpy((DWORD*)0x5C420E, patch, 2);
	memcpy((DWORD*)0x5C4217, patch, 2);
    VirtualProtect ( ( void* ) 0x5C420E, 10, orig1, &orig1 );


    if ( !bulletTrace ) {
        bulletTrace = new BulletTrace_T;
        ZeroMemory ( bulletTrace, sizeof ( BulletTrace_T ) );
    }

	int Weapon = CG->WeaponID;

    //memset(bulletTrace, 0, sizeof(BulletTrace_T));
    bulletTrace->MaxEntNum    = 2046;
	bulletTrace->EntitieNum = CG->ClientNum;
    bulletTrace->visible    = 1.0f;
    bulletTrace->z_crap0    = ( Weapon + 1905 );

    Math.VectorCopy ( RefDef->ViewAngles, bulletTrace->viewOrigin );
    Math.VectorCopy ( vieworg, bulletTrace->start );
    Math.VectorCopy ( origin, bulletTrace->end );

    float delta[3], angles[3];
    Math.VectorSubtract ( origin, vieworg, delta );
    Math.VectorAngles ( delta, angles );

    Math.AngleVectors ( angles, bulletTrace->viewAngle, NULL, NULL );

    BulletPenetrationCheck ( bulletTrace );
    BulletPenetration ( 0, bulletTrace, Weapon, 0, &TargetEnt[CG->ClientNum], 0xFFFFFFFF, vieworg, 0 );

	return bulletTrace->EntitieNum == TargetEnt->ClientNum;
}