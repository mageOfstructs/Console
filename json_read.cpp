#include "json_ns.h"

std::vector<std::string> my_json::rconvert_arr(std::string raw_json)
{
	int j = 0;
	std::vector<std::string> ret;

	for (int i = 0; i < raw_json.size(); i++)
	{
		if (raw_json[i] == '\"')
		{
			int dif = i - j;
			ret.push_back(raw_json.substr(j, dif));

			int off = i++;
			j = raw_json.find("\"", off) + 1;
		}
	}

	ret.erase(ret.begin());

	for (std::vector<std::string>::iterator it = ret.begin(); it != ret.end(); it++)
	{
		if (*it == ", ")
		{
			ret.erase(it);
			it = ret.begin();
		}
	}

	return ret;
}

std::string my_json::read_json_raw(std::string filename)
{
	std::string ret;
	std::string temp;
	std::ifstream ifs(filename);

	do
	{
		getline(ifs, temp);
		if (temp != "")
		{
			ret += temp;
			ret += '\n';
		}
	} while (!temp.empty());

	ifs.close();
	return ret;
}

std::string my_json::read_json_raw(fs::path path)
{
	std::string ret;
	std::ifstream ifs(path);
	std::string temp_line;

	do {
		getline(ifs, temp_line);
		if (temp_line != "")
		{
			ret += temp_line;
			ret += '\n';
		}
	} while (!temp_line.empty());

	ifs.close();
	return ret;
}

my_json::json_raw read_obj_str(std::string raw)
{
	int j = 0;
	my_json::json_raw ret;
	std::vector<std::string> lines;

	for (int i = 0; i < raw.size(); i++)
	{
		if (raw[i] == '\n')
		{
			int dif = i - j;

			lines.push_back(raw.substr(j, dif));

			j = ++i;
		}
	}

	if (lines.size() == 0)
	{
		lines.push_back(raw);
	}

	for (int i = 0; i < lines.size(); i++)
	{
		int i_semic = lines[i].find('/') + 2;
		int i_break = lines[i].find('\n');
		int dif = i_break - i_semic;
		std::string comment = lines[i].substr(++i_semic, dif);

		int f_quote = lines[i].find("\"");
		int next_q = lines[i].find("\"", ++f_quote);
		dif = next_q - ++f_quote;
		std::string key = lines[i].substr(++f_quote, dif);

		int begin = lines[i].find(":") + 2;
		int coma = lines[i].find(",");
		if (coma == std::string::npos)
		{
			coma = lines[i].find("/");
		}
		dif = coma - begin;
		std::string value = lines[i].substr(begin, dif);

		ret.push_back(std::tuple<std::string, std::string, std::string>(key, value, comment));
	}

	return ret;
}

std::string my_json::find_key(std::string json_line)
{
	int dif = json_line.find('\"', 2) - 1;

	std::string ret = json_line.substr(1, dif);
	return ret;
}

std::string my_json::find_val(std::string json_line)
{
	int placeholder = json_line.find(" ");
	int val_begin;
	int val_end;
	bool is_string = false;

	if (json_line.find("[") != std::string::npos)
	{
		val_begin = json_line.find("[") + 1;
	}
	else if (json_line.find("\"", placeholder) != std::string::npos)
	{
		val_begin = json_line.find("\"", placeholder) + 1;
		is_string = true;
	}
	else
	{
		val_begin = ++placeholder;
		is_string = false;
	}

	if (json_line.find_last_of("]") != std::string::npos)
	{
		val_end = json_line.find_last_of("]");
	}
	else if (json_line.find(',') != std::string::npos)
	{
		val_end = json_line.find(',');
	}
	else
	{
		val_end = json_line.find('/');
	}

	int dif;
	if (is_string)
	{
		dif = val_end - val_begin - 1;
	}
	else
	{
		dif = val_end - val_begin;
	}
	std::string ret = json_line.substr(val_begin, dif);
	return ret;
}

