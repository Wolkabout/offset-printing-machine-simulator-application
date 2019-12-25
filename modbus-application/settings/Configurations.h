#ifndef CONFIGURATIONS_H
#define CONFIGURATIONS_H

#include <string>
#include <vector>

class Configurations
{
public:
    static const std::string PATH;
    static const int LENGTH;
    static const char DELIMITER;

    static bool exists();

    static std::vector<int> load();

    static void save(std::vector<int>);
};

#endif // CONFIGURATIONS_H
