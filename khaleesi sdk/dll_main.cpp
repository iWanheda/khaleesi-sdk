#include <iostream>

#include "hooks/hooks.h"

using namespace std::literals::chrono_literals;

auto setup_debug_console() -> void WINAPI {
	AllocConsole();
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	SetConsoleTitleA("[khaleesi sdk]");
}

auto dll_setup(HINSTANCE module_handle) -> DWORD WINAPI {
	#ifdef _DEBUG
	 setup_debug_console();
	#endif

	interfaces::init();
	hooks::init();

	//interfaces::cvar->print_to_console(color(255, 20, 255), "[khaleesi sdk] ");
	//interfaces::cvar->print_to_console(color(255, 255, 255), "initialized!");

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(50)); {

		hooks::restore();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		fclose((FILE*)stdin);
		fclose((FILE*)stdout);
		FreeConsole();

		FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(module_handle), NULL);
	}
}

auto __stdcall DllMain(HMODULE module, DWORD reason_for_call, LPVOID reserved) -> bool {
	if (reason_for_call == DLL_PROCESS_ATTACH) {
		//DisableThreadLibraryCalls(module);
		CreateThread(NULL, NULL, reinterpret_cast<LPTHREAD_START_ROUTINE>(dll_setup), NULL, NULL, NULL);
	} return true;
}