#include "hooks.h"
#include "../utilities/globals.h"
#include "../utilities/render_manager.h"
#include "..\ui\menu.h"

std::unique_ptr<vmt>   client_mode_hook;
std::unique_ptr<vmt>   panel_hook;
std::unique_ptr<vmt>   client_hook;

auto hooks::init() -> void {
	client_mode_hook	= std::make_unique<vmt>(interfaces::client_mode);
	panel_hook			= std::make_unique<vmt>(interfaces::panel);
	client_hook			= std::make_unique<vmt>(interfaces::client);

	client_mode_hook->hook(hook_indexes::create_move, create_move_hook);
	client_mode_hook->hook(hook_indexes::viewmodel_fov, viewmodel_fov_hook);

	panel_hook->hook(hook_indexes::paint_traverse, paint_traverse_hook);

	client_hook->hook(hook_indexes::frame_stage_notify, frame_stage_notify);

	render::get().setup_fonts();
}

auto hooks::restore() -> void {
	client_mode_hook->unhook(hook_indexes::create_move);
	client_mode_hook->unhook(hook_indexes::viewmodel_fov);

	panel_hook->unhook(hook_indexes::paint_traverse);

	client_hook->unhook(hook_indexes::frame_stage_notify);
}

auto __fastcall hooks::create_move_hook(i_client_mode* thisptr, void* edx, float sample_frametime, c_usercmd* cmd) -> bool {
	static auto o_create_move = client_mode_hook->get_original<create_move_t>(hook_indexes::create_move);

	o_create_move(thisptr, edx, sample_frametime, cmd);

	if (!(interfaces::engine->is_in_game() && interfaces::engine->is_connected() || cmd || cmd->command_number))
		return o_create_move;

	uintptr_t* pointer; __asm { MOV pointer, EBP }
	byte* send_packet = (byte*)(*pointer - 0x1C); if (!send_packet) return false;

	globals::send_packet = send_packet;
	globals::global_cmd = cmd;

	cmd->buttons |= cmd_buttons::in_bullrush;

	std::string clan_tag = " wanheda.red ";
	std::rotate(clan_tag.begin(), clan_tag.begin() + 1, clan_tag.end());
	utilities::set_clantag(clan_tag.c_str());

	cmd->viewangles.x = 89.f;

	return false;
}

auto __stdcall hooks::viewmodel_fov_hook() -> float {
	return 120.f;
}

auto __fastcall hooks::paint_traverse_hook(PVOID panel, int edx, unsigned int vgui_panel, bool force_repaint, bool allow_force) -> void {
	static auto o_paint_traverse = panel_hook->get_original<paint_traverse_t>(hook_indexes::paint_traverse);

	static unsigned int panel_hud_id, panel_id;

	if (!(panel_hud_id && strcmp("HudZoom", interfaces::panel->get_name(vgui_panel))))
		panel_hud_id = vgui_panel;

	o_paint_traverse(panel, vgui_panel, force_repaint, allow_force);

	if (!(panel_id && strcmp("MatSystemTopPanel", interfaces::panel->get_name(vgui_panel))))
		panel_id = vgui_panel;

	if (panel_id == vgui_panel) {
		//c_menu::get().draw();
	}
}

auto __stdcall hooks::frame_stage_notify(int frame_stage) -> void {
	static auto o_frame_stage_notify = client_hook->get_original<frame_stage_notify_t>(hook_indexes::frame_stage_notify);

	if (interfaces::engine->is_in_game() && interfaces::engine->is_connected()) {
		switch (frame_stage) {
			case frame_net_update_postdataupdate_start:
				break;
			case frame_net_update_postdataupdate_end:
				 break;
			case frame_render_start:
				break;
			case frame_net_update_start:
				break;
			case frame_net_update_end:
				break;
			case frame_render_end:
				break;
		}
	}
}