#ifndef BILLIONAIRE_H
#define BILLIONAIRE_H

#include <map>
#include <string>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Billionaire
{
public:
    Billionaire()
    {
        name.clear();
        fortune.clear();
        country.clear();
    }

    string name;
    string fortune;
    string country;

    friend istream& operator >>(istream& in, Billionaire &Destination)
    {
        getline(in,Destination.name,'\t');
        getline(in,Destination.fortune,'\t');
        getline(in,Destination.country,'\n');
           return in;
    }

    friend ostream& operator <<(ostream& out, const Billionaire &Source)
    { //const is a key word as friend it is.
        out<<Source.name <<" "<<Source.fortune<<" "<<Source.country;
        return out;
    }
};

#endif // BILLIONAIRE_H
