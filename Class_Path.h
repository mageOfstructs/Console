#pragma once
#include "console.h"

class Path
{
private:
	fs::path cur_path;
public:
	// Constructor
	Path();

	void check_all_paths();
	bool check_path(fs::path path);
	fs::path get_glv_path(int choice = 0);
	fs::path get_temp_path();
	fs::path get_log_path();
	fs::path get_users_path();
	my_json::json init_data();
};