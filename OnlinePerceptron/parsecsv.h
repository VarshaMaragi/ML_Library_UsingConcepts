#include<stdio.h>
#include<iostream>
#include <vector>
#include "boost/tokenizer.hpp"
using namespace std;
using namespace boost;
std::vector<vector<string>> parsefile(string filename)
{
	string data(filename);

    ifstream in(data.c_str());
    //if (!in.is_open()) return 1;

    typedef tokenizer< escaped_list_separator<char> > Tokenizer;
    std::vector< string > vec;
    string line;
    std::vector<vector<string>> res;
    cout<<"in parsefile"<<endl;
    while (getline(in,line))
    {
        Tokenizer tok(line);
        vec.assign(tok.begin(),tok.end());

        // vector now contains strings from one row, output to cout here
        copy(vec.begin(), vec.end(), ostream_iterator<string>(cout, "|"));
        for(int i=0;i<vec.size();i++)
        {
            cout<<"Vec"<<vec[i];
        }
        res.push_back(vec);
        cout << "\n----------------------" << endl;
    }
    return res;
}