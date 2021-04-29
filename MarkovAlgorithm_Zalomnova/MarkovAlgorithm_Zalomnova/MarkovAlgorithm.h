#ifndef MarkovAlgorithm_h
#define MarkovAlgorithm_h

#include<iostream>
#include <string>
#include <vector>
#include <assert.h>

using namespace std;

struct Rule
{
	string P;
	string Q;
	bool is_terminal;

	Rule(const string& p, const string& q, bool is_terminal)
	{
		this->P = p;
		this->Q = q;
		this->is_terminal = is_terminal;
	}

	Rule(const string& s)
	{
		std::string fin_delim = "->.";
		size_t delim_size = 3;
		this->is_terminal = true;

		std::string delim = "->";

		auto barrier = s.find(fin_delim);
		if (barrier == std::string::npos) 
		{
			barrier = s.find(delim);
			if (barrier == std::string::npos)
			{
				throw invalid_argument("Ñannot distinguish substitution.");
			}
			delim_size = 2;
			this->is_terminal = false;
		}

		this->P = s.substr(0, barrier);
		this->Q = s.substr(barrier + delim_size, s.size() - barrier);
	}

	friend std::ostream& operator<<(std::ostream& out, const Rule& sub) {
		return out << (sub.P == ""? "<empty>" : sub.P) << (sub.is_terminal? "->." : "->")<< sub.Q;
	}
};

//executes one substitution
bool replace(string& x, Rule& rule);

//finds index of applicable rule
int applicable_index(string& x, vector<Rule>& ruls);

//executes one step of markov algorithm
bool ma_step(string& x, vector<Rule>& subs, bool output_enabled);

//executes markov algorithm
void ma(string& x, vector<Rule>& subs, bool output_enabled);

//for inputting rules of algorithm
void input_subs(std::vector<Rule>& subs);

//runs the process
void run();

#endif 