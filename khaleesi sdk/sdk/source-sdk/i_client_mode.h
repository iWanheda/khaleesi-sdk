#pragma once

#include "i_client_entity.h"

class i_client_mode {

public:
	bool should_draw_entity(i_client_entity *p_entity) {
		using original_fn = bool(__thiscall*)(void*, i_client_entity*);
		return (*(original_fn**)this)[ 14 ](this, p_entity);

	}
};