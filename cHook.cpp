#include "main.h"

cHook Hook;

void* cHook::DetourFunction ( BYTE* src, const BYTE* dst, const int len ) {
    BYTE* jmp = ( BYTE* ) malloc ( len + 5 );
    DWORD dwBack;

	//Basic Virtual protect...
    VirtualProtect ( src, len, PAGE_EXECUTE_READWRITE, &dwBack );

	//Copy the bytes from src to the jump position...
    memcpy ( jmp, src, len );

    jmp += len;

	//Write the JMP
    jmp[0] = 0xE9;

	//Write the position to where we're gonna jump
    * ( DWORD* ) ( jmp + 1 ) = ( DWORD ) ( src + len - jmp ) - 5;

    src[0] = 0xE9;
    * ( DWORD* ) ( src + 1 ) = ( DWORD ) ( dst - src ) - 5;

	//Fill the rest of the bytes with NOPs
    for ( int i = 5; i < len; i++ )
        src[i] = 0x90;

	//Restore the permissions
    VirtualProtect ( src, len, dwBack, &dwBack );

    return ( jmp - len );

}


void cHook::MakeJMP ( BYTE* pAddress, DWORD dwJumpTo, DWORD dwLen ) {
    DWORD dwOldProtect, dwBkup, dwRelAddr;

    VirtualProtect ( pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect );

    dwRelAddr = ( DWORD ) ( dwJumpTo - ( DWORD ) pAddress ) - 5;

    *pAddress = 0xE9;

    * ( ( DWORD * ) ( pAddress + 0x1 ) ) = dwRelAddr;

    for ( DWORD x = 0x5; x < dwLen; x++ ) * ( pAddress + x ) = 0x90;

    VirtualProtect ( pAddress, dwLen, dwOldProtect, &dwBkup );

    return;

}
