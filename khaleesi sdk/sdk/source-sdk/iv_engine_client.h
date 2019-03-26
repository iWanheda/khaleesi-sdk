#pragma once

#include "..\..\utilities\utilities.h"
#include "view_matrix.h"

struct player_info_t {
	int64_t __pad0;
	union {
		int64_t xuid;
		struct {
			int xuidlow;
			int xuidhigh;
		};
	};
	char name[128];
	int userid;
	char guid[33];
	unsigned int friendsid;
	char friendsname[128];
	bool fakeplayer;
	bool ishltv;
	unsigned int customfiles[4];
	unsigned char filesdownloaded;
};

class iv_engine_client {
public:
	void get_screen_size(int& width, int& height) {
		using original_fn = void(__thiscall*)(void*, int&, int&);
		return (*(original_fn**)this)[ 5 ](this, width, height);
	}

	int get_local_player() {
		using original_fn = int(__thiscall*)(void*);
		return (*(original_fn**)this)[ 12 ](this);
	}

	float last_timestamp() {
		using original_fn = float(__thiscall*)(void*);
		return (*(original_fn**)this)[ 14 ](this);
	}

	int get_max_clients() {
		using original_fn = int(__thiscall*)(void*);
		return (*(original_fn**)this)[ 20 ](this);
	}

	bool is_in_game() {
		using original_fn = bool(__thiscall*)(void*);
		return (*(original_fn**)this)[ 26 ](this);
	}

	bool is_connected() {
		using original_fn = bool(__thiscall*)(void*);
		return (*(original_fn**)this)[ 27 ](this);
	}

	void client_cmd(const char* sz_cmd_string) {
		using original_fn = void(__thiscall*)(void*, const char*);
		return (*(original_fn**)this)[ 108 ](this, sz_cmd_string);
	}

	void unrestricted_client_cmd(const char* sz_cmd_string) {
		using original_fn = void(__thiscall*)(void*, const char*);
		return (*(original_fn**)this)[ 114 ](this, sz_cmd_string);
	}

	view_matrix_t& world_to_screen_matrix() {
		view_matrix_t temp;
		using original_fn = view_matrix_t& (__thiscall*)(iv_engine_client*);
		return (*(original_fn**)this)[37](this);
	}
};