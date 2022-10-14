#include "console.h"
#include "Class_Path.h"

Path input_obj_Path;

std::string input()
{
	std::string input_user; 
	getline(std::cin, input_user);
	log_add(input_user);

	return input_user;
}

std::filesystem::path input_f()
{
		std::string input_type;
		getline(std::cin, input_type);

		int end = input_type.find(")");
		int dif = end - 5;
		std::string input_f = input_type.substr(5, dif);
		char begin = 'C';

		if (input_f.at(0) != begin)
		{
			std::filesystem::path absolute_p = std::filesystem::current_path();
			absolute_p /= input_f;

			return absolute_p;
		}
		else
		{
			return input_f;
		}
}

void run_input_func(std::string input_param, struct input_struct i_struct)
{

	if (input_param.find("string") != std::string::npos)
	{
		int end = input_param.find(")");
		int dif = end - 7;
		auto ret_val = input_param.substr(7, dif);

		i_struct.ret_str = ret_val;
	}
	else if (input_param.find("file") != std::string::npos)
	{
		std::filesystem::path ret_val_f = input_f();
		i_struct.ret_p = ret_val_f;
	}
	else if (input_param.find("integer") != std::string::npos)
	{
		int end = input_param.find(")");
		int dif = end - 8;
		auto ret_val_int = input_param.substr(8, dif);
		int result = stoi(ret_val_int);

		i_struct.ret_int = result;
	}
	else if (input_param.find("config") != std::string::npos)
	{
		std::filesystem::path path = "Console_Config/system/config";
		int end = input_param.find(")");
		int dif = end - 7;
		std::string config = input_param.substr(7, dif);
		path /= config;

		if (!std::filesystem::exists(path))
		{
			std::cout << "Error/FileNotFound The system could not find this file" << std::endl;
		}
		else
		{
			my_json::json log_data = input_obj_Path.init_data();
			log_data.str[glv_config].second = "custom";
		}
	}
	else
	{
		i_struct.ret_str = input();
	}

}