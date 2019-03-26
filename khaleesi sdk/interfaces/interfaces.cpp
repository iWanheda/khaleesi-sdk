#include "interfaces.h"
#include "../utilities/utilities.h"

typedef void* (*create_interface_fn) (const char* name, int* return_code);
auto get_interface(const char* module, const char* interface_name) -> void* {
	void* interf = nullptr;
	auto create_interface = reinterpret_cast<create_interface_fn>(GetProcAddress(GetModuleHandleA(module), "CreateInterface"));

	char possible_interface_name[1024];
	for (size_t i = 1; i < 100; i++) {
		sprintf(possible_interface_name, "%s0%i", interface_name, i);
		interf = create_interface(possible_interface_name, NULL);
		if (interf)
			break;
		sprintf(possible_interface_name, "%s00%i", interface_name, i);
		interf = create_interface(possible_interface_name, NULL);
		if (interf)
			break;
	} std::string name = interface_name; std::transform(name.begin(), name.end(), name.begin(), ::tolower);
	printf("[interface] %s: 0x%p\n", name.c_str(), interf);
	return interf;
}

namespace interfaces {
	iv_engine_client*		engine				= nullptr;
	i_surface*				surface				= nullptr;
	i_base_client_dll*		client				= nullptr;
	i_client_mode*			client_mode			= nullptr;
	i_panel*				panel				= nullptr;
	c_global_vars*			global_vars			= nullptr;
	i_client_entity_list*   entity_list			= nullptr;
	i_cvar*					cvar				= nullptr;
	i_input_system*			input_system		= nullptr;

	auto init() -> void {
		engine = reinterpret_cast<iv_engine_client*>			( get_interface( "engine.dll", "VEngineClient" ));
		surface = reinterpret_cast<i_surface*>					( get_interface( "vguimatsurface.dll", "VGUI_Surface" ));
		client = reinterpret_cast<i_base_client_dll*>			( get_interface( "client_panorama.dll", "VClient" ));
		panel = reinterpret_cast<i_panel*>						( get_interface( "vgui2.dll", "VGUI_Panel" ));
		entity_list = reinterpret_cast<i_client_entity_list*>	( get_interface( "client_panorama.dll", "VClientEntityList" ));
		cvar = reinterpret_cast<i_cvar*>						( get_interface( "vstdlib.dll", "VEngineCvar" ));
		input_system = reinterpret_cast<i_input_system*>		( get_interface( "inputsystem.dll", "InputSystemVersion" ));

		client_mode = **(i_client_mode***)((*(DWORD**)client)[10] + 0x5);
		global_vars = **reinterpret_cast<c_global_vars***>((*reinterpret_cast<uintptr_t**>(client))[0] + 0x1Bu);
	}
}