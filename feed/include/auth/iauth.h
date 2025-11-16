#pragma once
#include <string>

class IAuthProvider
{
   public:
    virtual std::string get_auth_header() = 0;
};