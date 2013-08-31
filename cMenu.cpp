#include "main.h"

Tab::Tab(int NumberOfOptions){
	this->NumberOfOptions = NumberOfOptions;
	//Options = (Option*)malloc(NumberOfOptions * sizeof(Option));
}

void Tab::AddOption(int Index, char* Label, bool Active){
	
	Options[Index].Label = Label;
	Options[Index].Active = Active;
}

cMenu::cMenu(int NumberOfTabs){
	this->NumberOftabs = NumberOfTabs;
	Tabs = (Tab*)malloc(NumberOfTabs * sizeof(Tab));
}

void cMenu::AddTab(int Index, char* Label, bool Active){
	Tabs[Index].Active = Active;
	Tabs[Index].Label = Label;
}

void GetMousePos(POINT* Mouse){
	GetCursorPos ( Mouse );
    RECT rcClient;
    HWND Window = FindWindow ( L"IW5", NULL );
    GetClientRect ( Window, &rcClient );
    ScreenToClient ( Window, Mouse );
    float XCorr = 1;
    float YCorr = 1;

    //if ( First ) {
        if ( rcClient.bottom == 768 ) {
            YCorr = 1.07f;
        } else if ( rcClient.bottom == 864 ) {
            YCorr = 1.2f;
        } else if ( rcClient.bottom == 884 ) {
            YCorr = 1.265;
        }
        if ( rcClient.right == 1360 || rcClient.right == 1366 ) {
            XCorr = 1.07;
        } else if ( rcClient.right == 1440 ) {
            XCorr = 1.13;
        } else if ( rcClient.right == 1600 ) {
            XCorr = 1.262;
        }
   // }
    Mouse->x /= XCorr;
    Mouse->y /= YCorr;
}

bool cMenu::IsOptionActive(int tab, char* Option){
	for(int i = 0; i < Tabs[tab].NumberOfOptions; i++){
		if(strcmp(Tabs[tab].Options[i].Label, Option) == 0)
			return Tabs[tab].Options[i].Active;
	}
	return false;
}

bool cMenu::IsMouseOverTab(int Tab){
	POINT Mouse;
	GetMousePos(&Mouse);
	
	MyRect TabPos = {Position.x + 20, (Position.y + 25) + Tab * 40, Position.w - 30, 30 };

	return (Mouse.x >= TabPos.x && Mouse.x <= TabPos.x + TabPos.w && Mouse.y >= TabPos.y && Mouse.y <= TabPos.y + TabPos.h);
}

bool cMenu::IsMouseOverOption(int Tab, int Option){
	POINT Mouse;
	GetMousePos(&Mouse);
	MyRect OptionPos = {Position.x + Position.w, ((Position.y + 25) + Tab * 40) + Option * 20, 150, 15};

	return (Mouse.x >= OptionPos.x && Mouse.x <= OptionPos.x + OptionPos.w && Mouse.y >= OptionPos.y && Mouse.y <= OptionPos.y + OptionPos.h);
}

void DrawMouse(){
	POINT Mouse;
	GetMousePos(&Mouse);
	Draw.DrawRotatedShader ( ( float ) Mouse.x, ( float ) Mouse.y, 25, 25, -45.0f, "compassping_player", MENU_MOUSE );
}

