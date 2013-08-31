#include "main.h"

Scanner Scan;

BOOL Scanner::Match ( const BYTE* pData, const BYTE* bMask, const char* szMask ) {
    for ( ; *szMask; ++szMask, ++pData, ++bMask )
        if ( *szMask == 'x' && *pData != *bMask )
            return false;
    return ( *szMask ) == NULL;
}

DWORD Scanner::FindPattern ( char* szSig, char* szMask ) {
    DWORD dwAddress = ( DWORD ) GetModuleHandleA ( NULL );
    DWORD dwLen = GetModuleInfo ( NULL ).SizeOfImage;

    for ( DWORD i = 0; i < dwLen; i++ )
        if ( Match ( ( BYTE* ) ( dwAddress + i ), ( BYTE* ) szSig, szMask ) )
            return ( DWORD ) ( dwAddress + i );

    return 0;
}

DWORD Scanner::FindPattern ( DWORD dwAddress, DWORD dwLen, char* bMask, char* szMask ){
	for ( DWORD i = 0; i < dwLen; i++ )
        if ( Match ( ( BYTE* ) ( dwAddress + i ), ( BYTE* ) bMask, szMask ) )
            return ( DWORD ) ( dwAddress + i );

    return 0;
}
