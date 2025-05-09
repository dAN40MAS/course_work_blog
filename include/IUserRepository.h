#pragma once
#include "User.h"
#include <memory>
#include <vector>

class IUserRepository {
public:
    virtual void add_user(std::shared_ptr<User> user) = 0;
    virtual std::shared_ptr<User> find_user(const std::string& username) = 0;
    virtual std::vector<std::shared_ptr<User>> get_all_users() = 0;
    virtual ~IUserRepository() = default;
};
