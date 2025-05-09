#include "../include/UserRepository.h"

void UserRepository::add_user(std::shared_ptr<User> user) {
    users[user->get_username()] = user;
}

std::shared_ptr<User> UserRepository::find_user(const std::string& username) {
    auto it = users.find(username);
    return it != users.end() ? it->second : nullptr;
}

std::vector<std::shared_ptr<User>> UserRepository::get_all_users() {
    std::vector<std::shared_ptr<User>> result;
    for (const auto& pair : users) result.push_back(pair.second);
    return result;
}
