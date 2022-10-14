#include "json_ns.h"

using namespace my_json;

my_json::json::json(std::string type)
{
	if (type == "account")
	{
		std::pair<std::string, std::string> username("Username", "Unregistered User");
		std::pair<std::string, std::string> password("Password", "");
		std::pair<std::string, bool> is_admin("is_admin", false);
		std::pair<std::string, std::string> status("status", "user");
		std::pair<std::string, bool> locked("locked", false);

		this->str.push_back(username);
		this->str.push_back(password);
		this->jbool.push_back(is_admin);
		this->str.push_back(status);
		this->jbool.push_back(locked);
	}
	else if (type == "glv")
	{
		std::string f_e = "  --System Log--  ";
		std::vector<std::string> log_val;
		log_val.push_back(f_e);

		std::pair<std::string, bool> logged_in("logged_in", false);
		std::pair<std::string, bool> connected("connected", false);
		std::pair<std::string, bool> acc_n_locked("acc_n_locked", false);
		std::pair<std::string, bool> hacked("hacked", false);
		std::pair<std::string, bool> unlocked("unlocked", false);
		std::pair<std::string, int> version("version", 0);
		std::pair<std::string, std::string> config("config", "default");
		std::pair<std::string, std::string> username("username", "Unregistered User");
		std::pair<std::string, std::vector<std::string>> log("log", log_val);

		this->jbool.push_back(logged_in);
		this->jbool.push_back(connected);
		this->jbool.push_back(acc_n_locked);
		this->jbool.push_back(hacked);
		this->jbool.push_back(unlocked);
		this->jint.push_back(version);
		this->str.push_back(config);
		this->str.push_back(username);
		this->arr.str.push_back(log);
	}
	else if (type == "ban_ip")
	{
		std::vector<std::string> sec(1, "295.234.234.3");

		std::pair<std::string, std::vector<std::string>> banned("Banned", sec);

		this->arr.str.push_back(banned);
	}
	else if (type == "devices")
	{
		std::vector<std::string> cams;

		std::pair<std::string, std::string> o2("O2 Generator", "");
		std::pair<std::string, std::string> fac("Factory", "");
		std::pair<std::string, std::string> cc("Control Panel", "");
		std::pair<std::string, std::string> pp("Power Plant", "");
		std::pair<std::string, std::vector<std::string>> cam("Cameras", cams);

		this->str.push_back(o2);
		this->str.push_back(fac);
		this->str.push_back(cc);
		this->str.push_back(pp);
		this->arr.str.push_back(cam);
	}
	else if (type == "user_d")
	{
		std::pair<std::string, std::string> threat_lvl("Threat_lvl", "neutral");

		this->str.push_back(threat_lvl);
	}
	else
	{
		std::cout << "Error: Unknown type!" << std::endl;
	}
}

std::string my_json::convert_json_obj(my_json::json_args_obj raw_obj)
{
	std::string ret = "{ ";

	for (int i = 0; i < raw_obj.size(); i++)
	{
		std::vector<std::string> temp = my_json::convert_json(raw_obj[i].second);

		for (int j = 0; j < temp.size(); j++)
		{
			ret += temp[i];
		}
	}

	ret += " }";
	return ret;
}