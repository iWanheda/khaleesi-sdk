#include "../../utilities/utilities.h"

class i_panel {
public:
	const char* get_name(unsigned int vgui_panel) {
		using original_fn = const char*(__thiscall*)(PVOID, int);
		return (*(original_fn**)this)[ 36 ](this, vgui_panel);
	}
};