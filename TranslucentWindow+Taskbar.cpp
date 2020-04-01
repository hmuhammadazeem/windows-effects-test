#include <Windows.h>
#include <iostream>
#include <string>

#define ACCENT_ENABLE_TRANSPARENTGRADIENT 2

struct ACCENTPOLICY {
	int nAccentState;
	int nFlags;
	int nColor;
	int nAnimationId;
};

struct WINCOMPATTRDATA {
	int nAttribute;
	PVOID pData;
	ULONG ulDataSize;
};


void SetBlurBehind(HWND hwnd) {
	if (true) {
		const HINSTANCE hModule = LoadLibrary(TEXT("user32.dll"));
		if (hModule) {
			typedef BOOL(WINAPI*pSetWindowCompositionAttribute)(HWND,
				WINCOMPATTRDATA*);
			const pSetWindowCompositionAttribute
				SetWindowCompositionAttribute =
				(pSetWindowCompositionAttribute)GetProcAddress(
					hModule,
					"SetWindowCompositionAttribute");

			// Only works on Win10
			if (SetWindowCompositionAttribute) {
				ACCENTPOLICY policy =
				{3, 0 , 3 == (ACCENT_ENABLE_TRANSPARENTGRADIENT) ? 255 : 0,0 };
				WINCOMPATTRDATA data = { 19,&policy, sizeof(ACCENTPOLICY) };
				SetWindowCompositionAttribute(hwnd, &data);
			}
			FreeLibrary(hModule);
		}
	}
	else {
		//Nothing
	}
}

int main() {

	HWND TaskbarHandle = FindWindow("Shell_TrayWnd", NULL);
	//HWND SecondaryTaskbar = FindWindow("This PC", NULL);
	HWND Actionbar = GetDesktopWindow();
	Sleep(3000);
	HWND pc = GetTopWindow(Actionbar);

	HWND c = GetForegroundWindow();
	tagWINDOWINFO *inf = new tagWINDOWINFO;
	inf->cbSize = sizeof(WINDOWINFO);

	GetWindowInfo(c, inf);

	LPSTR *a = new LPSTR;
	SendMessage(c, WM_GETTEXT, NULL, NULL);

	//ShowWindow(c, SW_SHOW);
	//std::string p = *a;
	SetBlurBehind(c);
	SetBlurBehind(TaskbarHandle);

	std::cout << "Hello!";




}