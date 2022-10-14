#include "console.h"
#include "Class_Path.h"
#include "json_ns.h"

Path login_obj_Path;

void new_acc(std::string &username, std::string &password, std::string &file_name, my_json::json &global_vars_login)
{
	my_json::json account("account");

	std::cout << "creating new account..." << std::endl;
	std::cout << "Please enter a username: ";
	getline(std::cin, username);

	account.str[acc_username].second = username;

	std::cout << "Please enter a password: ";
	getline(std::cin, password);

	account.str[acc_password].second = password;

	account.jbool[acc_is_admin].second = false;

	account.str[acc_status].second = "user";

	account.jbool[acc_is_locked].second = false;

	file_name = username;
	file_name += ".json";
	std::filesystem::path path = std::filesystem::current_path();
	path /= "Console_Config/users";
	path /= file_name;
	my_json::json_raw raw = my_json::gen_json_raw(account);
	std::vector<std::string> file_content = my_json::convert_json(raw);
	my_json::write_json(file_content, path);

	std::cout << "successfully created " << username << ".json" << std::endl;
	global_vars_login.jbool[glv_logged_in].second = true;
	global_vars_login.arr.str[glv_log].second.push_back("[SYSTEM] successfully logged on as " + username);
	global_vars_login.str[glv_username].second = username;
	my_json::json_raw raw2 = my_json::gen_json_raw(global_vars_login);
	std::vector<std::string> lines = my_json::convert_json(raw2);
	my_json::write_json(lines, login_obj_Path.get_glv_path());
}

void check_password(my_json::json j_data, std::string password, int i = 0)
{
	my_json::json global_vars_cpswd = login_obj_Path.init_data();

	if (j_data.str[acc_password].second == password)
	{
		std::cout << "Access Granted" << std::endl;
		global_vars_cpswd.jbool[glv_logged_in].second = true;
	}
	else
	{
		if (i != 3)
		{
			std::cout << "Password>";
			getline(std::cin, password);
			i++;

			check_password(j_data, password, i);
		}
		else
		{
			std::cout << "Error: More than 3 incorrect password inputs!" << std::endl;
		}
	}
}

std::string re_enter_username(std::string old_username)
{
	std::cout << "Username>";
	getline(std::cin, old_username);

	return old_username;
}

std::string do_user_input_login(std::string username)
{
	std::string password;
	std::cout << "Username " << username << " found" << std::endl;

	std::cout << "Password>";
	getline(std::cin, password);

	return password;
}

int login()
{
	my_json::json global_vars_login = login_obj_Path.init_data();
	my_json::json data("account");
	std::string username;
	std::string password;
	std::string file_name;

	std::cout << "<Login Protocols>" << std::endl;
	std::cout << "Hint: type 'new' to create a new account" << std::endl;
	std::cout << "Username>";
	getline(std::cin, username);

	if (username == "new")
	{
		username.clear();

		new_acc(username, password, file_name, global_vars_login);

		return 0;
	}
	else
	{
		fs::path user_path = login_obj_Path.get_users_path();
		file_name = username;
		file_name += ".json";
		user_path /= file_name;

		if (fs::exists(user_path))
		{
			std::cout << "Err/AccNotFound This username does not exist" << std::endl;
			char yn;
			std::cout << "Create Account File(Y/N)? ";
			std::cin >> yn;
			std::cout << std::endl;

			if (yn == 'Y')
			{
				data.str[acc_username].second = username;

				data.str[acc_password].second = password;

				file_name = username;
				file_name += ".json";
				std::filesystem::path path = std::filesystem::current_path();
				path /= "Console_Config/users";
				path /= file_name;

				my_json::conandwrite(data, path);

				std::cout << "successfully created " << username << ".json" << std::endl;
				global_vars_login.jbool[glv_logged_in].second = true;
				global_vars_login.str[glv_username].second = username;
				global_vars_login.arr.str[glv_log].second.push_back("[SYSTEM] successfully logged on as " + username);
			}
		}
		else
		{
			std::string raw = my_json::read_json_raw(user_path);
			my_json::read_json_str(raw, data);

			std::string password = do_user_input_login(username);
			if (data.jbool[acc_is_locked].second)
			{
				if (global_vars_login.jbool[glv_hacked].second == true)
				{
					std::cout << "Welcome User " << data.str[glv_username].second << std::endl;
					global_vars_login.arr.str[glv_log].second.push_back("[SYSTEM] successfully logged on as " + username);
					global_vars_login.jbool[glv_logged_in].second = true;
					global_vars_login.str[glv_username].second = username;
				}
				else
				{
					std::cout << "Err/LockedAcc Sorry, but you can only log into this account, when you're in a specific location" << std::endl;
					global_vars_login.jbool[glv_acc_n_locked].second = true;
					return 1;
				}
			}
			else
			{
				check_password(data, password);
				global_vars_login.str[glv_username].second = username;
				return 0;
			}
		}
	}

	return 1;
}