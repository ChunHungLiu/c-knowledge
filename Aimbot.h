class Aim {
public:
	int Frame;
	int FrameShot;

	Aim(){ Frame = 0, FrameShot = 0; }

    void Initialize(bool Zoom, bool Wall, bool Shoot);
	void AutoShoot();
};

extern Aim Aimbot;
