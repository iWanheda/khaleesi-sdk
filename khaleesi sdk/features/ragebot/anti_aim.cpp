#include "anti_aim.h"

void canti_aim::do_anti_aim(c_usercmd* cmd) {
	//auto local_player = interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()); if (!local_player) return;
	if (interfaces::engine->is_connected() && interfaces::engine->is_in_game()) {

	}
}

/*struct another_struct {
	template <typename T>
	T get() {
		T return_value;
		return return_value;
	}
};

struct other_struct {
	another_struct* the_fuck;
};

struct something {
	other_struct what;
};

int main() {
	something thing { };
	if (thing.what.the_fuck->get<bool>()) {

	}
}

template <class myType>
myType GetMax() {
	return GetMax();
}

template <class myType>

void smth() {
	if (GetMax<bool>()) {

	}
}*/

void anti_aim_desync_yaw(c_usercmd* cmd) {
	if (!globals::send_packet) {
		cmd->viewangles.y += 180.f;
	}
	else {
		cmd->viewangles.y += 180.f; // + get_max_desync_delta();
	}
}

/*void anti_aim_pitch(c_usercmd* cmd) {
	switch (vars->anti_aim.pitch<int>) {
		case 0:
			break;
		case 1:
			cmd->viewangles.x = +89; // down
			break;
		case 2:
			cmd->viewangles.x = -89; // up
			break;
		case 3:
			cmd->viewangles.x = -540; // fake down
			break;
		default:
			break;
	}
}*/