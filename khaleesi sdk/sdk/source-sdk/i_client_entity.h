#pragma once

#include "client_class.h"

class i_base_client_dll {
public:
	c_client_class* get_client_classes() {
		using original_fn = c_client_class*(__thiscall*)(i_base_client_dll*);
		return (*(original_fn**)this)[ 8 ](this);
	}
};

class i_client_entity {
public:
	int entity_index() {
		using original_fn = int(__thiscall*)(void*, void*);
		return (*(original_fn**)this)[ 10 ](this, reinterpret_cast<void*>(this + 0x8)); // wrong???
	}
};