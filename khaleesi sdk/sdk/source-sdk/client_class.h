#pragma once

#include "structs.h"
#include "..\..\utilities\recv.h"

class client_class;
class i_client_networkable;

typedef i_client_networkable* (*create_client_class_fn)(int ent_number, int serial_number);
typedef i_client_networkable* (*create_event_fn)();

class c_client_class {
public:
	create_client_class_fn create_fn;
	create_event_fn create_event_fn;
	char* network_name;
	recv_table* recvtable_ptr;
	c_client_class* next_ptr;
	class_ids class_id;
};