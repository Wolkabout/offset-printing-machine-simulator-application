#include "configurations.h"

const std::string Configurations::PATH = "./config";

const int Configurations::LENGTH = 7;

const char Configurations::DELIMITER = ',';

bool Configurations::exists() {
    std::ifstream file(PATH);
    if (file.is_open()) {
        return true;
    }
    return false;
}

std::vector<int> Configurations::load() {
    std::vector<int> values;
    std::string line;
    std::ifstream file(PATH);
    if (file.is_open()) {
        getline(file, line);
        while (!line.empty()) {
            std::string part = line.substr(0, line.find(DELIMITER));
            line = line.erase(0, part.size() + 1);
            values.emplace_back(std::atoi(part.c_str()));
        }
        file.close();
    }
    return values;
}

void Configurations::save(std::vector<int> values) {
    std::ofstream file(PATH);
    if (file.is_open()) {
        for (int i = 0; i < LENGTH; i++) {
            file << values[i];
            if (i != (LENGTH - 1)) {
                file << DELIMITER;
            }
        }
        file.close();
    }
}
