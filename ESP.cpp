#include "main.h"

cESP ESP;

void cESP::DrawBones ( entity_t* Entity, client_t* Client, bool IsVisible ) {
    float Screen[2];
    ScreenMatrix* ScreenMat;
    Vector BonePos;
    bool Enemy = true;

    ScreenMat = Engine.GetScreenMatrix();

    Enemy = ! ( ( ( Client->Team == 1 ) || ( Client->Team == 2 ) ) && ( Client->Team == Engine.MyTeam ) );

    for ( int j = 0; j < BONESMAX; j++ ) {
        Engine.GetTagPos ( Entity, Bones[j], BonePos );

        if ( Engine.WorldToScreen ( 0, ScreenMat, BonePos, Screen ) ) {
            if ( !Enemy )
				Draw.DrawEngineText ( false, Screen[0], Screen[1], Draw.MenuFont, BONES_FRIEND, "." );
            else if ( !IsVisible )
				Draw.DrawEngineText ( false, Screen[0], Screen[1], Draw.MenuFont, BONES_ENEMY, "." );
            else
                Draw.DrawEngineText ( false, Screen[0], Screen[1], Draw.MenuFont, BONES_ENEMY_VISIBLE, "." );
        }
    }
}

void cESP::DrawNames ( entity_t* Entity, client_t* Client, float* Screen ) {
    bool Enemy = true;

    Enemy = ! ( ( ( Client->Team == 1 ) || ( Client->Team == 2 ) ) && ( Client->Team == Engine.MyTeam ) );

    if ( Enemy )
        Draw.DrawEngineText ( true, Screen[0], Screen[1] - 10, Draw.MenuFont, ENEMY_NAME, "^1%s", Client->Name );
    else
        Draw.DrawEngineText ( true, Screen[0], Screen[1] - 10, Draw.MenuFont, FRIEND_NAME, "^2%s", Client->Name );
}

void cESP::DrawDistance ( entity_t* Entity, client_t* Client, float* Screen ) {
    bool Enemy = true;

    Enemy = ! ( ( ( Client->Team == 1 ) || ( Client->Team == 2 ) ) && ( Client->Team == Engine.MyTeam ) );

    if ( Enemy )
        Draw.DrawEngineText ( true, Screen[0], Screen[1] + 10, Draw.MenuFont, ENEMY_DIST, "^1%.2f", Math.GetDistance ( RefDef->ViewOrg, Entity->Origin ) );
    else
        Draw.DrawEngineText ( true, Screen[0], Screen[1] + 10, Draw.MenuFont, FRIEND_DIST, "^2%.2f", Math.GetDistance ( RefDef->ViewOrg, Entity->Origin ) );
}

void cESP::Draw3DBox ( entity_t* Entity, client_t* Client, Vector BonePos, bool IsVisible ) {

    bool Enemy = ! ( ( ( Client->Team == 1 ) || ( Client->Team == 2 ) ) && ( Client->Team == Engine.MyTeam ) );
    if ( Enemy )
        if ( !IsVisible )
			Draw.Make3DBox ( BonePos, Draw.GetBoxWidth ( Entity ), -Draw.GetBoxHeight ( Entity ), BOX_ENEMY );
        else
            Draw.Make3DBox ( BonePos, Draw.GetBoxWidth ( Entity ), -Draw.GetBoxHeight ( Entity ), BOX_ENEMY_VISIBLE );
}

void cESP::DrawWeaponsNames ( entity_t* Entity, client_t* Client, float* Screen ) {
    bool Enemy = true;

    Enemy = ! ( ( ( Client->Team == 1 ) || ( Client->Team == 2 ) ) && ( Client->Team == Engine.MyTeam ) );
	char* Shader = Engine.GetWeaponShader(Entity->WeaponID);
    if ( Enemy ){
		if(Shader != NULL)
			Draw.DrawShader(Screen[0] - 20, Screen[1] - 40, 20, NULL, Shader, ENEMY_GUN);
		else
			Draw.DrawEngineText ( true, Screen[0], Screen[1] - 20, Draw.MenuFont, ENEMY_GUN, "^1%s", Engine.GetWeaponName ( Entity->WeaponID ) );
	}
    else{
		if(Shader != NULL)
			Draw.DrawShader(Screen[0] - 20, Screen[1] - 40, 20, NULL, Shader , FRIEND_GUN);
		else
            Draw.DrawEngineText ( true, Screen[0], Screen[1] - 20, Draw.MenuFont, FRIEND_GUN, "^2%s", Engine.GetWeaponName ( Entity->WeaponID ) );
	}
}

void cESP::DrawItems ( entity_t* Entity, client_t* Client, float* Screen ) {
	char* Shader = Engine.GetWeaponShader(Entity->WeaponID);
	if(Shader != NULL)
		Draw.DrawShader(Screen[0], Screen[1], 20, 15, Shader, PICKUP_GUN);
	else
		Draw.DrawEngineText ( true, Screen[0], Screen[1] - 20, Draw.MenuFont, PICKUP_GUN, "%s", Engine.GetWeaponName ( Entity->WeaponID ) );
}


void cESP::FixBlindEye() { 
	client_t * pLocal = Client[CG->ClientNum];

	for(int i=0; i<18; i++) {
		if(Client[i] != pLocal) { 
			if(Client[i]->Perk & 0x20 || Client[i]->Perk & 0x40) 
				Client[i]->Perk = 0x0; 
		} 
	} 
} 
void cESP::ChopperBoxes() { 
	DWORD dwCall = Offsets.ChopperBoxes_OFFS; 
	FixBlindEye(); 
	__asm{ 
		push 0x0 
		call [dwCall]
		add esp, 0x4 
	} 
}
