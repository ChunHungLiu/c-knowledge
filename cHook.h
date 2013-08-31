class cHook {
public:
    void* DetourFunction ( BYTE* src, const BYTE* dst, const int len );
    void MakeJMP ( BYTE* pAddress, DWORD dwJumpTo, DWORD dwLen );
};
extern cHook Hook;
