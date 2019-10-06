#include "ex3.h"

#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <cctype>

using namespace std;

ex3::ex3()
{
    istream_iterator<string> input_stream_start(cin), input_stream_end;
    vector<string> words(input_stream_start, input_stream_end);
    cout << endl;
    sort(words.begin(), words.end());
    auto last = unique(words.begin(), words.end());
    words.erase(last, words.end());
    copy(words.begin(), words.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
}
