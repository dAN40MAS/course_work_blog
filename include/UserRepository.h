#pragma once
#include "IUserRepository.h"
#include <map>
#include <memory>

class UserRepository : public IUserRepository {
    std::map<std::string, std::shared_ptr<User>> users;

public:
    void add_user(std::shared_ptr<User> user) override;
    std::shared_ptr<User> find_user(const std::string& username) override;
    std::vector<std::shared_ptr<User>> get_all_users() override;
};
