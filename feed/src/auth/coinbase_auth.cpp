#include "auth/coinbase_auth.h"

#include <jwt-cpp/jwt.h>
#include <openssl/sha.h>

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <random>
#include <fstream>
#include <sstream>

std::string CoinbaseAuth::get_auth_header()
{
    return get_jwt();
}

std::string CoinbaseAuth::get_jwt()
{
    auto token =
        jwt::create()
            .set_issuer("coinbase-cloud")
            .set_subject(std::getenv("COINBASE_API_KEY"))
            .set_not_before(std::chrono::system_clock::now())
            .set_expires_at(std::chrono::system_clock::now() +
                            std::chrono::seconds{120})
            .set_header_claim(
                "kid", jwt::claim(std::string(std::getenv("COINBASE_API_KEY"))))
            .set_header_claim("nonce", jwt::claim(get_nonce()))
            .sign(jwt::algorithm::es256{"", std::getenv("COINBASE_PRIV_KEY")});

    return token;
}

std::string CoinbaseAuth::get_nonce()
{
    unsigned char bytes[16];
    std::random_device rd;
    for (int i = 0; i < 16; i++)
    {
        bytes[i] = rd() % 256;
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(bytes, 16, hash);

    std::ostringstream oss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        oss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return oss.str();
}
