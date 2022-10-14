#include "Class_Path.h"
#include "json_ns.h"

Path::Path()
{
	cur_path = fs::current_path();
}

void Path::check_all_paths()
{
	get_glv_path();
	get_temp_path();
	get_log_path();
	get_users_path();
}

bool Path::check_path(fs::path path)
{
	return fs::exists(path);
}

fs::path Path::get_temp_path()
{
	fs::path cur_path = fs::current_path();
	cur_path /= "Console_Config";
	cur_path /= "system";
	cur_path /= "temp";

	if (check_path(cur_path))
	{
		return cur_path;
	}
	else
	{
		std::cout << "Error: Temp Path doesn't exist! Creating one..." << std::endl;
		fs::create_directories(cur_path);

		return cur_path;
	}
}

fs::path Path::get_glv_path(int choice) // of global_vars
{
	fs::path cur_path = fs::current_path();
	cur_path /= "Console_Config";
	cur_path /= "system";

	if (!check_path(cur_path))
	{
		std::cout << "Error: GLV Path doesn't exist! Creating one..." << std::endl;
		fs::create_directories(cur_path);
	}

	if (choice == 0)
	{
		cur_path /= "global_vars.json";
	}

	return cur_path;
}

fs::path Path::get_log_path()
{
	fs::path cur_path = fs::current_path();
	cur_path /= "Console_Config";
	cur_path /= "system";
	cur_path /= "logs";

	if (check_path(cur_path))
	{
		return cur_path;
	}
	else
	{
		std::cout << "Error: Log Path doesn't exist! Creating one..." << std::endl;
		fs::create_directories(cur_path);
		return cur_path;
	}
}

my_json::json Path::init_data()
{
	my_json::json data;

	fs::path glv_path = this->get_glv_path();
	std::string raw = my_json::read_json_raw(glv_path);
	my_json::read_json_str(raw, data);


	return data;
}

fs::path Path::get_users_path()
{
	fs::path cur_path = fs::current_path();
	cur_path /= "Console_Config";
	cur_path /= "users";

	if (check_path(cur_path))
	{
		return cur_path;
	}
	else
	{
		std::cout << "Error: User Path doesn't exist! Creating one..." << std::endl;
		fs::create_directories(cur_path);
		return cur_path;
	}
}