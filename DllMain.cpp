#include "main.h"
cMenu Menu = cMenu(4);
void CreateHackMenu(){
	MyRect Pos = {20, 20, 150, 150};
	Menu.SetPosition(Pos);
	Menu.MenuActive = false;
	Menu.AddTab(0, "ESP", false);
	Menu.AddTab(1, "Misc", false);
	Menu.AddTab(2, "Aimbot", false);
	Menu.AddTab(3, "Show WhiteList", false);

	Menu.Tabs[0].NumberOfOptions = 8;
	Menu.Tabs[1].NumberOfOptions = 8;
	Menu.Tabs[2].NumberOfOptions = 4;

	Menu.Tabs[0].AddOption(0, "Bones", true);
	Menu.Tabs[0].AddOption(1, "Names", true);
	Menu.Tabs[0].AddOption(2, "Distance", false);
	Menu.Tabs[0].AddOption(3, "Weapons", true);
	Menu.Tabs[0].AddOption(4, "Items", true);
	Menu.Tabs[0].AddOption(5, "Explosives", true);
	Menu.Tabs[0].AddOption(6, "2D Boxes", true);
	Menu.Tabs[0].AddOption(7, "3D Boxes", false);

	Menu.Tabs[1].AddOption(0, "No-Spread (Host Only)", true);
	Menu.Tabs[1].AddOption(1, "No-Recoil", true);
	Menu.Tabs[1].AddOption(2, "No-Fog", false);
	Menu.Tabs[1].AddOption(3, "FullBright", false);
	Menu.Tabs[1].AddOption(4, "Lasers", true);
	Menu.Tabs[1].AddOption(5, "Advanced Uav", true);
	Menu.Tabs[1].AddOption(6, "Crosshair", true);
	Menu.Tabs[1].AddOption(7, "Visibility Check", true);

	Menu.Tabs[2].AddOption(0, "Activated", true);
	Menu.Tabs[2].AddOption(1, "Auto-Zoom", true);
	Menu.Tabs[2].AddOption(2, "Auto-Shoot", true);
	Menu.Tabs[2].AddOption(3, "Auto-Wall", true);

}

void ReadGame() {
    for ( int i = 0; i < ENTITIESMAX; i++ )
        Entity[i] = ( entity_t* ) ( Offsets.Entity_OFFS + ( ( int ) Offsets.Entity_Size_OFFS * i ) );
    for ( int i = 0; i < PLAYERSMAX; i++ )
        Client[i] = ( client_t* ) ( Offsets.ClientInfo_OFFS + ( ( int ) Offsets.ClientInfo_Size_OFFS * i ) );
}

void NoSpread(){
	weapon_t* pWeapon = Engine.GetWeapon(Entity[CG->ClientNum]->WeaponID);
		pWeapon->Spread0=0;
        pWeapon->Spread1=0;
        pWeapon->Spread2=0;
        pWeapon->Spread3=0;
        pWeapon->Spread4=0;
        pWeapon->Spread5=0;
        pWeapon->Spread6=0;
        pWeapon->Spread7=0;
        pWeapon->Spread8=0;
        pWeapon->Spread9=0;
}

