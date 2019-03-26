#pragma once

#include "..\utilities\render_manager.h"
#include "..\utilities\singleton.h"
#include "..\utilities\vector.h"

class c_menu : public singleton < c_menu > {
public:
private:
	void draw();
};