#include "../include/UserRepository.h"
#include <fstream>

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

bool UserRepository::saveToFile(const std::string& filename) {
    Json::Value root;
    for (const auto& [name, user] : users) {
        root.append(user->toJson());
    }
    
    Json::StyledWriter writer;
    std::ofstream file(filename);
    file << writer.write(root);
    return file.good();
}

bool UserRepository::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;
    
    Json::Value root;
    Json::Reader reader;
    if (!reader.parse(file, root)) return false;
    
    users.clear();
    for (const auto& userJson : root) {
        auto user = User::fromJson(userJson);
        users[user->get_username()] = user;
    }
    return true;
}