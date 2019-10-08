#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include "ex2.h"

using namespace std;

void ex2a()
{
    vector <pair < string , string >> vec
            { make_pair ("Homer", " 1111 "),
             make_pair ("Marge", " 2222 "),
             make_pair ("Lisa", " 3333 "),
             make_pair ("Magy", " 4444 "),
             make_pair ("Bart", " 5555 ")};

     unordered_map <string,string> book(vec.begin(),vec.end());
     cout<<"Enter name (or Exit ): "<<endl;
     string input;
     cin>>input;
     auto it= book.find(input);
     if(it != book.cend())
     {
         cout<<" Phone number : "<<it->second<<endl;
     }
     else
     {
         cout<<"Name not in directory ."<<endl;
     }
}
void ex2b()
{
    vector <pair < string , string >> vec
               { make_pair ("Homer", " 1111 "),
                make_pair ("Magy", " 54545 "),
                make_pair ("Homer", " 11122 "),
                make_pair ("Homer", " 11133 "),
                make_pair ("Marge", " 2222 "),
                make_pair ("Lisa", " 3333 "),
                make_pair ("Magy", " 4444 "),
                make_pair ("Bart", " 5555 ")};
        multimap <string,string> book(vec.begin(),vec.end());
        cout<<"Enter name (or Exit ): "<<endl;
        string input;
        cin>>input;
        auto it = book.equal_range(input);
        if(it.second != book.end())
        {
            cout<<"Number(s): ";
            for(auto i = it.first; i!= it.second; ++i )
            {
                cout<< i->second << " ";
            }
         cout<<endl;
        }
        else
        {
            cout<<"Name not in directory ."<<endl;
        }
}

