#pragma once

#include "..\..\utilities\utilities.h"
#include "..\..\utilities\globals.h"
#include "..\..\sdk\source-sdk\c_input.h"
#include "..\..\sdk\entities.h"

class canti_aim : public singleton < canti_aim > {
public:
	void do_anti_aim(c_usercmd*);
private:
};