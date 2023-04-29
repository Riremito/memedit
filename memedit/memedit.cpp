#include"../Share/Simple/Simple.h"
#include"../Share/Hook/SimpleHook.h"

bool memory_edit() {
	static bool first = true;

	if (!first) {
		return false;
	}

	first = false;

	// memory edit zone
	Rosemary r;
	// test code
	r.Patch(0x3284BFC0, L"31 C0 C3");
	//r.Patch(Address or Aob, L"90 90 90 90 90");

	return true;
}

decltype(CreateMutexW) *_CreateMutexW = NULL;
HANDLE WINAPI CreateMutexW_Hook(LPSECURITY_ATTRIBUTES lpMutexAttributes, BOOL bInitialOwner, LPCWSTR lpName) {
	if (lpName && wcsncmp(lpName, L"ElswordX2_", 10) == 0) {
		DEBUG(L"ElswordX2! started");
		memory_edit();
	}
	return _CreateMutexW(lpMutexAttributes, bInitialOwner, lpName);
}

bool EmuLoader(HMODULE hDll) {
	SHook(CreateMutexW);
	return true;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH:
	{
		DisableThreadLibraryCalls(hinstDLL);
		EmuLoader(hinstDLL);
		break;
	}
	case DLL_PROCESS_DETACH:
	{
		break;
	}
	default:
	{
		break;
	}
	}
	return TRUE;
}