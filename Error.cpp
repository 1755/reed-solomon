//
// Created by sergey on 13.12.15.
//

#include "Error.h"

Error::Error()
{
    m_message = "";
}

Error::Error(const string& message)
{
    m_message = message;
}

string Error::message() const
{
    return m_message;
}
