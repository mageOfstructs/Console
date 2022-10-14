#include "console.h"
#include "Class_Path.h"

Path pre_Kikai_obj_Path;

void connecting()
{
	my_json::json global_vars_con = pre_Kikai_obj_Path.init_data();
	char answer;
	std::cout << "<Remote connection to Kikais Garden Mobile Station>" << std::endl;
	std::cout << "Do you want to proceed? (Y/N) ";
	std::cin >> answer;
	std::cout << std::endl;

	if (answer == 'Y')
	{
		std::string id;
		std::string band_w;
		unsigned int seed = time(0);
		std::mt19937_64 ran_gen{ seed };
		std::uniform_int_distribution<int> ran_dist{ 48,57 };
		std::cout << "Searching for available connection ports..." << std::endl;

		for (int i = 0; i < 4; i++)
		{
			id += ran_dist(ran_gen);
		}

		std::cout << "Port: " << id << " is currently available." << std::endl;
		std::cout << "Establishing connection over Port " << id << "..." << std::endl;
		std::cout << "Testing Port Bandwidth..." << std::endl;

		for (int i = 0; i < 3; i++)
		{
			band_w += ran_dist(ran_gen);
		}
		std::cout << "Bandwidth is: " << band_w << " Hz" << std::endl;
		std::cout << std::endl;
		std::cout << "Sending Test Package..." << std::endl;
		std::cout << "Package Arrived\, no failures" << std::endl;
		std::cout << "Connection Established" << std::endl;
		std::cout << std::endl;

		if (global_vars_con.jbool[glv_logged_in].second == false)
		{
			std::cout << "Error/AccDenied: This system only accepts messages from logged in users." << std::endl;
			std::cout << "Do you wish to get redirected to the login screen? (Y/N)" << std::endl;
			std::cout << ">";
			std::cin >> answer;
			std::cout << std::endl;

			if (answer == 'Y')
			{
				login();
			}
			else if (answer == 'N')
			{
				std::cout << "exiting..." << std::endl;
			}
			else
			{
				std::cout << "Error 404: Command not found" << std::endl;
			}
		}
		else
		{
			global_vars_con.jbool[glv_connected].second = true;
		}
	}
	else if (answer == 'N')
	{
		std::cout << "exiting..." << std::endl;
	}
	else
	{
		std::cout << "Error 404: Command not found" << std::endl;
	}
}