#pragma once

#include "../utilities/vmt.h"
#include "../interfaces/interfaces.h"

#include "../sdk/source-sdk/c_input.h"

enum hook_indexes {
	create_move = 24,
	viewmodel_fov = 35,
	frame_stage_notify = 37,
	paint_traverse = 41
};

enum client_frame_stage_t {
	frame_undefined = -1,
	frame_start,
	frame_net_update_start,
	frame_net_update_postdataupdate_start,
	frame_net_update_postdataupdate_end,
	frame_net_update_end,
	frame_render_start,
	frame_render_end
};

namespace hooks {
	void init();
	void restore();

	static bool     __fastcall  create_move_hook(i_client_mode*, void*, float, c_usercmd*);
	static void		__fastcall  paint_traverse_hook(PVOID, int, unsigned int, bool, bool);
	static void		__stdcall   frame_stage_notify(int);
	static float    __stdcall   viewmodel_fov_hook();

	typedef bool(__fastcall* create_move_t) (i_client_mode*, void*, float, c_usercmd*);
	typedef void(__thiscall* paint_traverse_t) (PVOID, unsigned int, bool, bool);
	typedef void(__thiscall* frame_stage_notify_t) (i_base_client_dll*, int);
}