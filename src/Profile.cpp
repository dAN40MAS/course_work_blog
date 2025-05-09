#include "Profile.h"
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
