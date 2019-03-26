#pragma once

#include "..\utilities\utilities.h"
#include "source-sdk/structs.h"
#include "..\utilities\netvar_manager.h"
/*
template <typename T>
static T call_v_tablee(void* address, int index) {
	return (*reinterpret_cast<T**>(address))[index];
}

class entity_t {
private:
	template<class T>
	T get_pointer(const int offset) {
		return reinterpret_cast <T*> (reinterpret_cast <std::uintptr_t> (this) + offset);
	}
	template<class T>
	T get_value(const int offset) {
		return *reinterpret_cast <T*> (reinterpret_cast <std::uintptr_t> (this) + offset);
	}
public:
	bool dormant() {
		return *reinterpret_cast <bool*> (uintptr_t(this) + 0xED);
	}
	int team() {
		return get_value<int>(netvar_tree::get().get_offset("DT_BaseEntity", "m_iTeamNum"));
	}
	bool life_state() {
		return get_value<bool>(netvar_tree::get().get_offset("DT_BasePlayer", "m_lifeState"));
	}
	int health() {
		return get_value<int>(netvar_tree::get().get_offset("DT_BasePlayer", "m_iHealth"));
	}
	entity_flags flags() {
		return get_value<entity_flags>(netvar_tree::get().get_offset("DT_BasePlayer", "m_fFlags"));
	}
	move_types move_type() {
		return get_value<move_types>(netvar_tree::get().get_offset("DT_BaseEntity", "m_nRenderMode") + 1);
	}
	vec3_t origin() {
		return get_value<vec3_t>(netvar_tree::get().get_offset("DT_BaseEntity", "m_vecOrigin"));
	}
	vec3_t obb_min() {
		return get_value<vec3_t>(netvar_tree::get().get_offset("DT_BaseEntity", "m_vecMins"));
	}
	vec3_t obb_max() {
		return get_value<vec3_t>(netvar_tree::get().get_offset("DT_BaseEntity", "m_vecMaxs"));
	}
	float crouch_ammount() {
		return get_value<float>(netvar_tree::get().get_offset("DT_BasePlayer", "m_flDuckAmount"));
	}
	vec3_t& abs_origin() {
		return call_v_tablee<vec3_t&(__thiscall*)(void*)>(this, 10)(this);
	}
	bool is_alive() {
		return this->health() > 0;
	}
};*/