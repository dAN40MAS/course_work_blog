#pragma once

#include <map>
#include <memory>
#include <string>
#include <json/json.h>
#include "IUserRepository.h"
#include "User.h"

class UserRepository : public IUserRepository {
    std::map<std::string, std::shared_ptr<User>> users;

public:
    void add_user(std::shared_ptr<User> user) override;
    std::shared_ptr<User> find_user(const std::string& username) override;
    std::vector<std::shared_ptr<User>> get_all_users() override;
    
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
};