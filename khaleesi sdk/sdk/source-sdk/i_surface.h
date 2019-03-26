#pragma once

#include "i_app_system.h"
#include "../utilities/utilities.h"

namespace vgui {
	typedef unsigned long h_font;
	typedef unsigned int vpanel;
};

enum font_feature {
	FONT_FEATURE_ANTIALIASED_FONTS = 1, 
	FONT_FEATURE_DROPSHADOW_FONTS = 2,
	FONT_FEATURE_OUTLINE_FONTS = 6
};

enum font_draw_type {
	FONT_DRAW_DEFAULT = 0, 
	FONT_DRAW_NONADDITIVE, 
	FONT_DRAW_ADDITIVE, 
	FONT_DRAW_TYPE_COUNT = 2
};

enum font_flags {
	fontflag_none,
	fontflag_italic = 0x001,
	fontflag_underline = 0x002,
	fontflag_strikeout = 0x004,
	fontflag_symbol = 0x008,
	fontflag_antialias = 0x010,
	fontflag_gaussianblur = 0x020,
	fontflag_rotary = 0x040,
	fontflag_dropshadow = 0x080,
	fontflag_additive = 0x100,
	fontflag_outline = 0x200,
	fontflag_custom = 0x400,
	fontflag_bitmap = 0x800,
};

class color {
public:
	float r, g, b, a;
	color(float red, float green, float blue, float alpha) {
		r = red, g = green, b = blue, a = alpha;
	}
	color(float red, float green, float blue) {
		r = red, g = green, b = blue, a = 255.f;
	}
};

struct int_rect {
	int x0;
	int y0;
	int x1;
	int y1;
};

