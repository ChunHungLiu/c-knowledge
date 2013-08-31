#include "main.h"

cMisc Misc;

int cMisc::GetFPS() {
    int FrameRate;
    static float myFPS, LastCount, CurrentCount;

    CurrentCount = clock() * 0.001f;
    ++myFPS;
    if ( ( CurrentCount - LastCount ) > 0.5f ) {
        LastCount = CurrentCount;
        FrameRate = myFPS;
        myFPS = NULL;
    }
    return FrameRate * 2;
}

void cMisc::Laser ( bool Enabled ) {

    unsigned long* Laser = ( unsigned long* ) ( Offsets.Laser_OFFS );
    unsigned char On[2] = {0x90, 0x90};
    unsigned char Off[2] = {0x74, 0x25};
    unsigned long orig1;
    VirtualProtect ( ( void* ) Laser, sizeof ( On ), PAGE_EXECUTE_READWRITE, &orig1 );

    if ( Enabled )
        memcpy ( ( void* ) Laser, &On, sizeof ( On ) );
    else
        memcpy ( ( void* ) Laser, &Off, sizeof ( Off ) );

    VirtualProtect ( ( void* ) Laser, sizeof ( On ), orig1, &orig1 );
}

void cMisc::NoRecoil ( bool Enabled ) {

    unsigned long* Recoil = ( unsigned long* ) ( Offsets.NightmareTX_NoRecoil_OFFS );
    unsigned char On[2] = {0x90, 0x90};
    unsigned char Off[2] = {0xD8, 0x00};
    unsigned long orig1;
    VirtualProtect ( ( void* ) Recoil, sizeof ( On ), PAGE_EXECUTE_READWRITE, &orig1 );

    if ( Enabled )
        memcpy ( ( void* ) Recoil, &On, sizeof ( On ) );
    else
        memcpy ( ( void* ) Recoil, &Off, sizeof ( Off ) );

    VirtualProtect ( ( void* ) Recoil, sizeof ( On ), orig1, &orig1 );
}

void cMisc::NoFog ( bool Enabled ) {

    if ( Enabled )
        * ( DWORD* ) ( Offsets.FullBright_OFFS + 0x4 ) = 2;
    else
        * ( DWORD* ) ( Offsets.FullBright_OFFS + 0x4 ) = 5;
}

void cMisc::FullBright ( bool Enabled ) {

    if ( Enabled )
        * ( DWORD* ) ( Offsets.FullBright_OFFS ) = 4;
    else
        * ( DWORD* ) ( Offsets.FullBright_OFFS ) = 9;
}

void cMisc::AdvUav ( bool Enabled ) {

    if ( Enabled ) {
        * ( BYTE* ) ( * ( DWORD* ) ( Offsets.AdvUavCVAR_OFFS ) + 0xC ) = 1;
        * ( int* ) Offsets.AdvUav_OFFS = 1;
    } else {
        * ( BYTE* ) ( * ( DWORD* ) ( Offsets.AdvUavCVAR_OFFS ) + 0xC ) = 0;
        * ( int* ) Offsets.AdvUav_OFFS = 0;
    }
}

void cMisc::Crosshair( bool Enabled ){
	if ( Enabled )
		Draw.DrawEngineText(true, RefDef->Width/2, RefDef->Height/2 + 5, Draw.NamesFont, CROSSHAIR, "( + )");
}

void cMisc::AutoC4(entity_t* Ent){
	for(int i = 0; i < 18; i++) //<- looping through players
    {      
        if(Client[i]->Team == Client[CG->ClientNum]->Team)//<-TeamChecking
            continue;

		float Distance = Math.GetDistance( Ent->Origin , Entity[i]->Origin);
            // ^-Getting the distance-^
                
		if(Distance < 3.5f)//<-Is Player in range
        {
			Engine.Input->Lethal.Pressed = 1;

        }else Engine.Input->Lethal.Pressed = 0;
    }
}

void cMisc::ThermalOverlay(bool Enabled){
	BYTE patch[4] = {0xB1, 0x01, 0x90, 0x90};
	BYTE unpatch[4] = {0x8A, 0x44, 0x24, 0x04};

	if(Enabled)
		memcpy((DWORD*)0x00461110, patch, 4);
	else
		memcpy((DWORD*)0x00461110, unpatch, 4);
}