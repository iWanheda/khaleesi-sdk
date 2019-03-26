#pragma once

class i_input_system {
public:
	void enable_input(bool enable) {
		using original_fn = void(__thiscall*)(void*, bool);
		return (*(original_fn**)this)[11](this, enable);
	}
};