#include "auth/iauth.h"

#include <cstdlib>
#include <fstream>
#include <string>

void IAuthProvider::load_dotenv(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        return;

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty() || line[0] == '#')
            continue;

        size_t equal_pos = line.find('=');
        if (equal_pos == std::string::npos)
            continue;

        std::string key = line.substr(0, equal_pos);
        std::string value = line.substr(equal_pos + 1);

        setenv(key.c_str(), value.c_str(), 1);
    }

    file.close();
    return;
}