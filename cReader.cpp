#include "main.h"

bool cReader::OpenFile(const char* FileName) {
    File = fopen ( FileName, "r" );
    if ( File == NULL ) return false;
    else return true;
}

char* cReader::strtrim ( const char* str ) {
    char* newStr = ( char* ) malloc ( MAXLINELENGHT );
    int j = 0;
    for ( int i = 0; i < strlen ( str ); i++ ) {
        if ( str[i] != ' ' ) {
            newStr[j] = str[i];
            j++;
        }
    }
    newStr[j] = '\0';
    return newStr;
}

void cReader::ReadFile() {
    char* CurrentLine = ( char* ) malloc ( MAXLINELENGHT );
    int LineNumber = 0;
    for ( int i = 0; i < MAXLINES; i++ ) memset ( Content[i], NULL, sizeof ( Content[i] ) );
    while ( !feof ( File ) ) {
        fgets ( CurrentLine, MAXLINELENGHT, File );
        if ( CurrentLine[0] != '/' &&  CurrentLine[0] != '\n' ) { //Not Commented/Skipped line
            CurrentLine = strtrim ( CurrentLine );
            strcpy ( Content[LineNumber], CurrentLine );
            LineNumber++;
        }
    }
    free ( CurrentLine );
    fclose ( File );
}

void cReader::PrintReadContent() { //Just for debug stuff :D
    for ( int i = 0; i < MAXLINES; i++ )
        printf ( "%s", Content[i] );
}

char* cReader::GetValueFromLine ( int Line ) {
    bool Found = false;
    char* Value = ( char* ) malloc ( MAXLINELENGHT );
    int j = 0;
    for ( int i = 0; i < MAXLINELENGHT; i++ ) {
        if ( Found ) {
            Value[j] = Content[Line][i];
            j++;
            if ( Content[Line][i] == '\n' ) break;
        }
        if ( Content[Line][i] == '=' && !Found ) Found = true;
    }
    Value[j] = '\0';
    return Value;
}

char* cReader::GetFieldValue ( const char* Field ) {
    char* _return;
    char Error[256];
    for ( int i = 0; i < MAXLINES; i++ ) {
        if ( strstr ( Content[i], Field ) != NULL )
            return _return = GetValueFromLine ( i );
    }
    sprintf ( Error, "The Line %s wasn't found on the config file.\nPlease, delete the config file. If the problem continue, post on the hack thread.", Field );
	exit(1);
    return NULL;
}

int cReader::HexToInt ( char c ) {
    if ( c >= '0' && c <= '9' ) return c - 48;
    else if ( c >= 'A' && c <= 'F' ) return 10 + ( c - 65 );
    else return -1;
}

DWORD cReader::GetHexColorFromString ( const char* ColorString ) {
    DWORD Color = 0;
    for ( int i = 2; i < 10; i++ )
        Color |= ( HexToInt ( ColorString[i] ) & 0xff ) << ( 28 - 4 * ( i - 2 ) );
    return Color;
}

void cReader::GetFloatColorFromString ( const char* ColorString, Color ColorRet ) {
    int Alpha, Red, Green, Blue;

    Alpha = Red = Green = Blue = 0;

    //Get Alpha Channel Value
    for ( int i = 2; i <  4; i++ )
        Alpha |= ( HexToInt ( ColorString[i] ) & 0xff ) << ( 4 - 4 * ( i - 2 ) );
    for ( int i = 4; i <  6; i++ )
        Red   |= ( HexToInt ( ColorString[i] ) & 0xff ) << ( 4 - 4 * ( i - 4 ) );
    for ( int i = 6; i <  8; i++ )
        Green |= ( HexToInt ( ColorString[i] ) & 0xff ) << ( 4 - 4 * ( i - 6 ) );
    for ( int i = 8; i < 10; i++ )
        Blue  |= ( HexToInt ( ColorString[i] ) & 0xff ) << ( 4 - 4 * ( i - 8 ) );

    ColorRet[0] = ( double ) Red   / 255;
    ColorRet[1] = ( double ) Green / 255;
    ColorRet[2] = ( double ) Blue  / 255;
    ColorRet[3] = ( double ) Alpha / 255;
}

void cReader::HexColorToFloat ( DWORD C, Color ColorRet ) {

    int Alpha, Red, Green, Blue;

    Alpha = ( C >> 24 );
    Red   = ( C >> 16 ) & 0xff;
    Green = ( C >>  8 ) & 0xff;
    Blue  = ( C ) & 0xff;

	ColorRet[0] = ( double ) Red   / 255;
    ColorRet[1] = ( double ) Green / 255;
    ColorRet[2] = ( double ) Blue  / 255;
    ColorRet[3] = ( double ) Alpha / 255;
}

void cReader::CreateNewConfigFile(const char* FileName) {
    File = fopen ( FileName, "w" );
    
    fclose ( File );
}
