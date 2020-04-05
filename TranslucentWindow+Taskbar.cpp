#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

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

std::vector<HWND> handles;

BOOL CALLBACK collect(HWND handle, LPARAM lParam) {
	handles.push_back(handle);
	return true;
}


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
				/*{ 4, 0 , 3 == (ACCENT_ENABLE_TRANSPARENTGRADIENT) ? 255 : 26, 0 };*/
				{ 2, 0 , 2 == (ACCENT_ENABLE_TRANSPARENTGRADIENT) ? 255 : 0, 0 };
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

std::vector<std::wstring> getWindows() {
	std::vector<std::wstring> titles;
	EnumDesktopWindows(NULL, collect, reinterpret_cast<LPARAM>(&titles));
	return titles;
}

int main() {

	HWND TaskbarHandle = FindWindow("Shell_TrayWnd", NULL);
	//HWND SecondaryTaskbar = FindWindow("This PC", NULL);
	HWND Actionbar = GetDesktopWindow();
	Sleep(3000);
	

	getWindows();



	for (const auto& hwnd : handles) {
		const DWORD TITLE_SIZE = 1024;
		WCHAR windowTitle[TITLE_SIZE];
		int length = ::GetWindowTextLength(hwnd);
		if (IsWindowVisible(hwnd) && length > 0) {
			GetWindowTextW(hwnd, windowTitle, TITLE_SIZE);
			std::wcout << L"Title: " << windowTitle << std::endl;
		}
	}

	std::string t;

	do {
		std::cout << "\nEnter the Window Title: ";
		std::getline(std::cin, t);
		HWND pc = FindWindowA(NULL, t.c_str());

		Sleep(1000);

		//HWND c = GetForegroundWindow();
		//tagWINDOWINFO *inf = new tagWINDOWINFO;
		//inf->cbSize = sizeof(WINDOWINFO);

		//GetWindowInfo(c, inf);

		//LPSTR *a = new LPSTR;
		//SendMessage(c, WM_GETTEXT, NULL, NULL);

		//ShowWindow(c, SW_SHOW);
		//std::string p = *a;
		SetBlurBehind(pc);

	} while (t != "...");
	SetBlurBehind(TaskbarHandle);

	std::cout << "Hello!";

}