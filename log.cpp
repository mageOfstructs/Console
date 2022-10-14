#include "console.h"
#include "Class_Path.h"
#pragma warning(suppress : 4996)

Path log_obj_Path;
std::string full_log;

std::string get_log_file()
{

	time_t theTime = time(NULL);
	struct tm* aTime = localtime(&theTime);
	int mon = aTime->tm_mon + 1;
	int year = aTime->tm_year + 1900;
	std::string file_name = "log-";
	file_name += std::to_string(mon);
	file_name += "_";
	file_name += std::to_string(aTime->tm_mday);
	file_name += "_";
	file_name += std::to_string(year);
	file_name += ".txt";

	return file_name;
}

std::string log_add(std::string command)
{
	my_json::json glv_add = log_obj_Path.init_data();
	std::string log;

	std::string str = "[LOG] ";
	str += glv_add.str[glv_username].second;
	str += " executed '";
	log += str;
	log += command;
	log += "'";

	glv_add.arr.str[glv_log].second.push_back(log);
	my_json::conandwrite(glv_add, log_obj_Path.get_glv_path());

	return log;
}

bool log_end()
{
	my_json::json glv_end = log_obj_Path.init_data();
	fs::path log_path = log_obj_Path.get_log_path();
	log_path /= get_log_file();
	std::ofstream ofs(log_path);

	for (int i = 0; i < glv_end.arr.str[glv_log].second.size(); i++)
	{
		ofs << glv_end.arr.str[glv_log].second[i];
		ofs << '\n';
	}

	ofs << "\n Copyright StarCorporation @ 2099";
	ofs.close();

	glv_end.arr.str[glv_log].second.clear();
	glv_end.arr.str[glv_log].second.push_back("  --System Log--  ");

	my_json::conandwrite(glv_end, log_obj_Path.get_glv_path());

	return true;
}