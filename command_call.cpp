#include "console.h"
#include "json_ns.h"

int call_com(std::string command, my_json::json global_vars_com, struct input_struct commands_i_struct)
{
	std::string func = command.substr(5);

	if (func.find("login") != std::string::npos)
	{
		global_vars_com.jbool[glv_hacked].second = true;
		std::string param = func.substr(6);
		int first_param_end = param.find(",");
		std::string input_username = param.substr(0, first_param_end); // 10
		int second_param_begin = first_param_end + 1;
		int second_param_end = param.size() - 1;
		int dif = second_param_end - second_param_begin;
		std::string input_password = param.substr(second_param_begin, dif);

		if (input_username == "Kikai")
		{
			if (input_password == "answer")
			{
				std::cout << "Well done." << std::endl;
			}
		}
		auto this_path = std::filesystem::current_path();
		std::string file_name = input_username + ".json";
		this_path /= file_name;
		if (std::filesystem::exists(this_path))
		{
			my_json::json user_data;
			std::string raw = my_json::read_json_raw(this_path);
			my_json::read_json_str(raw, user_data);

			if (user_data.jbool[acc_is_admin].second)
			{
				std::cout << "Welcome Admin." << std::endl;
				return 19;
			}
			else
			{
				return 20;
			}
		}
		else
		{
			my_json::json acc_data("account");
			acc_data.str[acc_username].second = input_username;
			acc_data.str[acc_password].second = input_password;
			acc_data.jbool[acc_is_admin].second = false;
			my_json::json_raw raw = my_json::gen_json_raw(acc_data);
			std::vector<std::string> lines = my_json::convert_json(raw);
			my_json::write_json(lines, this_path);

			std::cout << "Account created" << std::endl;
			return 21;
		}
	}
	else if (func.find("commands") != std::string::npos)
	{
		global_vars_com.jbool[glv_hacked].second = true;
		std::string sub_command = func.substr(9);

		commands(sub_command);
		return 22;
	}
	else if (func.find("kikai_response") != std::string::npos)
	{
		global_vars_com.jbool[glv_unlocked].second = true;

		int sub_begin = func.find("(") + 1;
		int sub_end = func.find(")");
		int dif = sub_end - sub_begin;
		std::string message = func.substr(sub_begin, dif);
		std::cout << message << std::endl;

		kikai_response(message, true);
		return 23;
	}
	else if (func.find("intro") != std::string::npos)
	{
		int func_end = func.find(")");
		int dif = func_end - 6;
		std::string index = func.substr(6, dif);
		int int_index = stoi(index);
		intro(int_index);
		return 24;
	}
	else if (func.find("input") != std::string::npos)
	{
		int param_end = func.find(")");
		int dif = param_end - 6;
		std::string param = func.substr(6, dif);

		run_input_func(param, commands_i_struct);
		return 25;
	}
	else if (func.find("connecting") != std::string::npos)
	{
		if (func.find("kikai") != std::string::npos)
		{
			connecting();
			return 26;
		}
		else if (func.find("NIF-Movement") != std::string::npos)
		{
			std::cout << "Searching for available connection ports..." << std::endl;
			std::cout << "Err/FirewallReject The ip your trying to connect is labeled as dangerous/incorrect." << std::endl;
			return 27;
		}
	}
	else
	{
		std::cout << "Error: Unknown Function" << std::endl;
		return 28;
	}
}