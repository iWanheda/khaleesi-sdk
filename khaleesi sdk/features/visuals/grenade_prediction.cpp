#include "grenade_prediction.h"
/*
void c_nade_prediction::predict(c_usercmd* cmd) {
	constexpr float restitution = 0.45f;
	constexpr float power[] = { 1.0f, 1.0f, 0.5f, 0.0f };
	constexpr float velocity = 403.0f * 0.9f;

	float step, gravity, new_velocity, unk01;
	int index { }, grenade_act{ 1 };
	vec3_t pos, thrown_direction, start, eye_origin;
	vec3_t angles, thrown;

	static auto sv_gravity = g_csgo.m_convar->FindVar("sv_gravity");

	gravity = sv_gravity->GetFloat() / 8.0f;
	step = g_csgo.m_global_vars->m_interval_per_tick;

	eye_origin = g_cl.m_local->eye_pos();
	angles = cmd->viewangles;

	thrown = angles;

	if (thrown.x < 0) {
		thrown.x = -10 + thrown.x * ((90 - 10) / 90.0f);
	}
	else {
		thrown.x = -10 + thrown.x * ((90 + 10) / 90.0f);
	}

	auto primary_attack = cmd->buttons & in_attack;
	auto secondary_attack = cmd->buttons & in_attack2;

	if (primary_attack && secondary_attack) {
		grenade_act = ACT_LOB;
	}
	else if (secondary_attack) {
		grenade_act = ACT_DROP;
	}

	//	apply 'magic' and modulate by velocity
	unk01 = power[grenade_act];

	unk01 = unk01 * 0.7f;
	unk01 = unk01 + 0.3f;

	new_velocity = velocity * unk01;

	//	here's where the fun begins
	math::angle_to_vector(thrown, thrown_direction);

	start = eye_origin + thrown_direction * 16.0f;
	thrown_direction = (thrown_direction * new_velocity) + g_cl.m_local->velocity();

	//	let's go ahead and predict
	for (auto time = 0.0f; index < 500; time += step) {
		pos = start + thrown_direction * step;

		//	setup trace
		trace_t trace;
		CTraceFilterSkipEntity filter(g_cl.m_local);

		g_csgo.m_engine_trace->TraceRay(Ray_t{ start, pos }, MASK_SOLID, &filter, &trace);

		//	modify path if we have hit something
		if (trace.fraction != 1.0f) {
			thrown_direction = trace.plane.m_normal * -2.0f * thrown_direction.Dot(trace.plane.m_normal) + thrown_direction;

			thrown_direction *= restitution;

			pos = start + thrown_direction * trace.fraction * step;

			time += (step * (1.0f - trace.fraction));
		}

		//	check for detonation
		auto detonate = detonated(g_cl.m_local->get_active_weapon(), time, trace);

		//	emplace nade point
		_points.at(index++) = c_nadepoint(start, pos, trace.fraction != 1.0f, true, trace.plane.m_normal, detonate);
		start = pos;

		//	apply gravity modifier
		thrown_direction.z -= gravity * trace.fraction * step;

		if (detonate) {
			break;
		}
	}

	//	invalidate all empty points and finish prediction
	for (auto n = index; n < 500; ++n) {
		_points.at(n).m_valid = false;
	}

	_predicted = true;
}

bool c_nade_prediction::detonated(C_BaseCombatWeapon *weapon, float time, trace_t &trace) {
	if (!weapon) {
		return true;
	}

	//	get weapon item index
	const auto index = weapon->item_index();

	switch (index) {
		//	flash and HE grenades only live up to 2.5s after thrown
	case 43:
	case 44:
		if (time > 2.5f) {
			return true;
		}
		break;

		//	fire grenades detonate on ground hit, or 3.5s after thrown
	case WEAPON_MOLOTOV:
	case 48:
		if (trace.fraction != 1.0f && trace.plane.m_normal.z > 0.7f || time > 3.5f) {
			return true;
		}
		break;

		//	decoy and smoke grenades were buggy in prediction, so i used this ghetto work-around
	case WEAPON_DECOY:
	case 45:
		if (time > 2.5f) {
			return true;
		}
		break;
	}

	return false;
}

void c_nade_prediction::trace(CUserCmd *ucmd) {
	if (!g_vars.visuals.grenade_pred)
		return;

	if (!(ucmd->m_buttons & IN_ATTACK) && !(ucmd->m_buttons & IN_ATTACK2)) {
		_predicted = false;
		return;
	}

	const static std::vector< int > nades{
		WEAPON_FLASHBANG,
		WEAPON_SMOKEGRENADE,
		WEAPON_HEGRENADE,
		WEAPON_MOLOTOV,
		WEAPON_DECOY,
		WEAPON_INCGRENADE
	};

	//	grab local weapon
	auto weapon = g_cl.m_local->get_active_weapon();

	if (!weapon) {
		return;
	}

	if (std::find(nades.begin(), nades.end(), weapon->item_index()) != nades.end()) {
		return predict(ucmd);
	}

	_predicted = false;
}

void c_nade_prediction::draw() {
	if (!g_vars.visuals.grenade_pred)
		return;

	if (!g_csgo.m_engine->IsInGame() || !g_cl.m_local || !g_cl.m_local->alive())
		return;

	auto draw_3d_dotted_circle = [](vec3_t position, float points, float radius) {
		float step = math::pi * 2.0f / points;
		for (float a = 0; a < math::pi * 2.0f; a += step) {
			vec3_t start(radius * cosf(a) + position.x, radius * sinf(a) + position.y, position.z);

			vec3_t start2d;
			if (g_visuals.world_to_screen(start, start2d))
				g_renderer.line(OSHColor::FromRGB(255, 255, 255), start2d.x, start2d.y, start2d.x + 1, start2d.y + 1);
		}
	};

	vec3_t start, end;

	//	draw nade path
	if (_predicted) {
		for (auto &p : _points) {
			if (!p.m_valid) {
				break;
			}

			if (g_visuals.world_to_screen(p.m_start, start) && g_visuals.world_to_screen(p.m_end, end)) {
				//	draw line
				g_renderer.line(OSHColor::FromRGB(0, 125, 255), start.x, start.y, end.x, end.y);

				//	draw small box if detonated or hit a wall
				if (p.m_detonate || p.m_plane) {
					g_renderer.rect(p.m_detonate ? OSHColor::FromRGB(255, 0, 0) : OSHColor::White(), start.x - 2, start.y - 2, 5, 5);
				}

				if (p.m_detonate)
					draw_3d_dotted_circle(p.m_end, 100, 150);
			}
		}
	}
}*/