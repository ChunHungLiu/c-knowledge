class cOffsets {
public:
    DWORD RefDef_OFFS;
    DWORD CG_OFFS;
    DWORD CGS_OFFS;
    DWORD ViewMatrix_OFFS;
    DWORD Entity_OFFS;
    INT Entity_Size_OFFS;
    DWORD ClientInfo_OFFS;
    INT ClientInfo_Size_OFFS;
    DWORD GetWeapon_OFFS;
    DWORD IsInGame_OFFS;
    DWORD Zoom_OFFS;
    DWORD FullBright_OFFS;
    DWORD NoFog_OFFS;
    DWORD AdvUav_OFFS;
    DWORD AdvUavCVAR_OFFS;
    DWORD DisableIngameMouse_OFFS;
    DWORD RegisterFont_OFFS;
    DWORD RegisterShader_OFFS;
    DWORD EngineText_OFFS;
    DWORD StrWidth_OFFS;
    DWORD CG_Trace_OFFS;
    DWORD GetPlayerTag_OFFS;
    DWORD RegisterTag_OFFS;
    DWORD NoRecoil_OFFS;
    DWORD GetScreenMatrix_OFFS;
    DWORD WorldToScreen_OFFS;
    DWORD UIShowList_OFFS;
    DWORD CG_Draw2D_OFFS;
    DWORD WritePacket_OFFS;
    DWORD DrawShadersOnText_OFFS;
    DWORD SendCommandToConsole_OFFS;
    DWORD DrawRotatedPic_OFFS;
    DWORD NightmareTX_NoRecoil_OFFS;
    DWORD Laser_OFFS;
	DWORD Input_OFFS;
	
	DWORD dwDVar;
	DWORD dwDVarValue;
	DWORD ExcAddy;

	DWORD R_BulletPenetrationCheckOFFS;
	DWORD R_BulletPenetrationOFFS;
	DWORD DisableImpacts;

	DWORD ChopperBoxes_OFFS;
	DWORD GetWeaponShader_OFFS;
public:
    void Initialize();
};
extern cOffsets Offsets;
