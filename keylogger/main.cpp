#include <iostream>
#include <windows.h>
using namespace std;

LRESULT CALLBACK proc01(int code, WPARAM wp, LPARAM lp);
// /subsystem:windows
//int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
//					LPSTR lpCmdLine, int nCmdShow )
int main()
{
    HHOOK keyHook = SetWindowsHookEx(WH_KEYBOARD_LL, proc01, nullptr, NULL);
    //settimer
    MSG  msg;
    while( GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
LRESULT CALLBACK proc01(int code, WPARAM wp, LPARAM lp){
    if(code==0){
        KBDLLHOOKSTRUCT khs = *(KBDLLHOOKSTRUCT*)lp;
        LONG msg = 1;
        WCHAR keyname[256] = {0};
        msg += (khs.scanCode << 16);
        msg += (khs.flags << 24);
        GetKeyNameText(msg, keyname,256);
        //key name
        wcout<<keyname<<endl;
        //key released or pressed
        cout<<wp<<endl;

    }
    return CallNextHookEx(NULL, code, wp, lp);
}
