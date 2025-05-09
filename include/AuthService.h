#pragma once
#include "IUserRepository.h"
#include <memory>

class AuthService {
    std::shared_ptr<IUserRepository> user_repo;

public:
    AuthService(std::shared_ptr<IUserRepository> repo);
    std::shared_ptr<User> authenticate(const std::string& username, const std::string& password);
};
