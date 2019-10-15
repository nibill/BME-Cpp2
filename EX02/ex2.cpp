#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "ex2.h"

using namespace std;

void ex2a()
{
	vector<pair<string, string>> vec 
	{ 
		make_pair("Homer", "1111"),
		make_pair("Marge", "2222"),
        make_pair("Lisa", "3333"),
        make_pair("Magy", "4444"),
        make_pair("Bart", "5555")
	};

	map<string, string> map{vec.begin(), vec.end()};

	string input;
	while(true)
    {
		cout << "Enter name (or Exit ): ";
        getline(cin, input);
        if(input.compare("Exit") == 0) break;
        auto result = map.find(input);
        cout << (result != map.end() ? "Phone number: " +  result->second : "Name not in directory.");
        cout << endl;
	}
}

void ex2b()
{
	vector<pair<string, string>> vec 
	{
		make_pair("Homer", "1111"), 
		make_pair("Homer", "1111"),
		make_pair("Marge", "2222"), make_pair("Marge", "2222"),
        make_pair("Lisa", "3333"), make_pair("Lisa", "3333"),
        make_pair("Magy", "4444"), make_pair("Magy", "4444"),
        make_pair("Bart", "5555"), make_pair("Bart", "5555")
	};

    multimap<string, string> map{vec.begin(), vec.end()};

    string input;
    while(true)
    {
		cout << "Enter name (or Exit ): ";
        getline(cin, input);
        if(input.compare("Exit") == 0) break;
        auto result = map.equal_range(input);
        if(result.second != map.end())
        {
			cout << "Phone numbers: ";
            for(auto pair = result.first; pair != result.second; ++pair)
            {
				cout << pair->second + ", ";
			}
		}
        else
        {
			cout << "Name not in directory.";
		}
        cout << endl;
	}
}

