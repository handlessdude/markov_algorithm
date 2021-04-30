#include "MarkovAlgorithm.h"

bool file_write_enabled;
bool calc_output_enabled;
std::vector<Rule> ruls;
string filename;
std::ofstream writeto;

void input_subs()
{
	ruls.clear();

	std::cout << "\nPlease enter your rules in format \"P->Q\" or \"P->.Q\" if rule is final:\n"
		<< "[input empty string to finish]\n"
		<< "[if it's needed to enter empty word as a side of the rule just enter nothing there]\n\n";
	std::string s;
input_label:
	int i = 1;
	std::cout << i << ")";
	while (std::getline(std::cin, s))
	{
		if (s == "")
		{
			break;
		}
		try
		{
			ruls.push_back(Rule(s));
		}
		catch (std::exception e)
		{
			std::cout << "\n" <<e.what() << "\nretry input:\n" << i << ")";
			continue;
		}
		std::cout << "\n" << ++i << ")";
	}
	if (!ruls.size())
	{
		std::cout << "\nPlease unput at least one rule...\n\n";
		goto input_label;
	}
}

//===============================================================

//executes one substitution
bool replace(string& x, Rule& rule)
{
	string& from = rule.P;
	string& to = rule.Q;
	size_t start_pos = x.find(from);
	if (start_pos == string::npos)
	{
		return false;
	}
	x.replace(start_pos, from.length(), to);
	return true;
}

//finds index of applicable rule
int applicable_index(string& x)
{
	for (size_t i = 0; i < ruls.size(); i += 1)
	{
		if (x.find(ruls[i].P) != string::npos)
		{
			return i;
		}
	}
	return string::npos;
}

//executes one step of markov algorithm
bool ma_step(string& x)
{
	int index = applicable_index(x);
	if (index != string::npos)
	{
		if (calc_output_enabled)
		{
			cout << "Found applicable rule: " << index + 1 << ")" << ruls[index] << "\n";
			if (file_write_enabled)
			{
				writeto << "Found applicable rule: " << index + 1 << ")" << ruls[index] << "\n";
			}
		}

		if (ruls[index].P == "")
		{
			x.insert(0, ruls[index].Q);
		}
		else
		{
			replace(x, ruls[index]);
		}

		if (calc_output_enabled)
		{
			cout << "String after applying: " << x << "\n\n";
			if (file_write_enabled)
			{
				writeto << "String after applying: " << x << "\n\n";
			}
		}
		return ruls[index].is_terminal;
	}
	if (calc_output_enabled)
	{
		cout << "No applicable rule found.\n\n";
		if (file_write_enabled)
		{
			writeto << "No applicable rule found.\n\n";
		}
	}

	return true;
}

//executes markov algorithm
void ma(string& x)
{
	bool is_terminal = false;
	int i = 1;
	while (!is_terminal)
	{
		if (calc_output_enabled)
		{
			cout << i << ") ";
			if (file_write_enabled)
			{
				writeto << i << ") ";
			}
			i++;
		}
		is_terminal = ma_step(x);
	}
}

void write_rules_to_file()
{
	writeto << "Algorithm scheme:\n\n";
	int i = 1;
	for (auto& rule : ruls)
	{
		writeto << (i++) << ")" << rule << "\n";
	}
	writeto << "\n ================ \n\n";
}

//===============================================================

void run()
{
	std::string s;
	
start_label:
	//===============enabling output
	cout << " =========== START ===========\nEnable calculations output? (y = yes, no = any other key): ";
	std::getline(std::cin, s);
	calc_output_enabled = (s == "y");

	//enabling saving to file
	cout << "Enable saving output in file? (y = yes, no = any other key): ";
	std::getline(std::cin, s);
	file_write_enabled = (s == "y");
	if (file_write_enabled)
	{
		cout << "Enter filename: ";
		std::getline(std::cin, filename);
		while(fs::exists(fs::current_path().u8string() + "/" + filename))
		{
			cout << "File already exists in the current folder. Choose another name: ";
			std::getline(std::cin, filename);
		}
		writeto.open(filename);
	}

	//===============reentering rules
	if (ruls.size())
	{
		cout << "Enter new rules? (y = yes, no = any other key): ";
		std::getline(std::cin, s);
		if (s == "y")
		{
			input_subs();
		}
	}
	else
	{
		input_subs();
	}

	if (file_write_enabled)
	{
		write_rules_to_file();
	}

	//===============entering new string
	cout << "\nEnter the string to process:\n";
	std::getline(std::cin, s);
	if (file_write_enabled)
	{
		writeto << "String to process:\n" << s << "\n\n ================ \n\n";
	}

	if (calc_output_enabled)
	{
		cout << "\nString process started.\n\n";
		if (file_write_enabled)
		{
			writeto << "String processing steps:\n\n";
		}
	}

	ma(s);

	//===============result output
	if (file_write_enabled)
	{
		if (calc_output_enabled)
		{
			writeto << " ================ \n\n";
		}
		writeto << "Processed string:\n" << s << "\n";
		writeto.close();
	}

	cout << "\nProcessed string:\n" << s<< "\n\nAnother one? (y = yes, no = any other key): ";
	std::getline(std::cin, s);
	if (s == "y")
	{
		cout << "\n";
		goto start_label;
	}
	cout << "\n =========== PROCESS FINISHED ===========\n";
}


int main()
{
	setlocale(LC_ALL, "Russian");

	run();
	/*
	
	
	*/
	system("pause");

	return 0;
}