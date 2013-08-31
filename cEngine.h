typedef ScreenMatrix* ( __cdecl* tGetScreenMatrix ) ();
typedef void* ( *tRegisterFont ) ( char* szName );
typedef int ( *R_RegisterTag ) ( char* szName );
typedef int* ( *R_RegisterShader ) ( char* szName );
typedef int ( * tDrawEngineText ) ( char* Text, int NumOfChars, void* Font, float X, float Y, float scaleX, float scaleY, float unk1, float* Color, int unk2 );
typedef int ( *CG_StrWidth ) ( char* szText, int a2, void* lpFont, int a4 );
typedef void ( __cdecl* CG_Trace_t ) ( Trace_T* tr, float start[3], float endpos[3], int Skip, int mask ); // ( Trace_T* tr, float* start, float* NullVec, float* endpos, int Skip, int mask );
typedef bool ( *World2Screen_ ) ( int unknown, ScreenMatrix* w2scalc, float* vPoint, float Screen[2] );
typedef int ( __cdecl* tDrawRotatedPic ) ( ScreenMatrix* ptr, float x, float y, float w, float h, float angle, float* color, int* shader );
typedef void ( __cdecl* tUiShowList ) ( int a1, int a2, int a3, int a4 );
typedef int ( __cdecl* tDraw2D ) ( int a1 );
typedef int (__cdecl* tWritepacket) (int a1);
typedef int ( __cdecl* StrechPic ) ( float x, float y, float w, float h, float a5, float a6, float a7, float a8, float* color, int* shader );

static char* Bones[20] = {
    /*Head*/          "j_helmet"     , "j_head"            , "j_neck"
    /*Arms*/        , "j_shoulder_le", "j_shoulder_ri"  , "j_elbow_le"     , "j_elbow_ri", "j_wrist_le", "j_wrist_ri", "j_gun"
    /*Back*/        , "j_mainroot"   , "j_spineupper"   , "j_spinelower" , "j_spine4"
    /*Legs*/        , "j_hip_ri"     , "j_hip_le"       , "j_knee_le"    , "j_knee_ri" , "j_ankle_ri", "j_ankle_le"
};
class cEngine {
public:
    tRegisterFont RegisterFont_;
    tDrawEngineText DrawEngineText_;
    R_RegisterShader RegisterShader_;
    tGetScreenMatrix GetScreenMatrix;
    tDrawRotatedPic DrawRotatedPic_;
    CG_Trace_t CG_Trace_;
    R_RegisterTag GetTagByName;
    World2Screen_ WorldToScreen;
    CG_StrWidth StrWidth_;
    tUiShowList UiShowList;
    tDraw2D Draw2D;
	tWritepacket WritePacket;
    StrechPic DrawStretchPic;
	Input_t* Input;

	BulletTrace_T* bulletTrace;

    char GameVersion[20];
    int* IsInGame;
    int MyTeam;

    void Initialize();
    bool GetTagPos ( entity_t* pEnt, char* szTag, float* flOut );
    bool CG_Trace ( float* Start, float* End, entity_t* Ent, bool AutoWallOn );
    DWORD GetWeaponPointer ( int iWeaponID );
    weapon_t* GetWeapon ( int iWeaponID );
    char* GetWeaponName ( int iWeaponID );
	char* GetWeaponShader(DWORD dwNum);

    int AddIconToText ( int startLen, int* shader, char* text, float iconW, float iconH, BOOL flipIconHorizontal );
    char* GetIconText ( int* shader, float iconW, float iconH, BOOL flipIconHorizontal );
	void SendCommandToConsole ( char* Cmd );
	BOOL ExecuteAction( CONST PCHAR Action );
	bool BulletPenetrationCheck ( BulletTrace_T* MapTrace );
	void BulletPenetration ( int unk1, BulletTrace_T* bulletTrace, int WeaponNum, int unk2, entity_t* cent, int unk3, float vieworg[3], int unk4 );
	bool GetRemainingIndex ( float vieworg[3], entity_t* TargetEnt, float origin[3] );
};
extern cEngine Engine;

extern cg_t* CG;
extern cgs_t* CGS;
extern refdef_t* RefDef;
extern viewMatrix_t* ViewMatrix;
extern entity_t* Entity[ENTITIESMAX];
extern client_t* Client[PLAYERSMAX];
