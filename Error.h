#pragma once

#include <exception>
#include <string>

using namespace std;

class Error : exception
{
    string m_message;

public:
    Error();
    Error(const string& message);
};



