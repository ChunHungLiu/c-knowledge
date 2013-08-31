#include "main.h"

cOptions Options;

cOptions::cOptions() {
    MenuOffset[0] = 500;
    MenuOffset[1] = 5;
    MenuWidth = 400;
    MenuHeight = 250;

    ZeroMemory ( OptionsTab1, 10 );
    ZeroMemory ( OptionsTab2, 10 );

    MenuActivated = false;
    Tab1MaxOptions = 7;
    Tab2MaxOptions = 6;
    AddOption ( 0, 0, true, "Bones" );
    AddOption ( 0, 1, true, "Names" );
    AddOption ( 0, 2, true, "Weapons" );
    AddOption ( 0, 3, true, "Items" );
    AddOption ( 0, 4, true, "Distance" );
    AddOption ( 0, 5, true, "Explosives" );
    AddOption ( 0, 6, true, "3D Boxes" );
    AddOption ( 1, 0, true, "Vis. Check" );
    AddOption ( 1, 1, true, "Lasers" );
    AddOption ( 1, 2, true, "No-Recoil" );
    AddOption ( 1, 3, false, "No-Fog" );
    AddOption ( 1, 4, false, "FullBright" );
    AddOption ( 1, 5, true, "Adv. Uav" );

}

void cOptions::AddOption ( int Tab, int Index, bool Active, char* Label ) {
    if ( Tab == 0 ) {
        OptionsTab1[Index].Active = Active;
        OptionsTab1[Index].Label = Label;
    } else if ( Tab == 1 ) {
        OptionsTab2[Index].Active = Active;
        OptionsTab2[Index].Label = Label;
    }
}

BYTE* IsMouseEnabled;
int MouseX;
int MouseY;

void cOptions::DrawMenu() {
    IsMouseEnabled = ( BYTE* ) Offsets.DisableIngameMouse_OFFS;
    if ( GetAsyncKeyState ( VK_INSERT ) & 1 ) {
        if ( !MenuActivated ) {
            *IsMouseEnabled = 0;
			MouseX = Mouse.x;
			MouseY = Mouse.y;
            MenuActivated = true;
        } else {

            *IsMouseEnabled = 1;
			Mouse.x = MouseX;
			Mouse.y = MouseY;
            MenuActivated = false;
        }
    }

    if ( !MenuActivated ) {
        Draw.DrawGradientButton ( MenuOffset[0], MenuOffset[1], MenuWidth, 20, MENUWINDOWBORDER, BLACK, Separator, "Press Insert To Display the Menu" );
        return;
    } else {
        DrawBGBox();

        Draw.DrawGradientButton ( MenuOffset[0], MenuOffset[1], MenuWidth, 20, MENUWINDOWBORDER, BLACK, Separator, "-InSaNe-'s Universal ESP" );
        DrawMouse();
    }
}

bool cOptions::GetOption ( char* Op ) {
    for ( int i = 0; i < Tab1MaxOptions; i++ ) {
        if ( strcmp ( Op, OptionsTab1[i].Label ) == 0 )
            return OptionsTab1[i].Active;
    }
    for ( int i = 0; i < Tab2MaxOptions; i++ ) {
        if ( strcmp ( Op, OptionsTab2[i].Label ) == 0 )
            return OptionsTab2[i].Active;
    }
    return false;
}

bool First = true;
void GetMousePos ( POINT* Mouse ) {
    GetCursorPos ( Mouse );
    RECT rcClient;
    HWND Window = FindWindow ( L"IW5", NULL );
    GetClientRect ( Window, &rcClient );
    ScreenToClient ( Window, Mouse );
    float XCorr = 1;
    float YCorr = 1;

    if ( First ) {
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
    }
    Mouse->x /= XCorr;
    Mouse->y /= YCorr;
}
void cOptions::DrawMouse() {
    GetMousePos ( &Mouse );

    Draw.DrawRotatedShader ( ( float ) Mouse.x, ( float ) Mouse.y, 25, 25, -45.0f, "compassping_player", RED );
    int Box = BoxClicked ( Mouse );
    if ( GetAsyncKeyState ( 1 ) & 1 ) {
        if ( Box != -1 ) {
            if ( Box <= Tab1MaxOptions ) {
                OptionsTab1[Box-1].Active = !OptionsTab1[Box-1].Active;
            } else if ( Box >= Tab1MaxOptions ) {
                OptionsTab2[Box-8].Active = !OptionsTab2[Box-8].Active;
            }
        }

    }
}

