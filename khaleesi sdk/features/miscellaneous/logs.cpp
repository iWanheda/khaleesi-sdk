#include "logs.h"

/*void c_notifications::add(bool display, color ccolor, const std::string message, ...) {
	if (message.empty())
		return;

	va_list va;
	std::string buf;

	va_start(va, message);

	const int str_len = std::vsnprintf(nullptr, 0, message.c_str(), va);
	if (str_len < 0) {
		va_end(va);

		return;
	} buf.resize(str_len);

	std::vsnprintf(&buf[0], str_len + 1, message.c_str(), va);

	if (m_notifications.size() > 15)
		m_notifications.pop_front();

	interfaces::cvar->print_to_console(color(255, 20, 255), "[khaleesi]");
	interfaces::cvar->print_to_console(color(255, 255, 255), " %s\n", buf.c_str());

	if (display)
		m_notifications.emplace_back(ccolor, color(125, 0, 0, 0), interfaces::global_vars->curtime, buf);
}

void c_notifications::clear() {
	m_notifications.clear();
}

void c_notifications::draw() {
	int adjust_height = 5;

	for (size_t i = 0; i < m_notifications.size(); i++) {
		auto &notification = m_notifications.at(i);

		color& ccolor = notification.ccolor;
		color& shadow_color = notification.background_color;
		const float cur_time = notification.m_time;
		std::string message = notification.m_buf;

		if (interfaces::global_vars->curtime - cur_time > m_text_duration) {
			int alpha = static_cast<int>(ccolor.a * 255.f - 255 / 1.f * std::max(interfaces::global_vars->frametime, 0.01f));
			if (alpha > 255)
				alpha = 255;
			if (alpha < 0)
				alpha = 0;

			if (!alpha) {
				m_notifications.erase(m_notifications.begin() + i);
				continue;
			}

			color col = ccolor;
			ccolor = color(col.r * 255.f, col.g * 255.f, col.b * 255.f, alpha);

			color shadow_col = shadow_color;
			shadow_color = color(shadow_col.r * 255.f, shadow_col.g * 255.f, shadow_col.b * 255.f, alpha);
		}

		/*OSHGui::Misc::TextHelper text_helper(g_renderer.get_font(FONT_VERDANA_7PX));
		text_helper.SetText(message);

		render::get().draw_text(8, adjust_height, render::get().main_font, message, ccolor);

		adjust_height += render::get().main_font /* get font height  + 1;
	}
}*/