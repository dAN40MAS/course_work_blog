#pragma once
#include "IUserRepository.h"
#include <memory>
#include <vector>

class UserFactory {
    std::shared_ptr<IUserRepository> repo;

public:
    explicit UserFactory(std::shared_ptr<IUserRepository> repo);
    std::shared_ptr<User> create_user(
        const std::string& username,
        const std::string& password,
        const std::string& bio,
        const std::vector<std::string>& interests
    );
};
