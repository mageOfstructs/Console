#pragma once
#include <vector>
#include <filesystem>
#include <numeric>
#include <string>
#include <fstream>
#include <iostream>
#include "json_ns_const.h"

namespace fs { using namespace std::filesystem; }

namespace my_json
{

	using json_args_str = std::vector <std::pair<std::string, std::string>>;
	using json_args_int = std::vector <std::pair<std::string, int>>;
	using json_args_arr_str = std::vector <std::pair<std::string, std::vector<std::string>>>;
	using json_args_bool = std::vector <std::pair<std::string, bool>>;

	//										key			 value		  type
	using json_raw = std::vector<std::tuple<std::string, std::string, std::string>>;

	//				object_collection			object_name, object_content
	using json_args_obj = std::vector<std::pair<std::string, json_raw>>;
	using json_args_arr_obj = std::vector<std::pair<std::string, json_args_obj>>;

	class jarray
	{
	public:
		json_args_arr_str str;
		json_args_arr_obj obj;
	};

	class json
	{
	public:
		json() = default;
		json(std::string type);

		json_args_str str;
		json_args_int jint;
		json_args_bool jbool;
		jarray arr;
		json_args_obj obj;
	};

	std::string find_key(std::string json_line);
	std::string find_val(std::string json_line);

	std::vector<std::string> str_to_arr(std::string raw_arr);
	json_args_str str_to_obj(std::string raw_arr);
	std::string convert_arr_str(std::vector<std::string> raw); // json_write.cpp
	std::string convert_arr_obj(json_args_arr_obj raw); // json_write.cpp
	std::vector<std::string> rconvert_arr(std::string raw_json);
	std::vector<std::string> convert_json(json_raw raw, bool is_obj = false); // json_write.cpp

	json_raw gen_json_raw(json obj); // json_write.cpp
	std::string gen_json(json_raw raw_arr); // json_write.cpp

	void write_json(std::vector<std::string> json_lines, fs::path path); // json_write.cpp
	void conandwrite(json obj, fs::path path); // json_write.cpp

	std::string read_json_raw(std::string filename);
	std::string read_json_raw(fs::path file_path);
	void read_json_str(std::string raw, json &obj);
	void read_json(fs::path path, json& obj);
	void read_json(std::string path, json& obj);
	std::string convert_json_obj(my_json::json_args_obj raw_obj);
}