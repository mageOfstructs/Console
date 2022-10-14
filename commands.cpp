#include "console.h"
#include "Class_Path.h"

Path commands_obj_Path;
struct input_struct commands_i_struct {};

int commands(std::string command)
{
	my_json::json global_vars_com = commands_obj_Path.init_data();

	if (command.find("message") != std::string::npos)
	{
		if (!global_vars_com.jbool[glv_connected].second)
		{
			std::cout << "Err/NotCon: To deliver a message to this system, you must first build up a connection" << std::endl;
			connecting();
			return 1;
		}
		else
		{
			kikai_response(command);
			return 2;
		}
	}
	else if (command.find("syntax") != std::string::npos)
	{
		std::cout << "call function_name(parameters separated by a ',')" << std::endl;
		std::cout << "Note: When using the commands() function there is only one parameter, a command. This command is divided in several sub_parameters, which are separated with a ' '" << std::endl;
		return 3;
	}
	else if (command.find("help") != std::string::npos)
	{
		std::cout << "help							display this list" << std::endl;
		std::cout << "connect							builds up a connection to the main station" << std::endl;
		std::cout << "message [message]					allows to communicate with main AI(note: only works if connection was successful" << std::endl;
		std::cout << "setup	 						executes 'New Home First Setup Protocols'" << std::endl;
		std::cout << "info [function_name]					Debugging only: returns information about the given function" << std::endl;
		std::cout << "call [function_name] [function_parameter(s)]		executes given function" << std::endl;
		std::cout << "							WARNING: Only for debugging: can heavily break the system," << std::endl;
		std::cout << "							Advanced knowledge of the system is advised" << std::endl;
		std::cout << "syntax							Outputs the syntax for call in detail" << std::endl;
		std::cout << "exit							closes the program" << std::endl;
		std::cout << "credits							outputs the creators" << std::endl;
		return 4;
	}
	else if (command.find("log_end") != std::string::npos)
	{
		log_end();
	}
	else if (command.find("exit") != std::string::npos)
	{
		bool log_s = log_end();

		if (log_s)
		{
			exit(0);
		}
	}
	else if (command.find("debug_glv") != std::string::npos)
	{
		my_json::json global_vars_com_s = commands_obj_Path.init_data();

		std::cout << "Logged in: " << global_vars_com_s.jbool[glv_logged_in].second << std::endl;
		std::cout << "Connected: " << global_vars_com_s.jbool[glv_connected].second << std::endl;
		std::cout << "Acc_n_locked: " << global_vars_com_s.jbool[glv_acc_n_locked].second << std::endl;
		std::cout << "Hacked: " << global_vars_com_s.jbool[glv_hacked].second << std::endl;
		std::cout << "Unlocked: " << global_vars_com_s.jbool[glv_unlocked].second << std::endl;
		std::cout << "Version: " << global_vars_com_s.jint[glv_version].second << std::endl;
		std::cout << "Config: " << global_vars_com_s.str[glv_config].second << std::endl;
		std::cout << "Username: " << global_vars_com_s.str[glv_username].second << std::endl;
		std::cout << "Log: ";

		for (int i = 0; i < global_vars_com.arr.str[glv_log].second.size(); i++)
		{
			std::cout << global_vars_com.arr.str[glv_log].second[i] << ",";
		}
		std::cout << std::endl;
	}
	else if (command.find("logon") != std::string::npos)
	{
		login();
		return 6;
	}
	else if (command.find("info") != std::string::npos)
	{
		// "intro()", "input()", "login()", "kikai_response", "commands", "connection()", "call()", "gen_ids()", "gen_o2()", "gen_cameras()", "gen_control_p()", "gen_factory()", "gen_power_p()"};
		if (command.find("intro") != std::string::npos)
		{
			std::cout << "--Intro(int time_index)--" << std::endl;
			std::cout << "Controls the intro output. Note: Function accepts an integer as parameter to act as a 'time index'. Through this index previous versions of the OS can be visited" << std::endl;
			return 7;
		}
		else if (command.find("input") != std::string::npos)
		{
			std::cout << "--Input()--" << std::endl;
			std::cout << "Allows the user to interact with the system. Note: Default value of input is: <string>, however there are overloads for other types..." << std::endl;
			return 8;
		}
		else if (command.find("login") != std::string::npos)
		{
			std::cout << "--Login(string username, string password)--" << std::endl;
			std::cout << "Login Algorithm. Note: While account locks are ineviteable on the normal interface are, maybe 'call' can do something?" << std::endl;
			return 9;
		}
		else if (command.find("kikai_response") != std::string::npos)
		{
			std::cout << "--Kikai_response(string message)--" << std::endl;
			std::cout << "The core of the console. Only through this function you are able to communicate with Kikai Yama. Dev_Note: We put several security codes in the system to prevent invalid input. Through a coding error we haven't put some in this function." << std::endl;
			return 10;
		}
		else if (command.find("commands") != std::string::npos)
		{
			std::cout << "--Commands(string command)--" << std::endl;
			std::cout << "Processes the user input. Note: To ensure none of the regular users can access admin commands, we put a barrier at the input() function" << std::endl;
			return 11;
		}
		else if (command.find("connect") != std::string::npos)
		{
			std::cout << "--Connection(string ip)" << std::endl;
			std::cout << "Connects client to a main server/other clients. Note: Default is <Kikai's Garden Mobile Station>" << std::endl;
			return 12;
		}
		else if (command.find("call") != std::string::npos)
		{
			std::cout << "--Call(string function_name, auto parameter(s))--" << std::endl;
			std::cout << "Debugging only. Can run single functions with given parameters. Note: Can heavily break the system as for the 'None without together'-Protocols the security codes must be in separate functions" << std::endl;
			return 13;
		}
		else if (command.find("gen_ids") != std::string::npos)
		{
			std::cout << "--Gen_ids(string auth_token)--" << std::endl;
			std::cout << "Connects devices. Note: The system can actually change its verification token, just give it in the parameter list and there you go." << std::endl;
			return 14;
		}
		else
		{
			std::cout << "Functions: " << std::endl;
			std::cout << "	intro(int time_index)" << std::endl;
			std::cout << "	input()" << std::endl;
			std::cout << "	login(string username, string password)" << std::endl;
			std::cout << "	kikai_response(string message)" << std::endl;
			std::cout << "	commands(string command)" << std::endl;
			std::cout << "	connection(string id)" << std::endl;
			std::cout << "	call(string function_name, auto parameter(s))" << std::endl;
			std::cout << "	gen_ids(string auth_token)" << std::endl;
			return 15;
		}
	}
	else if (command.find("setup") != std::string::npos)
	{
		std::cout << "<New Home First Setup Protocols>" << std::endl;
		std::cout << "<Kikai> Welcome on your new home, my child." << std::endl;
		std::cout << "<Kikai> These are prerecorded messages that will guide you through the basics of StarcorpOS\n and ensure that you can live in peace on this planet" << std::endl;
		std::cout << "To start the protocol please type 'continue'. If you want to exit, type 'cancel'" << std::endl;
		getline(std::cin, command);

		if (command == "continue")
		{
			std::cout << "<Kikai> Good. Now let's begin" << std::endl;
			std::cout << std::endl;
			std::cout << "<Kikai> The first step is to connect all of the vital life support devices through this OS." << std::endl;
			std::cout << "<Kikai> Please wait while the Starcorp Easy-Connection Scripts are being executed..." << std::endl;

			std::cout << std::endl;
			gen_ids();
			std::cout << std::endl;
			return 16;
		}
		else if (command == "cancel")
		{
			std::cout << "exiting protocols..." << std::endl;
			input();
			return 17;
		}

	}
	else if (command.find("credits") != std::string::npos)
	{
		std::cout << ">LIST PERSONELL" << std::endl;
		std::cout << "Story, main game, textures, minecraft map, Book -- KennithSimmons1111" << std::endl;
		std::cout << "Coding, algorithms, ID-Design -- mage_of_the_lost_souls" << std::endl;
		return 18;
	}
	else if (command.find("call") != std::string::npos)
	{
		// "intro()", "input()", "login()", "kikai_response", "commands", "connection()", "call()", "gen_ids()", "gen_o2()", "gen_cameras()", "gen_control_p()", "gen_factory()", "gen_power_p()"};

		call_com(command, global_vars_com, commands_i_struct);
	}
	else if (global_vars_com.jbool[glv_hacked].second)
	{
		if (command.find("override") != std::string::npos)
		{
			std::string sub_command = command.substr(command.find("override"));
			int end = sub_command.find(")");
			int dif = end - 9;
			std::string actual_str = sub_command.substr(9, dif);

			if (actual_str == "Kikai" || actual_str == "kikai")
			{
				std::cout << "<Kikai> Hahaha. Did you really thought you could that easily defeat me? I put that security leak intentionally there to lure traitors in." << std::endl;
				std::cout << "||WARNING|| E+/%§///otFoundd Files are missing. C§n##ct y11r a43§n)(=r???on" << std::endl;
				return 29;
			}
			else if (actual_str == "Server" || actual_str == "server")
			{
				if (!global_vars_com.jbool[glv_connected].second)
				{
					connecting();
				}
				std::string input;
				std::string path = "SERVER/";
				while (input != "exit")
				{
					std::cout << "<Server Console>" << std::endl;
					std::cout << path << ">";
					getline(std::cin, input);
					std::cout << std::endl;

					if (input == "help")
					{
						std::cout << "help" << std::endl;
						std::cout << "stop" << std::endl;
						std::cout << "goto" << std::endl;
						std::cout << "delete" << std::endl;
						std::cout << "clear" << std::endl;
						std::cout << "ban" << std::endl;
						std::cout << "unban" << std::endl;
						std::cout << "exit" << std::endl;
					}
					else if (input == "stop")
					{
						std::cout << "[SERVER] Shutdown initiated" << std::endl;
						std::cout << "[SERVER] stopping tasks..." << std::endl;
						std::cout << std::endl;
						std::cout << "<Kikai> Wait no-" << std::endl;
						std::cout << "[SERVER] Task rationsys0_4.exe was terminated" << std::endl;
						std::cout << "[SERVER] all server resources cleared" << std::endl;
						std::cout << "[SERVER] reducing power of main servers to 1.23 KWh" << std::endl;
						std::cout << "<Austin> why di-" << std::endl;
						std::cout << "[SERVER] Console closed;" << std::endl;
						break;
					}
					else if (input.find("goto") != std::string::npos)
					{
						std::string folder = input.substr(5);

						path += folder + "/";
					}
					else if (input.find("delete") != std::string::npos)
					{
						std::cout << "File " << input.substr(7) << " deleted" << std::endl;
					}
					else if (input.find("clear") != std::string::npos)
					{
						std::cout << "clearing server " << input.at(6) << std::endl;
					}
					else if (input.find("unban") != std::string::npos)
					{
						fs::path p = fs::current_path();
						std::string ban_ips = "bannen_ips.json";
						p /= ban_ips;
						if (fs::exists(p))
						{
							my_json::json ban_data;
							my_json::json_args_obj banned_ips;
							my_json::read_json(ban_ips, ban_data);
							banned_ips = ban_data.arr.obj[0].second;

							int first_param_end = input.find(",");
							std::string input_username = input.substr(4, first_param_end); // 10

							for (my_json::json_raw::iterator it = banned_ips[0].second.begin(); it != banned_ips[0].second.end(); it++)
							{
								if (std::get<0>(*it) == input_username)
								{
									banned_ips[0].second.erase(it);
									break;
								}
							}
						}
						else
						{
							my_json::json new_ban_data("ban_ip");

						}
					}
					else if (input.find("ban") != std::string::npos)
					{
						fs::path p = fs::current_path();
						std::string ban_ips = "bannen_ips.json";
						p /= ban_ips;
						if (fs::exists(p))
						{
							my_json::json ban_data;
							my_json::json_args_obj banned_ips;
							my_json::read_json(ban_ips, ban_data);
							banned_ips = ban_data.arr.obj[0].second;

							int first_param_end = input.find(",");
							std::string input_username = input.substr(4, first_param_end); // 10
							int second_param_begin = first_param_end + 1;
							int second_param_end = input.size() - 1;
							int dif = second_param_end - second_param_begin;
							std::string input_ip = input.substr(second_param_begin, dif);

							banned_ips[0].second.push_back({input_username, input_ip, "string"});

							for (int i = 1; i < banned_ips.size(); i++)
							{
								ban_data.arr.obj[0].second[i] = banned_ips[i];
							}
						}
						else
						{
							my_json::json new_ban_data("ban_ip");

						}
					}
				}
				return 30;
			}
		}
		else if (command.find("shutdown") != std::string::npos)
		{
			std::cout << "||WARNING|| Only the head_admin has access to this. Please do not contact him about that and forget that this command even exists." << std::endl;
			std::string input;
			getline(std::cin, input);

			if (input == "INITIATE")
			{
				std::cout << "Access Denied" << std::endl;
				return 31;
			}
			else
			{
				return 32;
			}
		}
		else if (command.find("access") != std::string::npos)
		{
			std::filesystem::path folder_accessed;
			auto this_path = std::filesystem::current_path();

			int end_folder = command.find(")");
			int dif = end_folder - 7;
			folder_accessed += command.substr(7, dif);

			this_path /= folder_accessed;
			std::cout << "´changed primary directory to " << folder_accessed << std::endl;
			return 33;
		}
		else
		{
			if (!command.empty())
			{
				std::cout << "Error 404: Command not found" << std::endl;
				return 34;
			}
			else
			{
				std::cout << "Error 405: Empty Command" << std::endl;
				return 35;
			}
		}
	}
	else if (command.find("connect") != std::string::npos)
	{
		connecting();
		return 36;
	}
	else
	{
		std::cout << "Error: Unknown Command" << std::endl;
		return 37; 
	}
}