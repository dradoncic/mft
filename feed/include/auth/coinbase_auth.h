#pragma once
#include <string>
#include <unordered_map>

#include "iauth.h"

class CoinbaseAuth : public IAuthProvider
{
   public:
    virtual ~CoinbaseAuth() = default;
    std::string get_auth_header() override;

   private:
    std::string get_jwt();
    std::string get_nonce();
};