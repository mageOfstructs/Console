#include "console.h"

std::string gen_o2()
{
	std::string o2 = "O";
	unsigned int seed = time(0);
	std::mt19937_64 ran_gen{ seed };
	std::uniform_int_distribution<int> ran_dist{ 1,3 };

	int num = ran_dist(ran_gen);

	switch (num)
	{
	case 1:
		o2 = o2 + "P"; // Plant
		break;
	case 2:
		o2 = o2 + "C"; // Chemical
		break;
	case 3:
		o2 = o2 + "R"; // Recycling
		break;
	}

	std::uniform_int_distribution<int> ran_dist2{ 0,9 };
	std::stringstream sstr;

	for (int i = 0; i < 4; i++)
	{
		sstr << ran_dist2(ran_gen);
	}

	std::string numbers;
	sstr >> numbers;
	o2 = o2 + numbers + "SV";

	return o2;
}

std::string gen_factory()
{
	std::string fac = "F";
	unsigned int seed = time(0);
	std::mt19937_64 ran_gen{ seed };
	std::uniform_int_distribution<int> ran_dist{ 1,3 };

	int num = ran_dist(ran_gen);

	switch (num)
	{
	case 1:
		fac = fac + "M"; // Metal
		break;
	case 2:
		fac = fac + "T"; // Technology
		break;
	case 3:
		fac = fac + "B"; // Biological
		break;
	}

	std::uniform_int_distribution<int> ran_dist2{ 0,9 };
	std::stringstream sstr;

	for (int i = 0; i < 4; i++)
	{
		sstr << ran_dist2(ran_gen);
	}

	std::string numbers;
	sstr >> numbers;
	fac = fac + numbers + "SV";

	return fac;
}

std::string gen_control_p()
{
	std::string control_p = "E";
	unsigned int seed = time(0);
	std::mt19937_64 ran_gen{ seed };
	std::uniform_int_distribution<int> ran_dist{ 1,2 };

	int num = ran_dist(ran_gen);

	switch (num)
	{
	case 1:
		control_p = control_p + "C"; // Control
		break;
	case 2:
		control_p = control_p + "O"; // Observation (Camera)
		break;
	}

	std::uniform_int_distribution<int> ran_dist2{ 0,9 };
	std::stringstream sstr;

	for (int i = 0; i < 4; i++)
	{
		sstr << ran_dist2(ran_gen);
	}

	std::string numbers;
	sstr >> numbers;
	control_p = control_p + numbers + "SV";

	return control_p;
}

std::string gen_power_p()
{
	std::string power_p = "P";
	unsigned int seed = time(0);
	std::mt19937_64 ran_gen{ seed };
	std::uniform_int_distribution<int> ran_dist{ 1,5 };

	int num = ran_dist(ran_gen);

	switch (num)
	{
	case 1:
		power_p = power_p + "N"; // nuclear fusion
		break;
	case 2:
		power_p = power_p + "W"; // water energy
		break;
	case 3:
		power_p = power_p + "C"; // coal
		break;
	case 4:
		power_p = power_p + "F"; // wind force
		break;
	case 5:
		power_p = power_p + "T"; // Triithium
	}

	std::uniform_int_distribution<int> ran_dist2{ 0,9 };
	std::stringstream sstr;

	for (int i = 0; i < 4; i++)
	{
		sstr << ran_dist2(ran_gen);
	}

	std::string numbers;
	sstr >> numbers;
	power_p = power_p + numbers + "SV";

	return power_p;
}

std::vector<std::string> gen_cameras()
{
	std::vector<std::string> cameras(1, "E");
	char space;
	unsigned int seed = time(0);
	std::mt19937_64 ran_gen{ seed };
	std::uniform_int_distribution<int> ran_dist{ 1,3 };

	int num = ran_dist(ran_gen);

	switch (num)
	{
	case 1:
		for (int i = 0; i < 2; i++)
		{
			cameras.push_back("E");
		}
		break;
	case 2:
		for (int i = 0; i < 4; i++)
		{
			cameras.push_back("E");
		}
		break;
	case 3:
		for (int i = 0; i < 5; i++)
		{
			cameras.push_back("E");
		}
		break;
	}

	std::uniform_int_distribution<int> ran_dist2{ 0,9 };
	std::stringstream sstr;
	for (int i = 0; i < cameras.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			sstr << ran_dist2(ran_gen);
		}
		sstr << ' ';
	}

	std::string numbers;
	std::string full_name;
	for (int i = 0; i < cameras.size(); i++)
	{
		sstr >> numbers >> space;
		full_name = "E" + numbers + "SV";
		cameras[i] = full_name;
		numbers.clear();
		full_name.clear();
	}

	return cameras;
}

void gen_ids()
{
	std::cout << "searching for O2 Generator..." << std::endl;
	std::string o2 = gen_o2();
	std::cout << "O2 generator: " << o2 << " found" << std::endl;

	std::cout << "searching for Factory..." << std::endl;
	std::string fac = gen_factory();
	std::cout << "Factory: " << fac << " found" << std::endl;

	std::cout << "searching for Control Panel..." << std::endl;
	std::string control_panel = gen_control_p();
	std::cout << "Control Panel: " << control_panel << " found" << std::endl;

	std::cout << "searching for Power Plant..." << std::endl;
	std::string power_plant = gen_power_p();
	std::cout << "Power Plant: " << power_plant << " found" << std::endl;

	std::cout << "searching for Camera(s)..." << std::endl;
	std::vector<std::string> cameras = gen_cameras();
	std::cout << "Camera(s): ";
	for (int i = 0; i < cameras.size(); i++)
	{
		std::cout << cameras[i] << ",";
	}
	std::cout << " found" << std::endl;

	std::string id_path = "devices.json";
	my_json::json id_data("devices");
	id_data.str[dev_o2].second = o2;
	id_data.str[dev_fac].second = fac;
	id_data.str[dev_cc].second = control_panel;
	id_data.str[dev_pp].second = power_plant;
	id_data.arr.str[dev_cams].second = cameras;
	my_json::conandwrite(id_data, id_path);
}