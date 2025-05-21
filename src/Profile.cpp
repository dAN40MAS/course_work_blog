#include "../include/Profile.h"
#include <iostream>
Profile::Profile(const std::string& bio, const std::vector<std::string>& interests)
    : bio(bio), interests(interests) {}

void Profile::print() const {
    std::cout << "\nО пользователе: " << bio << "\nИнтересы: ";
    if (interests.empty()) std::cout << "не указаны";
    else for (size_t i = 0; i < interests.size(); ++i)
        std::cout << interests[i] << (i != interests.size()-1 ? ", " : "");
    std::cout << "\n";
}

Json::Value Profile::toJson() const {
    Json::Value json;
    json["bio"] = bio;
    
    Json::Value interestsJson;
    for (const auto& i : interests) {
        interestsJson.append(i);
    }
    json["interests"] = interestsJson;
    return json;
}

Profile Profile::fromJson(const Json::Value& json) {
    std::vector<std::string> interests;
    for (const auto& i : json["interests"]) {
        interests.push_back(i.asString());
    }
    return Profile(json["bio"].asString(), interests);
}