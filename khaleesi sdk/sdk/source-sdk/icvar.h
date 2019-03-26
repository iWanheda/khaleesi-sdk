#pragma once

#include "i_surface.h"

class convar {
public:
	float get_float() {
		using original_fn = float(__thiscall*)(void*);
		return (*(original_fn**)this)[ 12 ](this);
	}

	float get_int() {
		using original_fn = int(__thiscall*)(void*);
		return (*(original_fn**)this)[ 13 ](this);
	}

	void set_value(int value) {
		using original_fn = void(__thiscall*)(void*, int);
		return (*(original_fn**)this)[ 16 ](this, value);
	}
};

class i_cvar {
public:
	convar* find_var(const char* var) {
		using original_fn = convar*(__thiscall*)(void*, const char*);
		return (*(original_fn**)this)[ 15 ](this, var);
	}

	/*template <typename ... T>
	void print_to_console(const color& clr, const char* format, T ... args) {
		using original_fn = void(__thiscall*)(void*, const color&, const char*, T ...);
		return (*(original_fn**)this)[ 25 ](this, clr, format, args ...);
	}*/
};