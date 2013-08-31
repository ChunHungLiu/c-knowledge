#include "main.h"

Drawing Draw;

int Drawing::StrWidth ( void* Font, int a1, int a2, char* szString, ... ) {
    char szBuf[300] = "";
    va_list valist;

    va_start ( valist, szString );
    _vsnprintf_s ( szBuf, sizeof ( szBuf ), szString, valist );
    va_end ( valist );

    return Engine.StrWidth_ ( szBuf, a1, Font, a2 );
}
#define TEXT_NORMAL 1
#define TEXT_SHADOWED 3

void Drawing::DrawEngineText ( bool center, int x, int y, void* Font, float* color, const char* Text, ... ) {
    char buf[300] = "";
    va_list va_alist;
    va_start ( va_alist, Text );
    vsnprintf ( buf, sizeof ( buf ), Text, va_alist );
    va_end ( va_alist );
    if ( !center )
        Engine.DrawEngineText_ ( buf, strlen ( buf ), Font, x, y, 0.8f, 1.0f, 0, color, TEXT_SHADOWED );
    else
        Engine.DrawEngineText_ ( buf, strlen ( buf ), Font, x - StrWidth ( Font, 0.8f, 0.8f, buf ) / 2 + 5, y, 0.8f, 1.0f, 0, color, TEXT_SHADOWED );
}

void Drawing::DrawFilledBox ( int x, int y, int w, int h, float* color ) {
    ScreenMatrix* ptr = Engine.GetScreenMatrix();

    Engine.DrawRotatedPic_ ( ptr, x, y, w, h, 0, color, Shader );
}

void Drawing::DrawLine ( int x1, int y1, int x2, int y2, float* color, int size ) {
    ScreenMatrix* ptr = Engine.GetScreenMatrix();

    float x, y, angle, l1, l2, h1;
    h1 = y2 - y1;
    l1 = x2 - x1;
    l2 = sqrt ( l1 * l1 + h1 * h1 );
    x = x1 + ( ( l1 - l2 ) / 2 );
    y = y1 + ( h1 / 2 );
    angle = ( float ) atan ( h1 / l1 ) * ( 180 / 3.14159265358979323846 ) ;

    Engine.DrawRotatedPic_ ( ptr, x, y, l2, size, angle, color, Shader );
}

void Drawing::DrawBox ( int x, int y, int w, int h, float* color, int Size ) {
    DrawLine ( x, y, x + w, y, color, Size );
    DrawLine ( x + w, y, x + w, y + h, color, Size );
    DrawLine ( x + w, y + h, x, y + h, color, Size );
    DrawLine ( x, y + h, x, y, color, Size );
}


int Drawing::GetBoxWidth ( entity_t* Ent ) {
    if ( Ent->Flags & FL_PRONE )
        return 65;
    else
        return 20;
}

int Drawing::GetBoxHeight ( entity_t* Ent ) {
    if ( Ent->Flags & FL_CROUCH )
        return 40;
    else if ( Ent->Flags & FL_PRONE )
        return 20;
    else
        return 65;
}

void Drawing::Make3DBox ( float center[3], float w, float h, float* color ) {
    //bottom
    DrawESPLine ( center, -w, -w, 0, w, -w, 0, color );
    DrawESPLine ( center, -w, -w, 0, -w, w, 0, color );
    DrawESPLine ( center, w, w, 0, w, -w, 0, color );
    DrawESPLine ( center, w, w, 0, -w, w, 0, color );

    //middle
    DrawESPLine ( center, -w, -w, 0, -w, -w, h, color );
    DrawESPLine ( center, -w, w, 0, -w, w, h, color );
    DrawESPLine ( center, w, -w, 0, w, -w, h, color );
    DrawESPLine ( center, w, w, 0, w, w, h, color );

    //top
    DrawESPLine ( center, -w, -w, h, w, -w, h, color );
    DrawESPLine ( center, -w, -w, h, -w, w, h, color );
    DrawESPLine ( center, w, w, h, w, -w, h, color );
    DrawESPLine ( center, w, w, h, -w, w, h, color );
}

void Drawing::DrawESPLine ( float center[3], float x1, float y1, float z1, float x2, float y2, float z2, float* color ) {
    float pointPos1[3] = {center[0] + x1, center[1] + y1, center[2] + z1};
    float pointPos2[3] = {center[0] + x2, center[1] + y2, center[2] + z2};
    float xy1[2], xy2[2];
    ScreenMatrix* calc = Engine.GetScreenMatrix();
    if ( Engine.WorldToScreen ( 0, calc, pointPos1, xy1 ) && Engine.WorldToScreen ( 0, calc, pointPos2, xy2 ) )
        DrawLine ( xy1[0], xy1[1], xy2[0], xy2[1], color, 1 );
}

void Drawing::DrawShaderWithText ( int x, int y, char* Shader, char* Text, Color c ) {

    static int* icon = Engine.RegisterShader_ ( Shader );

    char Buf[512];
    sprintf ( Buf, "%s", Engine.GetIconText ( icon, 3.f, 1.8f, TRUE ) );

    DrawEngineText ( false, x, y, Draw.MenuFont, c, Buf );
}

void Drawing::DrawShader ( int x, int y, int h, int w, char* S, float* color ) {

    int* icon = Engine.RegisterShader_ ( S );
	if(w == NULL) w = h;
    Engine.DrawRotatedPic_ ( Engine.GetScreenMatrix(), x, y, w*1.8, h, 0, color, icon );
}

void Drawing::DrawRotatedShader ( float x, float y, int w, int h, float angle, char* Shader, float* color ) {
    static int* icon = Engine.RegisterShader_ ( Shader );

    Engine.DrawRotatedPic_ ( Engine.GetScreenMatrix(), x, y, w, h, angle, color, icon );
}

void Drawing::DrawGradientButton ( int x, int y, int w, int h, Color A, Color B, Color ctext, char* Text ) {
    DrawFilledBox ( x, y, w, h, A );
    Color Grad;
    Math.VectorCopy ( B, Grad );
    for ( int i = 0; i < h; i++ ) {
        Grad[3] = ( float ) i / 50;
        if ( ( y + h / 2 - h / 4 ) + i >= y + h ) break;
        DrawFilledBox ( x, ( y + h / 2 - h / 4 ) + i, w , 2, Grad );
    }
    DrawEngineText ( true, x + w / 2, (y + h / 1.2)-2, Draw.MenuFont, ctext, Text );
}
