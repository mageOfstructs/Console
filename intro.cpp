#include "console.h"
#include "Class_Path.h"

Path intro_obj_Path;

void intro(int time_i)
{
	my_json::json global_vars_intro = intro_obj_Path.init_data();

	if (time_i >= 2056 && time_i <= 2071) // 2056 to 2071
	{
		struct tm time_data {};
		std::string time;
		std::string date;
		std::stringstream sstr;
		int months = time_data.tm_mon;
		int days = time_data.tm_mday;
		time = "E.DATE/TIME: ";
		sstr << days << "/" << months << "/2033 " << time_data.tm_hour << ":" << time_data.tm_min;
		sstr >> date;
		time += date;

		std::cout << "# Starlight Electronics" << std::endl;
		std::cout << time << std::endl;
		std::cout << std::endl;

		global_vars_intro.jint[glv_version].second = time_i;
	}
	else if (time_i >= 2072)
	{
		std::cout << "StarlightOS: consumer version/Kikai communication system active" << std::endl;
		std::cout << "Copyright 2099 @ Starcorp Corperation" << std::endl;
		std::cout << "Do not distribute" << std::endl;
		std::cout << std::endl;
	}
	else if (time_i >= 2041 && time_i <= 2055) // 2041 to 2055
	{
		struct tm time_struct {};
		std::stringstream sstr;
		std::string time_f;
		sstr << time_struct.tm_wday << "/" << time_struct.tm_mon << "/2039";
		sstr >> time_f;

		std::cout << ">>SDC QuickComputerAccessProgram  V2.5" << std::endl;
		std::cout << ">client license active			" << time_f << std::endl;
		std::cout << ">Copyright 2039 @ All rights reserved" << std::endl;
		std::cout << std::endl;

		global_vars_intro.jint[glv_version].second = time_i;
	}
	else
	{
		std::cout << "Err/BackupNotFound" << std::endl;
	}
}