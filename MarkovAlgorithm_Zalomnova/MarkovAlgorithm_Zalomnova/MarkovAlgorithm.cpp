#include "MarkovAlgorithm.h"

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
int applicable_index(string& x, vector<Rule>& ruls)
{
	for (size_t i = 0; i < ruls.size(); i+=1)
	{
		if (x.find(ruls[i].P)!=string::npos)
		{
			return i;
		}
	}
	return string::npos;
}

//executes one step of markov algorithm
bool ma_step(string& x, vector<Rule>& ruls, bool output_enabled)
{
	int index = applicable_index(x, ruls);
	if (index != string::npos)
	{
		if (output_enabled)
		{
			cout << "Found applicable rule: " << index + 1 << ")" << ruls[index] << "\n";
		}
		
		if (ruls[index].P == "")
		{
			x.insert(0, ruls[index].Q);
		}
		else
		{
			replace(x, ruls[index]);
		}

		if (output_enabled)
		{
			cout << "String after applying: " << x << "\n\n";
		}
		return ruls[index].is_terminal;
	}
	if (output_enabled)
	{
		cout << "No applicable rule found.\n\n";
	}
	
	return true;
}

//executes markov algorithm
void ma(string& x, vector<Rule>& ruls, bool output_enabled)
{
	bool is_terminal = false;
	while (!is_terminal)
	{
		is_terminal = ma_step(x, ruls, output_enabled);
	}
}