void cOptions::DrawBGBox() {


    Draw.DrawFilledBox ( MenuOffset[0], MenuOffset[1], MenuWidth, MenuHeight, MENUWINDOW );

    Draw.DrawLine ( ( MenuOffset[0] * 2 + MenuWidth ) / 2, MenuOffset[1] + 30, ( MenuOffset[0] * 2 + MenuWidth ) / 2, MenuOffset[1] + MenuHeight - 10, Separator, 1 );

    Draw.DrawGradientButton ( MenuOffset[0] + 75, MenuOffset[1] + 30, 60, 20, MENUWINDOWBORDER, BLACK, Separator, "ESP" );
    for ( int i = 0; i < Tab1MaxOptions; i++ ) {
        Draw.DrawEngineText ( false, MenuOffset[0] + 20, ( MenuOffset[1] + 75 ) + i * 20, Draw.MenuFont, WHITE, OptionsTab1[i].Label );
        Draw.DrawBox ( MenuOffset[0] + 150, ( MenuOffset[1] + 60 ) + i * 20, 15, 15, Separator, 1 );
        if ( OptionsTab1[i].Active )
            Draw.DrawFilledBox ( MenuOffset[0] + 151, ( MenuOffset[1] + 62 ) + i * 20, 12, 12, DARKGREEN );
    }
    Draw.DrawGradientButton ( ( ( MenuOffset[0] * 2 + MenuWidth ) / 2 ) + 75, MenuOffset[1] + 30, 60, 20, MENUWINDOWBORDER, BLACK, Separator, "Misc" );
    for ( int i = 0; i < Tab2MaxOptions; i++ ) {
        Draw.DrawEngineText ( false, ( ( MenuOffset[0] * 2 + MenuWidth ) / 2 ) + 20, ( MenuOffset[1] + 75 ) + i * 20, Draw.MenuFont, WHITE, OptionsTab2[i].Label );
        Draw.DrawBox ( ( ( MenuOffset[0] * 2 + MenuWidth ) / 2 ) + 150, ( MenuOffset[1] + 60 ) + i * 20, 15, 15, Separator, 1 );
        if ( OptionsTab2[i].Active )
            Draw.DrawFilledBox ( ( ( MenuOffset[0] * 2 + MenuWidth ) / 2 ) + 151, ( MenuOffset[1] + 62 ) + i * 20, 12, 12, DARKGREEN );
    }
}

int cOptions::BoxClicked ( tagPOINT Mouse ) {
    int OpX1 = MenuOffset[0] + 145;
    int OpX2 = ( ( MenuOffset[0] * 2 + MenuWidth ) / 2 ) + 145;
    int OpY = MenuOffset[1] + 60;


    if ( Mouse.x > OpX1 && Mouse.x < OpX1 + 10 ) //tab1
        if ( Mouse.y > OpY && Mouse.y < MenuOffset[1] + 27 * Tab1MaxOptions ) {
            for ( int i = 0; i < 130; i += 20 )
                if ( Mouse.y > OpY + i && Mouse.y < OpY + i + 10 )
                    return i / 20 + 1;
        }
    if ( Mouse.x > OpX2 && Mouse.x < OpX2 + 10 ) { //tab2
        for ( int i = 0; i < 110; i += 20 )
            if ( Mouse.y > OpY + i && Mouse.y < OpY + i + 10 )
                return i / 20 + 1 + 7;
    }
    return -1;
}
