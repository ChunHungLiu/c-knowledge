static Color BONES_ENEMY = {1,0,0,1};
static Color BONES_ENEMY_VISIBLE = {1,1,0,1};
static Color BOX_ENEMY = {1,0,0,1};
static Color BOX_ENEMY_VISIBLE = {1,1,0,1};
static Color ENEMY_GUN = {1,0,0,1};
static Color FRIEND_GUN = {0,1,0,1};
static Color BONES_FRIEND = {0,1,0,1};
static Color ENEMY_NAME = {1,0,0,1};
static Color FRIEND_NAME = {0,1,0,1};
static Color ENEMY_DIST = {1,0,0,1};
static Color FRIEND_DIST = {0,1,0,1};

static Color PICKUP_GUN = {0.11,0.60,1,1};
static Color CROSSHAIR = {1,0,0,1};

static Color MENU_BG = {0,0,0,0.7};
static Color MENU_BUTTON_COLOR1 = {0.80,0,0,1};
static Color MENU_BUTTON_COLOR2 = {0,0,0,1};
static Color MENU_SEL_OPTION = {0,1,0,0.7};
static Color MENU_SUBMENU_BG = {0,0,0,0.7};
static Color MENU_CHECKBOX = {0,1,0,1};
static Color MENU_FONT = {1,1,1,1};
static Color MENU_TOPBAR_COLOR1 = {0,0,0.8f,1};
static Color MENU_TOPBAR_COLOR2 = {0,0,0,1};
static Color MENU_MOUSE = {0,0,1,1};
static Color GRAY = {0.65, 0.65, 0.65, 1};
static Color WHITE = {1,1,1,1};
static Color BLUE = {0,0,1,1};
static Color GREEN = {0,1,0,1};
static Color RED = {1,0,0,1};

class Drawing {

private:
    int StrWidth ( void* Font, int a1, int a2, char* szString, ... );
public:

    void DrawEngineText ( bool center, int x, int y, void* Font, float* color, const char* Text, ... );
    void DrawFilledBox ( int x, int y, int w, int h, float* color );
    void DrawLine ( int x1, int y1, int x2, int y2, float* color, int size );
    void DrawBox ( int x, int y, int w, int h, float* color, int Size );
    void DrawESPLine ( float center[3], float x1, float y1, float z1, float x2, float y2, float z2, float* color );
    void Make3DBox ( float center[3], float w, float h, float* color );
    void DrawShaderWithText ( int x, int y, char* Shader, char* Text, Color c );
    void DrawShader ( int x, int y,int h, int w, char* Shader, float* color );
    void DrawRotatedShader ( float x, float y, int w, int h, float angle, char* Shader, float* color );
    void DrawGradientButton ( int x, int y, int w, int h, Color A, Color B, Color ctext, char* Text );
    int GetBoxHeight ( entity_t* Ent );
    int GetBoxWidth ( entity_t* Ent );

    void* MenuFont;
    void* NamesFont;
    int* Shader;

};

extern Drawing Draw;