bool bInitialize = false;
void WrapperFunc() {

    if ( !bInitialize ) {
        Draw.MenuFont = Engine.RegisterFont_ ( FONT_SMALL_DEV );
        Draw.NamesFont = Engine.RegisterFont_ ( FONT_CONSOLE );
        Draw.Shader = Engine.RegisterShader_ ( "white" );
        bInitialize = true;
    }

    ReadGame();
	Menu.DrawMenu();

    if ( *Engine.IsInGame != 0 ) {
		
		if(Menu.IsOptionActive (0, "2D Boxes")) ESP.ChopperBoxes();
		if(Menu.IsOptionActive (1,"No-Spread (Host Only)" )) NoSpread();
        Misc.Laser ( Menu.IsOptionActive (1,"Lasers" ) );
        Misc.Crosshair ( Menu.IsOptionActive (1,"Crosshair" ) );
        Misc.NoRecoil ( Menu.IsOptionActive ( 1,"No-Recoil" ) );
        Misc.FullBright ( Menu.IsOptionActive ( 1,"FullBright" ) );
        Misc.NoFog ( Menu.IsOptionActive ( 1,"No-Fog" ) );
        Misc.AdvUav ( Menu.IsOptionActive ( 1,"Advanced Uav" ) );

        for ( int i = 0; i < PLAYERSMAX; i++ ) {
            if ( CG->ClientNum == Entity[i]->ClientNum ) {
                Engine.MyTeam = Client[i]->Team;
                break;
            }
        }
		
        for ( int i = 0; i < ENTITIESMAX; i++ ) {

            if ( Entity[i]->Type != ET_PLAYER && Entity[i]->Type != ET_TURRET && Entity[i]->Type != ET_ITEM && Entity[i]->Type != ET_EXPLOSIVE ) continue;
          
            if ( Entity[i]->Type == ET_ITEM && Menu.IsOptionActive ( 0, "Items" ) && Entity[i]->Valid ) {
                float Screen[2];
                if ( Engine.WorldToScreen ( 0, Engine.GetScreenMatrix(), Entity[i]->Origin, Screen ) ) 
                    ESP.DrawItems(Entity[i], Client[i], Screen);
            }

            if ( Entity[i]->Type == ET_EXPLOSIVE){
				if(Menu.IsOptionActive ( 0, "Explosives" ) && Entity[i]->IsAlive & 1) {
					float Screen[2];
					if ( Engine.WorldToScreen ( 0, Engine.GetScreenMatrix(), Entity[i]->Origin, Screen ) ) {
						char* Shader = Engine.GetWeaponShader(Entity[i]->WeaponID);
						if(Shader != NULL)
							Draw.DrawShader(Screen[0], Screen[1], 20, 20, Shader, WHITE);
					}
				}
			}
            if ( Entity[i]->Type == ET_PLAYER && i < PLAYERSMAX && Entity[i]->IsAlive & 1 && Entity[i]->Valid && CG->ClientNum != Entity[i]->ClientNum ) {
				
                Vector BonePos;
                bool IsVisible = false;

                Engine.GetTagPos ( Entity[i], "j_helmet", BonePos );
                if ( Menu.IsOptionActive ( 1,"Visibility Check" ) )
                    IsVisible = Engine.CG_Trace ( RefDef->ViewOrg, BonePos, Entity[i], false );
                if ( Menu.IsOptionActive ( 0,"Bones" ) )
                    ESP.DrawBones ( Entity[i], Client[i], IsVisible );

                if ( Menu.IsOptionActive ( 0,"Names" ) ) {
                    float Screen[2];
                    if ( Engine.WorldToScreen ( 0, Engine.GetScreenMatrix(), BonePos, Screen ) )
                        ESP.DrawNames ( Entity[i], Client[i], Screen );
                }
                if ( Menu.IsOptionActive ( 0,"Distance" ) ) {
                    float Screen[2];
                    if ( Engine.WorldToScreen ( 0, Engine.GetScreenMatrix(), Entity[i]->Origin, Screen ) )
                        ESP.DrawDistance ( Entity[i], Client[i], Screen );
                }
                if ( Menu.IsOptionActive ( 0,"Weapons" ) ) {
                    float Screen[2];
                    if ( Engine.WorldToScreen ( 0, Engine.GetScreenMatrix(), BonePos, Screen ) )
                        ESP.DrawWeaponsNames ( Entity[i], Client[i], Screen);
                }
                if ( Menu.IsOptionActive ( 0,"3D Boxes" ) ) {
                    BonePos[2] += 5;
                    ESP.Draw3DBox ( Entity[i], Client[i], BonePos, IsVisible );
                    BonePos[2] -= 5;
                }
            }
        }
    }
}

void hkUIShowList ( int a1, int a2, int a3, int a4 ) {
    __asm PUSHAD;

    WrapperFunc();

    __asm POPAD;
    Engine.UiShowList ( a1, a2, a3, a4 );
}


void Wrapper() { 
	if(*Engine.IsInGame != 0){
		if(Menu.IsOptionActive(2, "Activated"))
			Aimbot.Initialize(Menu.IsOptionActive(2, "Auto-Zoom"), Menu.IsOptionActive(2, "Auto-Wall"), Menu.IsOptionActive(2, "Auto-Shoot"));
	}
} 

long __stdcall pVectoredExceptionHandler(_EXCEPTION_POINTERS *pException) { 
	if(pException->ContextRecord->Eip==Offsets.ExcAddy) //This is the address where the exception happens 
	{ 
		//Restore EDI. EDI = dwDVar wich is 0 and supposed to be dwDVarValue
		pException->ContextRecord->Edi = Offsets.dwDVarValue; 

		Wrapper(); //Call our function

		return EXCEPTION_CONTINUE_EXECUTION; 
	} 
	return EXCEPTION_CONTINUE_SEARCH; 
}

BOOL APIENTRY DllMain ( HMODULE hModule, DWORD  reason, LPVOID lpReserved ) {
    if ( reason == DLL_PROCESS_ATTACH ) {
        Offsets.Initialize();

        Engine.Initialize();

		CreateHackMenu();

        HMODULE aCI = GetModuleHandleA ( "libnp.dll" );
		
        if ( aCI != NULL ) {
            MessageBoxA ( NULL, "This Hack doesn't support this game version", "Game Version Not Supported", MB_OK | MB_ICONERROR );
            exit ( 1 );
        }
		aCI = GetModuleHandleA ( "teknomw3.dll" );
		if ( aCI != NULL ) {
            MessageBoxA ( NULL, "This Hack doesn't support this game version", "Game Version Not Supported", MB_OK | MB_ICONERROR );
            exit ( 1 );
        }
		
		MessageBoxA(NULL, "Hack sucesfully injected. Press INSERT or DELETE do show up the menu.\nIf it doesn't work... IDK what could be wwrong...", "Sucess", MB_OK);

        Engine.UiShowList = ( tUiShowList ) Hook.DetourFunction ( ( BYTE* ) Offsets.UIShowList_OFFS, ( BYTE* ) &hkUIShowList, 5 );
		
		AddVectoredExceptionHandler(1,pVectoredExceptionHandler); 
		*(DWORD*)Offsets.dwDVar = 0x0; //Set DVar to 0 so that an exception happens at 0x5A14F7
    }
    return TRUE;
}

