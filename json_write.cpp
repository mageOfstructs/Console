#include "json_ns.h"

std::vector<std::string> my_json::str_to_arr(std::string raw_arr)
{
	int j = 0;
	std::vector<int> commas;
	std::vector<std::string> elements;

	for (int i = 0; i < raw_arr.size(); i++)
	{
		if (raw_arr[i] == ',')
		{
			int dif = i - j;
			elements.push_back(raw_arr.substr(j, dif));

			j = ++i;
		}
	}

	elements.push_back(raw_arr.substr(j));

	return elements;
}

my_json::json_args_str my_json::str_to_obj(std::string raw_arr)
{
	my_json::json_args_str ret;
	int j = 0;
	std::vector<std::string> args;

	// separate object's arguments
	for (int i = 0; i < raw_arr.size(); i++)
	{
		if (raw_arr[i] == ',')
		{
			int dif = i - j;
			args.push_back(raw_arr.substr(j, dif));

			j = ++i;
		}
	}

	j = 0;
	// separate key from val
	for (int i = 0; i < args.size(); i++)
	{
		for (int k = 0; k < args[i].size(); k++)
		{
			if (args[i][k] == ':')
			{
				std::pair<std::string, std::string> temp;
				int val_begin = k + 2;
				int val_end = args[i].size() - 1;

				temp.first = args[i].substr(0, k);
				temp.second = args[i].substr(val_begin, val_end);

				ret.push_back(temp);
			}
		}
	}

	return ret;
}

std::string my_json::convert_arr_str(std::vector<std::string> arr) // uses pair
{
	std::string ret;
	int last_e = arr.size() - 1;

	for (int i = 0; i < arr.size(); i++)
	{
		ret += "\"";
		ret += arr[i];
		ret += "\"";

		if (i != last_e)
		{
			ret += ", ";
		}
	}

	return ret;
}

std::string my_json::convert_arr_obj(my_json::json_args_arr_obj raw)
{
	std::string ret = "[";
	bool is_last = false;

	for (int i = 0; i < raw.size(); i++)
	{
		if (i == (raw.size() - 1))
		{
			is_last = true;
		}

		ret += my_json::convert_json_obj(raw[i].second);
	}

	ret += "]";
	return ret;
}

std::vector<std::string> my_json::convert_json(my_json::json_raw raw, bool is_obj)
{
	std::vector<std::string> ret;
	ret.push_back("{\n");

	for (int i = 0; i < raw.size(); i++)
	{
		std::string temp;
		std::string key = std::get<0>(raw[i]);
		std::string val = std::get<1>(raw[i]);
		std::string type = std::get<2>(raw[i]);

		temp += "\"";
		temp += key;
		temp += "\"";

		temp += ": ";

		if (type == "string")
		{
			temp += "\"";
			temp += val;
			temp += "\"";
			if (i != (raw.size() - 1))
			{
				temp += ", // string\n";
			}
			else
			{
				temp += "// string\n";
			}
		}
		else if (type == "int")
		{
			temp += val;
			if (i != (raw.size() - 1))
			{
				temp += ", // int\n";
			}
			else
			{
				temp += "// int\n";
			}
		}
		else if (type == "bool")
		{
			temp += val;
			if (i != (raw.size() - 1))
			{
				temp += ", // bool\n";
			}
			else
			{
				temp += "// bool\n";
			}
		}
		else if (type.find("array") != std::string::npos)
		{
			if (type == "array-string")
			{
				temp += "[ ";
				temp += val;
				temp += " ]";

				if (i != (raw.size() - 1))
				{
					temp += ", // array-string\n";
				}
				else
				{
					temp += "// array-string\n";
				}
			}
			else if (type == "array-object")
			{
				temp += "[ ";
				temp += val;
				temp += " ]";

				if (i != (raw.size() - 1))
				{
					temp += ", // array-object\n";
				}
				else
				{
					temp += "// array-object\n";
				}
			}
		}
		else if (type == "object")
		{
			temp += val;
			if (i != (raw.size() - 1))
			{
				temp += ", // object\n";
			}
			else
			{
				temp += "// object\n";
			}
		}
		else
		{
			std::cout << "Error: Unknown Type for JSON Convertion";
			temp += "N/A";
		}

		ret.push_back(temp);
	}
	
	if (is_obj)
	{
		ret.push_back("}");
	}
	else
	{
		ret.push_back("}\n");
	}
	return ret;
}

void my_json::write_json(std::vector<std::string> json_lines, fs::path path)
{
	std::ofstream ofs(path);

	for (int i = 0; i < json_lines.size(); i++)
	{
		ofs << json_lines[i];
	}

	ofs.close();
}

void my_json::conandwrite(my_json::json obj, fs::path path)
{
	my_json::json_raw raw = my_json::gen_json_raw(obj);
	std::vector<std::string> lines = my_json::convert_json(raw);

	my_json::write_json(lines, path);
}

my_json::json_raw my_json::gen_json_raw(json obj)
{
	json_raw ret;

	std::string com_str = "string";
	std::string com_int = "int";
	std::string com_bool = "bool";
	std::string com_arr_str = "array-string";
	std::string com_arr_obj = "array-object";
	std::string com_obj = "object";

	for (int i = 0; i < obj.str.size(); i++)
	{
		std::tuple<std::string, std::string, std::string> raw_str(obj.str[i].first, obj.str[i].second, com_str);
		ret.push_back(raw_str);
	}

	for (int i = 0; i < obj.jint.size(); i++)
	{
		std::tuple<std::string, std::string, std::string> raw_str(obj.jint[i].first, std::to_string(obj.jint[i].second), com_int);
		ret.push_back(raw_str);
	}

	for (int i = 0; i < obj.jbool.size(); i++)
	{
		std::tuple<std::string, std::string, std::string> raw_str(obj.jbool[i].first, std::to_string(obj.jbool[i].second), com_bool);
		ret.push_back(raw_str);
	}

	for (int i = 0; i < obj.arr.str.size(); i++)
	{
		std::tuple<std::string, std::string, std::string> raw_str(obj.arr.str[i].first, my_json::convert_arr_str(obj.arr.str[i].second), com_arr_str);
		ret.push_back(raw_str);
	}

	for (int i = 0; i < obj.arr.obj.size(); i++)
	{
		std::tuple<std::string, std::string, std::string> raw_str(obj.arr.obj[i].first, my_json::convert_arr_obj(obj.arr.obj), com_arr_obj);
		ret.push_back(raw_str);
	}

	for (int i = 0; i < obj.obj.size(); i++)
	{
		std::vector<std::string> lines = my_json::convert_json(obj.obj[i].second, true);
		std::string value;

		for (int j = 0; j < lines.size(); j++)
		{
			value += lines[j];
		}

		std::tuple<std::string, std::string, std::string> raw_str(obj.obj[i].first, value, com_obj);
		ret.push_back(raw_str);
	}

	return ret;
}

std::string my_json::gen_json(my_json::json_raw raw_arr)
{
	std::string ret;
	std::vector<std::string> temp;

	ret += "{\n";

	temp = my_json::convert_json(raw_arr);

	for (int i = 0; i < temp.size(); i++)
	{
		ret += temp[i];
	}

	ret += "}";
	return ret;
}
