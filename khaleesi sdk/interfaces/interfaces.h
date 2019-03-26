#pragma once

#include "../sdk/source-sdk/i_surface.h"
#include "../sdk/source-sdk/i_panel.h"
#include "../sdk/source-sdk/iv_engine_client.h"
#include "../sdk/source-sdk/i_client_mode.h"
#include "../sdk/source-sdk/i_client_entity.h"
#include "../sdk/source-sdk/c_global_vars.h"
#include "../sdk/source-sdk/i_input_system.h"
#include "../sdk/source-sdk/i_client_entity_list.h"
#include "../sdk/source-sdk/icvar.h"

namespace interfaces {
	extern iv_engine_client*		engine;
	extern i_surface*				surface;
	extern i_panel*					panel;
	extern i_base_client_dll*		client;
	extern i_client_mode*			client_mode;
	extern c_global_vars*			global_vars;
	extern i_client_entity_list*	entity_list;
	extern i_cvar*					cvar;
	extern i_input_system*			input_system;

	void init();
}