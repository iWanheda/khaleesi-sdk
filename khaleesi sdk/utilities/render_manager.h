#pragma once

#include "vector.h"
#include "../interfaces/interfaces.h"
#include "singleton.h"

class render : public singleton<render> {
public:
	DWORD main_font;
	DWORD menu_font;
	DWORD tab_font;
	DWORD esp_font;

public:
	void setup_fonts() {
		static bool _o = false;
		if (!_o) {
			main_font = interfaces::surface->create_font();
			menu_font = interfaces::surface->create_font();
			tab_font = interfaces::surface->create_font();
			esp_font = interfaces::surface->create_font();

			interfaces::surface->set_font_glyph(main_font, "Roboto", 15, 500, 0, 0, font_flags::fontflag_dropshadow);
			interfaces::surface->set_font_glyph(menu_font, "Roboto", 14, 500, 0, 0, fontflag_dropshadow);
			interfaces::surface->set_font_glyph(tab_font, "cherryfont", 14, 0, 0, 0, font_flags::fontflag_antialias);
			interfaces::surface->set_font_glyph(esp_font, "Roboto", 15, 500, 0, 0, font_flags::fontflag_dropshadow);
			_o = true;
		}
	}
	void draw_line(int x1, int y1, int x2, int y2, color colour) {
		interfaces::surface->draw_set_color(colour.r, colour.g, colour.b, colour.a);
		interfaces::surface->draw_line(x1, y1, x2, y2);
	}
	void draw_text(int x, int y, unsigned long font, const char* string, bool text_centered, color colour) {
		va_list va_alist;
		char buf[1024];
		va_start(va_alist, string);
		_vsnprintf(buf, sizeof(buf), string, va_alist);
		va_end(va_alist);
		wchar_t wbuf[1024];
		MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

		int width, height;
		interfaces::surface->get_text_size(font, wbuf, width, height);

		interfaces::surface->draw_set_text_color(colour.r, colour.g, colour.b, colour.a);
		interfaces::surface->draw_set_text_font(font);
		if (text_centered)
			interfaces::surface->draw_set_text_pos(x - (width / 2), y);
		else
			interfaces::surface->draw_set_text_pos(x, y);
		interfaces::surface->draw_print_text(wbuf, wcslen(wbuf));
	}
	void draw_text(int x, int y, unsigned long font, std::string string, bool text_centered, color colour) {
		std::wstring text = std::wstring(string.begin(), string.end());
		const wchar_t* converted_text = text.c_str();

		int width, height;
		interfaces::surface->get_text_size(font, converted_text, width, height);

		interfaces::surface->draw_set_text_color(colour.r, colour.g, colour.b, colour.a);
		interfaces::surface->draw_set_text_font(font);
		if (text_centered)
			interfaces::surface->draw_set_text_pos(x - (width / 2), y);
		else
			interfaces::surface->draw_set_text_pos(x, y);
		interfaces::surface->draw_print_text(converted_text, wcslen(converted_text));
	}
	void draw_filled_rect(int x, int y, int w, int h, color colour) {
		interfaces::surface->draw_set_color(colour.r, colour.g, colour.b, colour.a);
		interfaces::surface->draw_filled_rect(x, y, w, h);
	}
	void draw_outline(int x, int y, int w, int h, color colour) {
		interfaces::surface->draw_set_color(colour.r, colour.g, colour.b, colour.a);
		interfaces::surface->draw_filled_rect(x, y, w, h);
	}
	/*void draw_textured_polygon(int n, vertex_t* vertice, color col) {
		static int texture_id = interfaces::surface->create_new_texture_id(true);
		static unsigned char buf[4] = { 255, 255, 255, 255 };
		interfaces::surface->set_texture_rgba(texture_id, buf, 1, 1);
		interfaces::surface->set_drawing_color(col.r, col.g, col.b, col.a);
		interfaces::surface->set_texture(texture_id);
		interfaces::surface->draw_polygon(n, vertice);
	}*/

	void draw_circle(int x, int y, int r, int s, color col) {
		float step = m_pi * 2.0 / s;
		for (float a = 0; a < (m_pi * 2.0); a += step) {
			float x1 = r * cos(a) + x;
			float y1 = r * sin(a) + y;
			float x2 = r * cos(a + step) + x;
			float y2 = r * sin(a + step) + y;
			interfaces::surface->draw_set_color(col.r, col.g, col.b, col.a);
			interfaces::surface->draw_line(x1, y1, x2, y2);
		}
	}

	void get_text_size(unsigned long font, const char* string, int w, int h) {
		va_list va_alist;
		char buf[1024];
		va_start(va_alist, string);
		_vsnprintf(buf, sizeof(buf), string, va_alist);
		va_end(va_alist);
		wchar_t out[1024];
		MultiByteToWideChar(CP_UTF8, 0, buf, 256, out, 256);

		interfaces::surface->get_text_size(font, out, w, h);
	}
	void get_text_size(unsigned long font, std::string string, int w, int h) {
		std::wstring text = std::wstring(string.begin(), string.end());
		const wchar_t* out = text.c_str();

		interfaces::surface->get_text_size(font, out, w, h);
	}
	RECT get_text_size2(DWORD font, const char* text, ...) {
		size_t origsize = strlen(text) + 1;
		const size_t newsize = 100;
		size_t convertedChars = 0;
		wchar_t wcstring[newsize];
		mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

		RECT rect; int x, y;
		interfaces::surface->get_text_size(font, wcstring, x, y);
		rect.left = x; rect.bottom = y;
		rect.right = x;
		return rect;
	}
};