BYTE* IsMouseEnabled;
void cMenu::DrawMenu(){
	IsMouseEnabled = ( BYTE* ) Offsets.DisableIngameMouse_OFFS;
	if ( GetAsyncKeyState ( VK_INSERT ) & 1 || GetAsyncKeyState ( VK_DELETE ) & 1  ) {
        if ( !MenuActive ) {
            *IsMouseEnabled = 0;

            MenuActive = true;
        } else {

            *IsMouseEnabled = 1;

            MenuActive = false;
        }
    }

	if(!MenuActive) return;
	
	Draw.DrawFilledBox(Position.x, Position.y+20, Position.w, NumberOftabs * 40, MENU_BG);
	Draw.DrawGradientButton(Position.x, Position.y, Position.w , 20, MENU_TOPBAR_COLOR1, MENU_TOPBAR_COLOR2, MENU_FONT, "MW3 -InSaNe-'s ESP");
	for(int i = 0; i < NumberOftabs; i++)
		if(IsMouseOverTab(i) || Tabs[i].Active)
			Draw.DrawFilledBox(Position.x, (Position.y + 20) + i * 40, Position.w, 40, MENU_SEL_OPTION);
	for(int i = 0; i < NumberOftabs; i++){
		Draw.DrawGradientButton(Position.x + 20, (Position.y + 25) + i * 40, Position.w - 30, 30, MENU_BUTTON_COLOR1, MENU_BUTTON_COLOR2, MENU_FONT, Tabs[i].Label);
		if(Tabs[i].Active && i < NumberOftabs - 1){
			Draw.DrawFilledBox(Position.x + Position.w, (Position.y + 20) + i * 40, 150, Tabs[i].NumberOfOptions * 20 + 5, MENU_SUBMENU_BG);
			for(int j = 0; j < Tabs[i].NumberOfOptions; j++){
				if(IsMouseOverOption(i,j))
					Draw.DrawFilledBox(Position.x + Position.w, ((Position.y + 23) + i * 40) + j * 20, 150, 20, MENU_SEL_OPTION);
				Draw.DrawBox(Position.x + Position.w + 5, ((Position.y + 25) + i * 40) + j * 20, 15, 15, GRAY, 1);
				Draw.DrawEngineText(false, Position.x + Position.w + 25, ((Position.y + 40) + i * 40) + j * 20, Draw.MenuFont,  MENU_FONT, Tabs[i].Options[j].Label);
				if(Tabs[i].Options[j].Active)
					Draw.DrawFilledBox(Position.x + Position.w + 6, ((Position.y + 26) + i * 40) + j * 20, 12, 12, MENU_CHECKBOX);
			}
		}
	}
	
	if(GetAsyncKeyState(1) & 0x1){
		for(int i = 0; i < NumberOftabs; i++){
			if(IsMouseOverTab(i)){
				for(int j = 0; j < NumberOftabs; j++){
					if(j == i && !Tabs[j].Active)
						Tabs[j].Active = true;
					else
						Tabs[j].Active = false;
				}
			}else{
				if(Tabs[i].Active){
					for(int j = 0; j < Tabs[i].NumberOfOptions; j++){
						if(IsMouseOverOption(i,j)){
							Tabs[i].Options[j].Active = !Tabs[i].Options[j].Active;
						}
					}
				}
			}
		}
	}
	WhiteList(Tabs[NumberOftabs - 1].Active);
	DrawMouse();
}

void cMenu::WhiteList(bool Enabled){ //This is for a whitelist that I was doing.. got banned before finishing it...
	if(!Enabled || Engine.IsInGame == 0) return;

	int i = 0;
	for(i = 0; i < CGS->MaxClients; i++)
		if(Entity[i]->Type != ET_PLAYER) break;

	Draw.DrawFilledBox(RefDef->Width - 200, 35, 200, i * 20, MENU_BG);
	Draw.DrawGradientButton(RefDef->Width - 200, 15, 200 , 20, MENU_TOPBAR_COLOR1, MENU_TOPBAR_COLOR2, MENU_FONT, "WhiteList");
	float* cor;
	for(int j = 0; j < i; j++){

		if(Entity[j]->Type != ET_PLAYER) break;

		cor = Engine.MyTeam != Client[j]->Team ? RED : GREEN;

		if(CG->ClientNum == Entity[i]->ClientNum)
			cor = BLUE;

		Draw.DrawBox(RefDef->Width - 195, 40 + j * 20, 15, 15, GRAY, 1);
		Draw.DrawEngineText(false,RefDef->Width - 170, 50 + j * 20, Draw.MenuFont, cor, Client[j]->Name);
	}
}