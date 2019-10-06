#include "ex1.h"

#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <cctype>

using namespace std;

ex1::ex1()
{
    vector<char> alphabet(26);
    iota(alphabet.begin(), alphabet.end(), 'a');
    copy(alphabet.begin(), alphabet.end(), ostream_iterator<char>(cout, " "));
    cout << endl;
    reverse_copy(alphabet.begin(), alphabet.end(), ostream_iterator<char>(cout, " "));
}
