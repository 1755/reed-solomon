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