void my_json::read_json_str(std::string raw, my_json::json& obj) // uses pair
{
	int j = 0;
	std::vector<std::string> lines;
	std::string comment;
	int i_semic;
	int i_break;
	int dif;

	// slice raw into JSON lines
	for (int i = 0; i < raw.size(); i++)
	{
		if (raw[i] == '\n')
		{
			int dif = i - j;

			lines.push_back(raw.substr(j, dif));

			j = ++i;
		}
	}

	// read json
	for (int i = 1; i < lines.size(); i++)
	{
		if (lines[i] == "}")
		{
			break;
		}

		// find type comments
		i_semic = lines[i].find('/') + 2;
		i_break = lines[i].find('\n');
		dif = i_break - i_semic;
		comment = lines[i].substr(++i_semic, dif);

 		if (comment == "int")
		{
			std::pair<std::string, int> int_ret(find_key(lines[i]), stoi(find_val(lines[i])));
			obj.jint.push_back(int_ret);
		}
		else if (comment == "string")
		{
			std::pair<std::string, std::string> str_ret(find_key(lines[i]), find_val(lines[i]));
			obj.str.push_back(str_ret);
		}
		else if (comment == "bool")
		{
			bool val;
			std::string val_str = find_val(lines[i]);
			if (val_str == "1")
			{
				val = 1;
			}
			else if (val_str == "0")
			{
				val = 0;
			}
			else
			{
				std::cout << "Error: Not a bool!" << std::endl;
			}

			std::pair<std::string, bool> bool_ret(find_key(lines[i]), val);
			obj.jbool.push_back(bool_ret);
		}
		else if (comment.find("array") != std::string::npos || comment.find("[") != std::string::npos)
		{
			if (comment == "array-string")
			{
				std::string key_arr = find_key(lines[i]);
				std::vector<std::string> val_arr = rconvert_arr(find_val(lines[i]));
				std::pair<std::string, std::vector<std::string>> pushb(key_arr, val_arr);
				obj.arr.str.push_back(pushb);
			}
			else if (comment == "array-object")
			{
				std::string key_obj = find_key(lines[i]);

				my_json::json_args_obj val;



				int bracketb = lines[i].find("[");
				int brackete = lines[i].find("]") + 1;
				int dif = brackete - bracketb;
				std::string arr_val = lines[i].substr(bracketb, dif);
				std::vector<std::pair<int, int>> obj_indexes;
				std::vector<std::pair<int, int>> obj_name_i;
				int temp;
				int temp_name = 0;
				// get object indexes
				for (int j = 0; j < arr_val.size(); j++)
				{
					if (arr_val[j] == '\"')
					{
						if (temp_name)
						{
							obj_name_i.push_back(std::pair<int, int>(temp_name, j));
							temp_name = 0;
						}
						else
						{
							temp_name = j;
						}
					}
					else if (arr_val[j] == '{')
					{
						temp = j;
					}
					else if (arr_val[j] == '}')
					{
						obj_indexes.push_back(std::pair<int, int>(temp, j));
					}
				}

				// generate obj_name
				std::vector<std::string> obj_names;
				for (int j = 0; j < obj_name_i.size(); j++)
				{
					int dif = obj_name_i[j].second - ++obj_name_i[j].first;
					obj_names.push_back(lines[i].substr(++obj_name_i[j].first, dif));
				}

				// generate obj_content
				std::vector<std::string> obj_content;
				for (int j = 0; j < obj_indexes.size(); j++)
				{
					int dif = ++obj_indexes[j].second - obj_indexes[j].first;
					obj_content.push_back(lines[i].substr(obj_indexes[j].first, dif));
				}

				for (int j = 0; j < obj_names.size(); j++)
				{
					json_raw raw_value = read_obj_str(obj_content[j]);
					val.push_back(std::pair<std::string, my_json::json_raw>(obj_names[j], raw_value));
				}
				std::pair<std::string, json_args_obj> pushb(key_obj, val);
				obj.arr.obj.push_back(pushb);
			}
		}
		else if (comment == "object" || comment.find("{") != std::string::npos)
		{
			std::string raw_object;
			int obj_begin = 0;
			int obj_end = 0;

			for (int j = i; j < lines.size(); j++)
			{

				if (lines[j].find("{") != std::string::npos)
				{
					obj_begin = j;
				}
				else if (lines[j].find("}") != std::string::npos)
				{
					obj_end = j;
				}

				if (obj_begin != 0 && obj_end != 0)
				{
					int dif = obj_end - obj_begin++;
					
					for (int k = obj_begin++; k < obj_end; k++)
					{
						raw_object += lines[k];
					}

					break;
				}
			}

			std::string key_obj = find_key(lines[i]);
			json_raw val_obj = read_obj_str(raw_object);
			std::pair<std::string, json_raw> pushb(key_obj, val_obj);

			obj.obj.push_back(pushb);
			i = obj_end;
		}
		else
		{
			std::cout << "Error: read_json_str cannot convert that type!" << std::endl;
		}
	}
}

void my_json::read_json(fs::path path, json& obj)
{
	std::string raw = my_json::read_json_raw(path);
	my_json::read_json_str(raw, obj);
}

void my_json::read_json(std::string path, json& obj)
{
	std::string raw = my_json::read_json_raw(path);
	my_json::read_json_str(raw, obj);
}