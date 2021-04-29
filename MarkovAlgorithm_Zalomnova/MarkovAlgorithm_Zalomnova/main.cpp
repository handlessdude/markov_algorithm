#include "MarkovAlgorithm.h"

void input_subs(std::vector<Rule>& subs)
{
	subs.clear();

	std::cout << "\nPlease enter your rules in format \"P->Q\" or \"P->.Q\" if rule is final:\n"
		<< "(input empty string to finish)\n\n";
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
			subs.push_back(Rule(s));
		}
		catch (std::exception e)
		{
			std::cout << "\n" <<e.what() << "\nretry input:\n" << i << ")";
			continue;
		}
		std::cout << "\n" << ++i << ")";
	}
	if (!subs.size())
	{
		std::cout << "\nPlease unput at least one rule...\n\n";
		goto input_label;
	}
}

void run()
{
	bool output_enabled;
	std::string s;
	std::vector<Rule> ruls;

start_label:
	//===============enabling output
	cout << " =========== START ===========\nEnable calculations output? (y = yes, no = any other key): ";
	std::getline(std::cin, s);
	output_enabled = (s == "y");

	//===============reentering rules
	if (ruls.size())
	{
		cout << "Enter new rules? (y = yes, no = any other key): ";
		std::getline(std::cin, s);
		if (s == "y")
		{
			input_subs(ruls);
		}
	}
	else
	{
		input_subs(ruls);
	}
	
	//===============entering new string
	cout << "\nEnter the string to process:\n";
	std::getline(std::cin, s);

	if (output_enabled)
	{
		cout << "\nString process started:\n\n";
	}
	ma(s, ruls, output_enabled);

	//===============result output
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

	cout << "[tip: if it's needed to enter empty word as a side of the rule just enter nothing there]\n\n";
	run();

	//EXAMPLE OF PROGRAM WORKING CYCLE:

	/*
[tip: if it's needed to enter empty word as a side of the rule just enter nothing there]

 =========== START ===========
Enable calculations output? (y = yes, no = any other key): y

Please enter your rules in format "P->Q" or "P->.Q" if rule is final:
(input empty string to finish)

1)->.test1

2)

Enter the string to process:
vsem perviy privet!

String process started:

Found applicable rule: 1)<empty>->.test1
String after applying: test1vsem perviy privet!


Processed string:
test1vsem perviy privet!

Another one? (y = yes, no = any other key): y

 =========== START ===========
Enable calculations output? (y = yes, no = any other key): n
Enter new rules? (y = yes, no = any other key): n

Enter the string to process:
privet mne i moemu drugu toje!

Processed string:
test1privet mne i moemu drugu toje!

Another one? (y = yes, no = any other key): y

 =========== START ===========
Enable calculations output? (y = yes, no = any other key): y
Enter new rules? (y = yes, no = any other key): y

Please enter your rules in format "P->Q" or "P->.Q" if rule is final:
(input empty string to finish)

1)ab->

2)a->b

3)

Enter the string to process:
aababab

String process started:

Found applicable rule: 1)ab->
String after applying: aabab

Found applicable rule: 1)ab->
String after applying: aab

Found applicable rule: 1)ab->
String after applying: a

Found applicable rule: 2)a->b
String after applying: b

No applicable rule found.


Processed string:
b

Another one? (y = yes, no = any other key): y

 =========== START ===========
Enable calculations output? (y = yes, no = any other key): y
Enter new rules? (y = yes, no = any other key): y

Please enter your rules in format "P->Q" or "P->.Q" if rule is final:
(input empty string to finish)

1)b->.a

2)a->b

3)

Enter the string to process:
aaa

String process started:

Found applicable rule: 2)a->b
String after applying: baa

Found applicable rule: 1)b->.a
String after applying: aaa


Processed string:
aaa

Another one? (y = yes, no = any other key): y

 =========== START ===========
Enable calculations output? (y = yes, no = any other key): y
Enter new rules? (y = yes, no = any other key): y

Please enter your rules in format "P->Q" or "P->.Q" if rule is final:
(input empty string to finish)

1)1->0|

2)|0->0||

3)0->

4)

Enter the string to process:
101

String process started:

Found applicable rule: 1)1->0|
String after applying: 0|01

Found applicable rule: 1)1->0|
String after applying: 0|00|

Found applicable rule: 2)|0->0||
String after applying: 00||0|

Found applicable rule: 2)|0->0||
String after applying: 00|0|||

Found applicable rule: 2)|0->0||
String after applying: 000|||||

Found applicable rule: 3)0->
String after applying: 00|||||

Found applicable rule: 3)0->
String after applying: 0|||||

Found applicable rule: 3)0->
String after applying: |||||

No applicable rule found.


Processed string:
|||||

Another one? (y = yes, no = any other key): y

 =========== START ===========
Enable calculations output? (y = yes, no = any other key): n
Enter new rules? (y = yes, no = any other key): n

Enter the string to process:
101

Processed string:
|||||

Another one? (y = yes, no = any other key): n

 =========== PROCESS FINISHED ===========
	*/
	system("pause");
	return 0;
}