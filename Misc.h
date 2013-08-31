class cMisc {

public:
    int GetFPS();
    void Laser ( bool Enabled );
    void NoRecoil ( bool Enabled );
    void NoFog ( bool Enabled );
    void FullBright ( bool Enabled );
    void AdvUav ( bool Enabled );
	void Crosshair ( bool Enabled );
	void AutoC4(entity_t* Ent);
	void ThermalOverlay(bool Enabled);
};

extern cMisc Misc;
