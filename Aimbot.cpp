#include "main.h"

Aim Aimbot;
static long Frames = 0;
int FrameRate;
int LastFrameShot;
void Aim::Initialize(bool Zoom, bool Wall, bool Shoot) {
   
    if (*Engine.IsInGame == 0 ) return;

	entity_t* pCurEnt	= NULL;
    entity_t* pBestEnt = NULL;
	client_t* pCurClient = NULL;
    float CurrentDistance = 0.0f;
    int TargetClientNum = -1;
    bool isAiming = false;
    float ClosestDistance = 9999.9f;
	Vector CurBone, BestBone;

    for ( int i = 0; i < PLAYERSMAX; i++ ) {
        if ( Entity[i]->Type != ET_PLAYER )
            continue;
		if ( ( Entity[i]->IsAlive & 1 ) && Entity[i]->Valid && CG->ClientNum != Entity[i]->ClientNum && (strcmp(Engine.GetWeaponName(Entity[i]->WeaponID), "RIOT") != 0)){
			
			if ( ( ( Client[i]->Team == 1 ) || ( Client[i]->Team == 2 ) ) && ( Client[i]->Team == Engine.MyTeam ) ) continue; //Same team
			for(int j = 0; j < 10; j++){
				Engine.GetTagPos ( Entity[i], Bones[j+1], CurBone );
			
				if ( Engine.CG_Trace ( RefDef->ViewOrg, CurBone, Entity[i], Wall ) ) {
					CurrentDistance = Math.GetDistance ( RefDef->ViewOrg, CurBone );
					if ( CurrentDistance < ClosestDistance ) {
						ClosestDistance = CurrentDistance;
						BestBone[0] = CurBone[0];
						BestBone[1] = CurBone[1];
						BestBone[2] = CurBone[2];
						pBestEnt = Entity[i];
						TargetClientNum	= i;
						isAiming = true;
					}
					break;
				}
			}
		}

    }
    if ( TargetClientNum != -1 && ( pBestEnt->IsAlive & 1 ) && pBestEnt->Valid ){
        float BoneVecCalc[3], VecAngle[3];
		Math.VectorSubtract ( BestBone, RefDef->ViewOrg, BoneVecCalc );

		Math.VectorAngles ( BoneVecCalc , VecAngle );

		ViewMatrix->SetViewAngleY += ( VecAngle[ 0 ] -= RefDef->ViewAngles[0] ) ;
		ViewMatrix->SetViewAngleX += ( VecAngle[ 1 ] -= RefDef->ViewAngles[1] ) ;

		if(Zoom)
			*(BYTE*)Offsets.Zoom_OFFS = 1;
		if(Shoot)
			AutoShoot();
	}
	Frame++;
}


void Aim::AutoShoot(){
	if(Frame - FrameShot > 5){
		Engine.Input->Weapon.Pressed = 0;
		FrameShot = Frame;
	}else{
		Engine.Input->Weapon.Pressed = 1;
	}
}
