#ifndef BILLIONAIRE_H
#define BILLIONAIRE_H

#include <string>
#include <iostream>

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

    string name{""};
    string fortune{""};
    string country{""};

    inline friend istream& operator >>(istream& in, Billionaire &b)
    {
        getline(in, b.name, '\t');
        getline(in, b.fortune, '\t');
        getline(in, b.country, '\n');
        return in;
    }

    inline friend ostream& operator <<(ostream& out, const Billionaire &b)
    {
        out << b.name << " " << b.fortune << " " << b.country;
        return out;
    }
};

#endif // BILLIONAIRE_H
