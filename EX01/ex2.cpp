#include "ex2.h"

#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <cctype>

using namespace std;

ex2::ex2()
{
    ifstream file_cars("cars.txt");
    istream_iterator<string> start(file_cars), end;
    vector<string> cars(start, end);

    copy(cars.begin(), cars.end(), ostream_iterator<string>(cout, " "));
    cout << endl << endl;
    sort(cars.begin(), cars.end());
    copy(cars.begin(), cars.end(), ostream_iterator<string>(cout, " "));

    cout << endl;

    cout << "\nUsing iterators:\n";
    for (auto it = cars.cbegin(); it != cars.cend(); ++it)
    {
        if((*it)[0] == 'A')
        {
            cout << *it << " ";
        }
    }

    cout << endl << endl;

    cout << "\nUsing a ranged based for loop:\n";
    for ( const auto& car : cars )
        {
        if (car[0] == 'A')
            cout << car << '\n';
        }


    vector<char> filter{'a', 'b', 'c'};
    copy_if(cars.begin(), cars.end(), ostream_iterator<string>(cout, " "), [filter](string input)
    {
       for(const auto& f : filter)
       {
           if(tolower(input.front()) == tolower(f))
           {
               return true;
           }
       }
       return false;
    });
}
