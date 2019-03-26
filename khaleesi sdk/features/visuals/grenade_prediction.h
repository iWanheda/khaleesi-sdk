#pragma once

#include "..\..\utilities\utilities.h"
/*
class cgrenade_prediction : public singleton < cgrenade_prediction > {
public:
	cgrenade_prediction() {
		m_valid = false;
	}
	cgrenade_prediction(vec3_t start, vec3_t end, bool plane, bool valid, vec3_t normal, bool detonate) {
		m_start = start;
		m_end = end;
		m_plane = plane;
		m_valid = valid;
		m_normal = normal;
		m_detonate = detonate;
	}
	vec3_t m_start, m_end, m_normal;
	bool m_valid, m_plane, m_detonate;
};

class c_nade_prediction {
	std::array<cgrenade_prediction, 500> _points { };
	bool _predicted = false;

	void predict(c_usercmd*);
	bool detonated(weapon_t*, float, trace_t&);
public:
	void trace(c_usercmd*);
	void draw();
};*/