#pragma once
#include <vector>
#include <string>

class Profile {
    std::string bio;
    std::vector<std::string> interests;

public:
    Profile(const std::string& bio = "", const std::vector<std::string>& interests = {});
    void print() const;
};
