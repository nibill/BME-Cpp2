#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "billionaire.h"

Billionaire::Billionaire()
{
    ifstream stream("Forbes2018.txt");
	if(!stream)
	{
		cout << " WARNING : File not found !" << endl;
	}

    vector<Billionaire> Billionaires;
    copy(istream_iterator <Billionaire>(stream), istream_iterator <Billionaire>(), back_inserter(Billionaires));
	map<string, pair<Billionaire, int>> map;

	for(auto b : Billionaires)
    {
		auto _r = map.find(b.country);
        auto pair = map.try_emplace(b.country, make_pair(b, 1));
        if(!pair.second)
        {
			pair.first->second.second++;
			if(_r != map.end() && stof(pair.first->second.first.fortune) < stof(_r->second.first.fortune))
            {
				map.try_emplace(b.country, make_pair(_r->second.first, pair.first->second.second));
			}
		}
	}

	//print all, could us a counter for first 5
    for(auto _m : map)
    {
		cout << _m.first << ": " << _m.second.second << " Billionaires. Richest is " << _m.second.first.name << " with " << _m.second.first.fortune << "B$" << endl;
	}
}
