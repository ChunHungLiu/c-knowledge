class cESP {
public:

    void DrawBones ( entity_t* Entity, client_t* Client, bool IsVisible );
    void DrawNames ( entity_t* Entity, client_t* Client, float* Screen );
    void DrawDistance ( entity_t* Entity, client_t* Client, float* Screen );
    void Draw3DBox ( entity_t* Entity, client_t* Client, Vector BonePos, bool IsVisible );
	//void GetWeaponShader(char* WeaponName);
    void DrawWeaponsNames ( entity_t* Entity, client_t* Client, float* Screen );
	void DrawItems ( entity_t* Entity, client_t* Client, float* Screen );
	void FixBlindEye();
	void ChopperBoxes();

};

extern cESP ESP;
