#pragma once
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class InputParser 
{
public:
    InputParser(int& argc, char** argv)
    {
        for (int i = 1; i < argc; ++i)
            this->tokens.push_back(string(argv[i]));
    }
    bool cmdOptionExists(const std::string& option) const
    {
        return find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
    }
private:
    vector <string> tokens;
};

