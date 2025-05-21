#pragma once

#include <vector>
#include <string>
#include <json/json.h>

class Profile {
    std::string bio;
    std::vector<std::string> interests;

public:
    Profile(const std::string& bio = "", const std::vector<std::string>& interests = {});
    void print() const;
    
    Json::Value toJson() const;
    static Profile fromJson(const Json::Value& json);
};