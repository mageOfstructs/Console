#include "console.h"
#include "json_ns.h"
#include "Class_Path.h"

Path main_obj_Path;

int main()
{
	main_obj_Path.check_all_paths();

	my_json::json glv_main;

	fs::path glv_path = main_obj_Path.get_glv_path();

	// write glv
	if (!fs::exists(glv_path))
	{
		std::cout << "GLV Folder Path doesn't exist" << std::endl;

		my_json::json glv_data("glv");
		my_json::json_raw raw = my_json::gen_json_raw(glv_data);
		std::vector<std::string> file_content = my_json::convert_json(raw);
		my_json::write_json(file_content, glv_path);
	}
	
	// read glv
	std::string raw_file_content = my_json::read_json_raw(glv_path);
	my_json::read_json_str(raw_file_content, glv_main);

	intro(2072); 

	while (true)
	{
		if (glv_main.str[glv_username].second != "Unregistered User")
		{
			fs::path user_path = main_obj_Path.get_users_path();
			std::string file_name = glv_main.str[glv_username].second + ".json";
			user_path /= file_name;

			my_json::json user_json;
			std::string raw = my_json::read_json_raw(user_path);
			my_json::read_json_str(raw, user_json);

			if (user_json.jbool[acc_is_admin].second)
			{
				std::cout << "%ROOT%>";
			}
			else
			{
				std::cout << "$USER_>";
			}
		}
		else
		{
			std::cout << "$USER_>";
		}

		std::string user_command = input();
		commands(user_command);
	}

	return 0;
}