class i_surface : i_app_system {
public:
	virtual void          run_frame() = 0;
	virtual vgui::vpanel  get_embedded_panel() = 0;
	virtual void          set_embedded_panel(vgui::vpanel p_panel) = 0;
	virtual void          push_make_current(vgui::vpanel panel, bool use_insets) = 0;
	virtual void          pop_make_current(vgui::vpanel panel) = 0;
	virtual void          draw_set_color(int r, int g, int b, int a) = 0;
	virtual void          draw_set_color(color col) = 0;
	virtual void          draw_filled_rect(int x0, int y0, int x1, int y1) = 0;
	virtual void          draw_filled_rect_int_array(int_rect *p_rects, int num_rects) = 0;
	virtual void          draw_outline(int x0, int y0, int x1, int y1) = 0;
	virtual void          draw_line(int x0, int y0, int x1, int y1) = 0;
	virtual void          draw_point_line(int *px, int *py, int num_points) = 0;
	virtual void          draw_set_depth(float f) = 0;
	virtual void          draw_clear_depth(void) = 0;
	virtual void          draw_set_text_font(vgui::h_font font) = 0;
	virtual void          draw_set_text_color(int r, int g, int b, int a) = 0;
	virtual void          draw_set_text_color(color col) = 0;
	virtual void          draw_set_text_pos(int x, int y) = 0;
	virtual void          draw_get_text_pos(int& x, int& y) = 0;
	virtual void          draw_print_text(const wchar_t *text, int text_len, font_draw_type draw_type = font_draw_type::FONT_DRAW_DEFAULT) = 0;
	virtual void          draw_unicode_character(wchar_t wch, font_draw_type draw_type = font_draw_type::FONT_DRAW_DEFAULT) = 0;
	virtual void          draw_flush_text() = 0;
	virtual void*         create_html_window(void *events, vgui::vpanel context) = 0; // reminder: look into this html stuff, may be useful someday.
	virtual void          paint_html_window(void *htmlwin) = 0;
	virtual void          delete_html_window(void *htmlwin) = 0;
	virtual int           draw_get_texture_id(char const *filename) = 0;
	virtual bool          draw_get_texture_file(int id, char *filename, int maxlen) = 0;
	virtual void          draw_set_texture_file(int id, const char *filename, int hardware_filter, bool reload) = 0;
	virtual void          draw_set_texture_rgba(int id, const unsigned char *rgba, int wide, int tall) = 0;
	virtual void          draw_set_texture(int id) = 0;
	virtual void          delete_texture_id(int id) = 0;
	virtual void          draw_get_texture_size(int id, int &wide, int &tall) = 0;
	virtual void          draw_textured_rect(int x0, int y0, int x1, int y1) = 0;
	virtual bool          is_texture_id_valid(int id) = 0;
	virtual int           create_new_texture_id(bool procedural = false) = 0;
	virtual void          get_screen_size(int &wide, int &tall) = 0;
	virtual void          set_as_top_most(vgui::vpanel panel, bool state) = 0;
	virtual void          bring_to_front(vgui::vpanel panel) = 0;
	virtual void          set_foreground_window(vgui::vpanel panel) = 0;
	virtual void          set_panel_visibility(vgui::vpanel panel, bool state) = 0;
	virtual void          set_panel_minimizised(vgui::vpanel panel, bool state) = 0;
	virtual bool          is_panel_minimized(vgui::vpanel panel) = 0;
	virtual void          flash_window(vgui::vpanel panel, bool state) = 0;
	virtual void          set_title(vgui::vpanel panel, const wchar_t *title) = 0;
	virtual void          set_as_toolbar(vgui::vpanel panel, bool state) = 0;
	virtual void          create_popup(vgui::vpanel panel, bool minimised, bool show_taskbar_icon = true, bool disabled = false, bool mouse_input = true, bool keyboard_input = true) = 0;
	virtual void          swap_buffers(vgui::vpanel panel) = 0;
	virtual void          invalidate(vgui::vpanel panel) = 0;
	virtual void          set_cursor(unsigned long cursor) = 0;
	virtual bool          is_cursor_visible() = 0;
	virtual void          apply_changes() = 0;
	virtual bool          is_within(int x, int y) = 0;
	virtual bool          has_focus() = 0;
	virtual bool          supports_feature(int feature) = 0;
	virtual void          restrict_paint_to_panel(vgui::vpanel panel, bool allow_nonmodal_surface = false) = 0;
	virtual void          set_modal_panel(vgui::vpanel) = 0;
	virtual vgui::vpanel  get_modal_panel() = 0;
	virtual void          unlock_cursor() = 0;
	virtual void          lock_cursor() = 0;
	virtual void          set_translate_extend_keys(bool state) = 0;
	virtual vgui::vpanel  get_topmost_popup() = 0;
	virtual void          set_top_level_focus(vgui::vpanel panel) = 0;
	virtual vgui::h_font  create_font() = 0;
	virtual bool          set_font_glyph(vgui::h_font font, const char *windows_font_name, int tall, int weight, int blur, int scanlines, int flags, int range_minimum = 0, int range_maximum = 0) = 0;
	virtual bool          add_custom_font(const char* font) = 0;
	virtual int           get_font_tall(vgui::h_font font) = 0;
	virtual int           get_font_ascent(vgui::h_font font, wchar_t wch) = 0;
	virtual bool          is_font_additive(vgui::h_font font) = 0;
	virtual void          get_char_wideness(vgui::h_font font, int ch, int &a, int &b, int &c) = 0;
	virtual int           get_char_width(vgui::h_font font, int ch) = 0;
	virtual void          get_text_size(vgui::h_font font, const wchar_t *text, int &wide, int &tall) = 0;
	virtual vgui::vpanel  get_notify_panel() = 0;
	virtual void          set_notify_panel(vgui::vpanel context, unsigned long icon, vgui::vpanel panel_to_recieve, const char *text) = 0;
	virtual void          play_sound(const char *filename) = 0;
	virtual int           get_popup_count() = 0;
	virtual vgui::vpanel  get_popup(int index) = 0;
	virtual bool          should_repaint_child_panel(vgui::vpanel child_panel) = 0;
	virtual bool          recreate_context(vgui::vpanel panel) = 0;
	virtual void          add_panel(vgui::vpanel panel) = 0;
	virtual void          release_panel(vgui::vpanel panel) = 0;
	virtual void          move_to_front(vgui::vpanel panel) = 0;
	virtual void          move_to_back(vgui::vpanel panel) = 0;
	virtual void          solve_traverse(vgui::vpanel panel, bool force_apply = false) = 0;
	virtual void          paint_traverse(vgui::vpanel panel) = 0;
	virtual void          enable_mouse_capture(vgui::vpanel panel, bool state) = 0;
	virtual void          get_workspace_bounds(int &x, int &y, int &wide, int &tall) = 0;
	virtual void          get_absolute_workspace_bounds(int &x, int &y, int &wide, int &tall) = 0;
	virtual void          get_base(int &width, int &height) = 0;
	virtual void          calculate_mouse_visible() = 0;
	virtual bool          need_keyboard_input() = 0;
	virtual bool          has_cursor_position_functions() = 0;
	virtual void          surface_get_cursor_position(int &x, int &y) = 0;
	virtual void          surface_set_cursor_position(int x, int y) = 0;
	virtual void          draw_outlined_circle(int x, int y, int radius, int segments) = 0;
	virtual void          draw_textured_sub_rect(int x0, int y0, int x1, int y1, float texs0, float text0, float texs1, float text1) = 0;
};